/**
 * ref: https://docs.nvidia.com/cupti/tutorial/tutorial.html
 */
#include <stdio.h>
#include <vector>
#include "cuda_compat.h"
#include "cuda_helpers.h"

// Global variables for PM Sampling
CUpti_PmSampling_Object* g_pPmSamplingObject = NULL;

std::string g_chipName;
std::vector<uint8_t> g_configImage;
std::vector<uint8_t> g_counterDataImage;

std::vector<const char*> g_metrics = {
	"gr__cycles_active.avg",	// GPU Active Cycles
	"gr__cycles_elapsed.max",	// GPU Elapsed Cycles
	"sm__cycles_active.avg"		// SM Active Cycles
};

// CUDA kernel for vector addition
__global__ void VectorAdd(const int *A, const int *B, int *C, int N)
{
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	if (idx < N)
		C[idx] = A[idx] + B[idx];
}

// Helper function to initialize PM Sampling
void InitializeAndEnablePmSampling(int deviceIndex);
void ConfigurePmSampling(uint64_t hardwareBufferSize, uint64_t samplingInterval);
void StartPmSampling();
void StopPmSampling();
void DecodeAndPrintSamplingData();
void CleanupPmSampling();

int main(void)
{
	const int vectorLen = 4096 * 4096 * 2;
	size_t size = vectorLen * sizeof(int);

	// Initialize CUDA
	cuInit(0);

	// Setup CUDA workload
	int *h_A = (int*)malloc(size);
	int *h_B = (int*)malloc(size);
	int *h_C = (int*)malloc(size);

	for (int i = 0; i < vectorLen; ++i) {
		h_A[i] = i;
		h_B[i] = i * 2;
	}

	int *d_A, *d_B, *d_C;
	cudaMalloc((void **)&d_A, size);
	cudaMalloc((void **)&d_B, size);
	cudaMalloc((void **)&d_C, size);

	cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

	// Initalize and Enable PM Sampling
	constexpr int deviceIndex = 0;
	InitializeAndEnablePmSampling(deviceIndex);

	// Configure PM Sampling
	constexpr size_t hardwareBufferSize = 512 * 1024 * 1024; // 512MB buffer
	constexpr uint64_t samplingInterval = 100000; // 100us interval
	ConfigurePmSampling(hardwareBufferSize, samplingInterval);

	// Start PM Sampling
	StartPmSampling();

	// Launch CUDA workload
	int threadsPerBlock = 512;
	int blocksPerGrid = (vectorLen + threadsPerBlock - 1) / threadsPerBlock;
	for (int i = 0; i < 100; ++i) {
		VectorAdd<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, vectorLen);
	}
	cudaDeviceSynchronize();

	// Stop PM Sampling
	StopPmSampling();

	// Decode and print sampling data
	DecodeAndPrintSamplingData();

	// Cleanup PM Sampling
	CleanupPmSampling();

	// Cleanup
	cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);
	cudaFree(d_A); cudaFree(d_B); cudaFree(d_C);
	free(h_A); free(h_B); free(h_C);
	return 0;
}

void CreateConfigImage()
{
	CUpti_Profiler_Host_Initialize_Params hostInitializeParams = {CUpti_Profiler_Host_Initialize_Params_STRUCT_SIZE};
	hostInitializeParams.profilerType = CUPTI_PROFILER_TYPE_PM_SAMPLING;
	hostInitializeParams.pChipName = g_chipName.c_str();
	hostInitializeParams.pCounterAvailabilityImage = nullptr;
	cuptiProfilerHostInitialize(&hostInitializeParams);
	CUpti_Profiler_Host_Object* pHostObject = hostInitializeParams.pHostObject;

	CUpti_Profiler_Host_ConfigAddMetrics_Params configAddMetricsParams {CUpti_Profiler_Host_ConfigAddMetrics_Params_STRUCT_SIZE};
	configAddMetricsParams.pHostObject = pHostObject;
	configAddMetricsParams.ppMetricNames = g_metrics.data();
	configAddMetricsParams.numMetrics = g_metrics.size();
	cuptiProfilerHostConfigAddMetrics(&configAddMetricsParams);

	CUpti_Profiler_Host_GetConfigImageSize_Params getConfigImageSizeParams {CUpti_Profiler_Host_GetConfigImageSize_Params_STRUCT_SIZE};
	getConfigImageSizeParams.pHostObject = pHostObject;
	cuptiProfilerHostGetConfigImageSize(&getConfigImageSizeParams);
	g_configImage.resize(getConfigImageSizeParams.configImageSize);

	CUpti_Profiler_Host_GetConfigImage_Params getConfigImageParams = {CUpti_Profiler_Host_GetConfigImage_Params_STRUCT_SIZE};
	getConfigImageParams.pHostObject = pHostObject;
	getConfigImageParams.pConfigImage = g_configImage.data();
	getConfigImageParams.configImageSize = g_configImage.size();
	cuptiProfilerHostGetConfigImage(&getConfigImageParams);

	CUpti_Profiler_Host_GetNumOfPasses_Params getNumOfPassesParam {CUpti_Profiler_Host_GetNumOfPasses_Params_STRUCT_SIZE};
	getNumOfPassesParam.pConfigImage = g_configImage.data();
	getNumOfPassesParam.configImageSize = g_configImage.size();
	cuptiProfilerHostGetNumOfPasses(&getNumOfPassesParam);
	printf("Num of Passes: %d\n", getNumOfPassesParam.numOfPasses);

	CUpti_Profiler_Host_Deinitialize_Params deinitializeParams = {CUpti_Profiler_Host_Deinitialize_Params_STRUCT_SIZE};
	deinitializeParams.pHostObject = pHostObject;
	cuptiProfilerHostDeinitialize(&deinitializeParams);
	pHostObject = nullptr;
}

void EvaluateAndPrintForSample(size_t sampleIndex, CUpti_Profiler_Host_Object* pHostObject, std::vector<uint8_t>& counterDataImage)
{
	CUpti_PmSampling_CounterData_GetSampleInfo_Params getSampleInfoParams = {CUpti_PmSampling_CounterData_GetSampleInfo_Params_STRUCT_SIZE};
	getSampleInfoParams.pPmSamplingObject = g_pPmSamplingObject;
	getSampleInfoParams.pCounterDataImage = counterDataImage.data();
	getSampleInfoParams.counterDataImageSize = counterDataImage.size();
	getSampleInfoParams.sampleIndex = sampleIndex;
	cuptiPmSamplingCounterDataGetSampleInfo(&getSampleInfoParams);
	printf("Sample Index: %zu, Start Timestamp: %llu, End Timestamp: %llu\n", sampleIndex, getSampleInfoParams.startTimestamp, getSampleInfoParams.endTimestamp);

	std::vector<double> metricValues(g_metrics.size());
	CUpti_Profiler_Host_EvaluateToGpuValues_Params evalauateToGpuValuesParams {CUpti_Profiler_Host_EvaluateToGpuValues_Params_STRUCT_SIZE};
	evalauateToGpuValuesParams.pHostObject = pHostObject;
	evalauateToGpuValuesParams.pCounterDataImage = counterDataImage.data();
	evalauateToGpuValuesParams.counterDataImageSize = counterDataImage.size();
	evalauateToGpuValuesParams.ppMetricNames = g_metrics.data();
	evalauateToGpuValuesParams.numMetrics = g_metrics.size();
	evalauateToGpuValuesParams.rangeIndex = sampleIndex;
	evalauateToGpuValuesParams.pMetricValues = metricValues.data();
	cuptiProfilerHostEvaluateToGpuValues(&evalauateToGpuValuesParams);

	for (size_t i = 0; i < g_metrics.size(); ++i) {
		printf("\t%s: %f\n", g_metrics[i], metricValues[i]);
	}
	printf("\n");
}

void EvaluateAndPrintAllSamples(size_t numOfSamples)
{
	CUpti_Profiler_Host_Initialize_Params hostInitializeParams = {CUpti_Profiler_Host_Initialize_Params_STRUCT_SIZE};
	hostInitializeParams.profilerType = CUPTI_PROFILER_TYPE_PM_SAMPLING;
	hostInitializeParams.pChipName = g_chipName.c_str();
	hostInitializeParams.pCounterAvailabilityImage = nullptr;
	cuptiProfilerHostInitialize(&hostInitializeParams);
	CUpti_Profiler_Host_Object* pHostObject = hostInitializeParams.pHostObject;

	for (size_t sampleIndex = 0; sampleIndex < numOfSamples; ++sampleIndex) {
		EvaluateAndPrintForSample(sampleIndex, pHostObject, g_counterDataImage);
	}

	CUpti_Profiler_Host_Deinitialize_Params deinitializeParams = {CUpti_Profiler_Host_Deinitialize_Params_STRUCT_SIZE};
	deinitializeParams.pHostObject = pHostObject;
	cuptiProfilerHostDeinitialize(&deinitializeParams);
	pHostObject = nullptr;
}

// Helper function to initialize PM Sampling
void InitializeAndEnablePmSampling(int deviceIndex)
{
	// Initialize CUPTI Profiler
	CUpti_Profiler_Initialize_Params profilerInitializeParams = { CUpti_Profiler_Initialize_Params_STRUCT_SIZE };
	cuptiProfilerInitialize(&profilerInitializeParams);

	CUpti_Device_GetChipName_Params getChipNameParams = { CUpti_Device_GetChipName_Params_STRUCT_SIZE };
	getChipNameParams.deviceIndex = deviceIndex;
	cuptiDeviceGetChipName(&getChipNameParams);
	g_chipName = getChipNameParams.pChipName;
	printf("Chip Name: %s\n", g_chipName.c_str());

	// Enable PM sampling
	CUpti_PmSampling_Enable_Params enableParams = { CUpti_PmSampling_Enable_Params_STRUCT_SIZE };
	enableParams.deviceIndex = deviceIndex;
	cuptiPmSamplingEnable(&enableParams);
	g_pPmSamplingObject = enableParams.pPmSamplingObject;
}

void ConfigurePmSampling(uint64_t hardwareBufferSize, uint64_t samplingInterval)
{
	// Need to create the config image which will have the scheduling information for the metrics
	CreateConfigImage();

	// Set configuration
	CUpti_PmSampling_SetConfig_Params setConfigParams = { CUpti_PmSampling_SetConfig_Params_STRUCT_SIZE };
	setConfigParams.pPmSamplingObject = g_pPmSamplingObject;
	setConfigParams.configSize = g_configImage.size();
	setConfigParams.pConfig = g_configImage.data();
	setConfigParams.hardwareBufferSize = hardwareBufferSize;
	setConfigParams.samplingInterval = samplingInterval;
	setConfigParams.triggerMode = CUPTI_PM_SAMPLING_TRIGGER_MODE_GPU_SYSCLK_INTERVAL;
	cuptiPmSamplingSetConfig(&setConfigParams);
}

// Helper function to start PM sampling
void StartPmSampling()
{
	CUpti_PmSampling_Start_Params startParams = { CUpti_PmSampling_Start_Params_STRUCT_SIZE };
	startParams.pPmSamplingObject = g_pPmSamplingObject;
	cuptiPmSamplingStart(&startParams);
}

// Helper function to stop PM sampling
void StopPmSampling()
{
	CUpti_PmSampling_Stop_Params stopParams = { CUpti_PmSampling_Stop_Params_STRUCT_SIZE };
	stopParams.pPmSamplingObject = g_pPmSamplingObject;
	cuptiPmSamplingStop(&stopParams);
}

// Helper function to create counter data image
void CreateCounterDataImage(uint64_t maxSamplesInCounterDataImage)
{
	CUpti_PmSampling_GetCounterDataSize_Params getCounterDataSizeParams = { CUpti_PmSampling_GetCounterDataSize_Params_STRUCT_SIZE };
	getCounterDataSizeParams.pPmSamplingObject = g_pPmSamplingObject;
	getCounterDataSizeParams.numMetrics = g_metrics.size();
	getCounterDataSizeParams.pMetricNames = g_metrics.data();
	getCounterDataSizeParams.maxSamples = maxSamplesInCounterDataImage;
	cuptiPmSamplingGetCounterDataSize(&getCounterDataSizeParams);

	g_counterDataImage.resize(getCounterDataSizeParams.counterDataSize);
	CUpti_PmSampling_CounterDataImage_Initialize_Params initializeParams = { CUpti_PmSampling_CounterDataImage_Initialize_Params_STRUCT_SIZE };
	initializeParams.pPmSamplingObject = g_pPmSamplingObject;
	initializeParams.counterDataSize = g_counterDataImage.size();
	initializeParams.pCounterData = g_counterDataImage.data();
	cuptiPmSamplingCounterDataImageInitialize(&initializeParams);
}

// Helper function to decode and print sampling data
void DecodeAndPrintSamplingData()
{
	// Create counter data image which will store the decoded data from the hardware buffer
	constexpr uint64_t maxSamplesInCounterDataImage = 10000;
	CreateCounterDataImage(maxSamplesInCounterDataImage);

	// Decode sampling data
	CUpti_PmSampling_DecodeData_Params decodeParams = { CUpti_PmSampling_DecodeData_Params_STRUCT_SIZE };
	decodeParams.pPmSamplingObject = g_pPmSamplingObject;
	decodeParams.pCounterDataImage = g_counterDataImage.data();
	decodeParams.counterDataImageSize = g_counterDataImage.size();
	cuptiPmSamplingDecodeData(&decodeParams);

	// Get information about decoded data
	CUpti_PmSampling_GetCounterDataInfo_Params counterDataInfo = { CUpti_PmSampling_GetCounterDataInfo_Params_STRUCT_SIZE };
	counterDataInfo.pCounterDataImage = g_counterDataImage.data();
	counterDataInfo.counterDataImageSize = g_counterDataImage.size();
	cuptiPmSamplingGetCounterDataInfo(&counterDataInfo);
	printf("Number of completed samples: %zu\n", counterDataInfo.numCompletedSamples);

	// Print sample information (first 10 samples)
	size_t maxSamplesToShow = (counterDataInfo.numCompletedSamples > 10) ? 10 : counterDataInfo.numCompletedSamples;
	EvaluateAndPrintAllSamples(maxSamplesToShow);
}

void CleanupPmSampling()
{
	// Disable PM sampling
	CUpti_PmSampling_Disable_Params disableParams = { CUpti_PmSampling_Disable_Params_STRUCT_SIZE };
	disableParams.pPmSamplingObject = g_pPmSamplingObject;
	cuptiPmSamplingDisable(&disableParams);

	// Deinitialize profiler
	CUpti_Profiler_DeInitialize_Params profilerDeInitializeParams = { CUpti_Profiler_DeInitialize_Params_STRUCT_SIZE };
	cuptiProfilerDeInitialize(&profilerDeInitializeParams);
}

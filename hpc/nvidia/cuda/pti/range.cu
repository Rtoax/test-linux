/**
 * ref: https://docs.nvidia.com/cupti/tutorial/tutorial.html
 */
#include <stdio.h>
#include <vector>
#include <cupti.h>
#include <cupti_profiler_target.h>
#include <cupti_target.h>
#if CUDA_VERSION > 12040
# include <cupti_pmsampling.h>
# include <cupti_profiler_host.h>
# include <cupti_range_profiler.h>
#endif
#include "cuda_helpers.h"


// Global variables for Range Profiler
CUpti_RangeProfiler_Object* g_pRangeProfilerObject = NULL;

std::vector<uint8_t> g_counterDataImage;
std::vector<uint8_t> g_configImage;

CUcontext g_cuContext;
std::string g_chipName;

std::vector<const char*> g_metrics = {
	"sm__warps_launched.sum",	// Number of warps launched
	"sm__ctas_launched.sum"
};

// CUDA kernel for vector addition
__global__ void VectorAdd(const float *A, const float *B, float *C, int N)
{
	int idx = blockIdx.x * blockDim.x + threadIdx.x;
	if (idx < N)
		C[idx] = A[idx] + B[idx];
}

// Helper function declarations
void InitializeAndEnableRangeProfiler(CUcontext cuContext);
void ConfigureRangeProfiler(CUpti_ProfilerRange range, CUpti_ProfilerReplayMode replayMode, size_t numOfRanges);
void StartRangeProfiler();
void StopRangeProfiler();
void DecodeAndPrintProfilingData();
void CleanupRangeProfiler();

int main()
{
	const int vectorLen = 1024 * 1024;
	const size_t size = vectorLen * sizeof(float);

	// Initialize CUDA and create context
	cuInit(0);
	cuCtxCreate(&g_cuContext, (CUctxCreateParams*)0, 0, 0);

	// Initialize and Enable Range Profiler
	InitializeAndEnableRangeProfiler(g_cuContext);

	// Configure Range Profiler
	constexpr size_t numOfRanges = 10;
	ConfigureRangeProfiler(CUPTI_AutoRange, CUPTI_KernelReplay, numOfRanges);

	// Setup CUDA workload
	float *h_A = (float*)malloc(size);
	float *h_B = (float*)malloc(size);
	float *h_C = (float*)malloc(size);

	for (int i = 0; i < vectorLen; ++i) {
		h_A[i] = rand() / (float)RAND_MAX;
		h_B[i] = rand() / (float)RAND_MAX;
	}

	float *d_A, *d_B, *d_C;
	cudaMalloc((void **)&d_A, size);
	cudaMalloc((void **)&d_B, size);
	cudaMalloc((void **)&d_C, size);

	cudaMemcpy(d_A, h_A, size, cudaMemcpyHostToDevice);
	cudaMemcpy(d_B, h_B, size, cudaMemcpyHostToDevice);

	int threadsPerBlock = 128;
	int blocksPerGrid = (vectorLen + threadsPerBlock - 1) / threadsPerBlock;

	// Start Range Profiling
	StartRangeProfiler();

	// Launch CUDA workload
	VectorAdd<<<blocksPerGrid, threadsPerBlock>>>(d_A, d_B, d_C, vectorLen);

	// Stop Range Profiling
	StopRangeProfiler();

	// Decode and evaluate profiling data
	DecodeAndPrintProfilingData();

	// Cleanup Range Profiler
	CleanupRangeProfiler();

	cudaMemcpy(h_C, d_C, size, cudaMemcpyDeviceToHost);
	cudaDeviceSynchronize();

	// Cleanup
	cudaFree(d_A); cudaFree(d_B); cudaFree(d_C);
	free(h_A); free(h_B); free(h_C);
	return 0;
}

void CreateConfigImage()
{
	CUpti_Profiler_Host_Initialize_Params hostInitializeParams = {CUpti_Profiler_Host_Initialize_Params_STRUCT_SIZE};
	hostInitializeParams.profilerType = CUPTI_PROFILER_TYPE_RANGE_PROFILER;
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

void EvaluateAndPrintForRange(size_t rangeIndex, CUpti_Profiler_Host_Object* pHostObject)
{
	std::vector<double> metricValues(g_metrics.size());
	CUpti_Profiler_Host_EvaluateToGpuValues_Params evalauateToGpuValuesParams {CUpti_Profiler_Host_EvaluateToGpuValues_Params_STRUCT_SIZE};
	evalauateToGpuValuesParams.pHostObject = pHostObject;
	evalauateToGpuValuesParams.pCounterDataImage = g_counterDataImage.data();
	evalauateToGpuValuesParams.counterDataImageSize = g_counterDataImage.size();
	evalauateToGpuValuesParams.ppMetricNames = g_metrics.data();
	evalauateToGpuValuesParams.numMetrics = g_metrics.size();
	evalauateToGpuValuesParams.rangeIndex = rangeIndex;
	evalauateToGpuValuesParams.pMetricValues = metricValues.data();
	cuptiProfilerHostEvaluateToGpuValues(&evalauateToGpuValuesParams);

	for (size_t i = 0; i < g_metrics.size(); ++i) {
		printf("\t%s: %f\n", g_metrics[i], metricValues[i]);
	}
	printf("\n");
}

void EvaluateAndPrintAllRanges(size_t numOfRanges)
{
	CUpti_Profiler_Host_Initialize_Params hostInitializeParams = {CUpti_Profiler_Host_Initialize_Params_STRUCT_SIZE};
	hostInitializeParams.profilerType = CUPTI_PROFILER_TYPE_RANGE_PROFILER;
	hostInitializeParams.pChipName = g_chipName.c_str();
	hostInitializeParams.pCounterAvailabilityImage = nullptr;
	cuptiProfilerHostInitialize(&hostInitializeParams);
	CUpti_Profiler_Host_Object* pHostObject = hostInitializeParams.pHostObject;

	for (size_t i = 0; i < numOfRanges; ++i)
	{
		CUpti_RangeProfiler_CounterData_GetRangeInfo_Params getRangeInfoParams = {CUpti_RangeProfiler_CounterData_GetRangeInfo_Params_STRUCT_SIZE};
		getRangeInfoParams.counterDataImageSize = g_counterDataImage.size();
		getRangeInfoParams.pCounterDataImage = g_counterDataImage.data();
		getRangeInfoParams.rangeIndex = i;
		getRangeInfoParams.rangeDelimiter = "/";
		cuptiRangeProfilerCounterDataGetRangeInfo(&getRangeInfoParams);

		printf("Range: %s\n", getRangeInfoParams.rangeName);
		printf("Metric Values:\n");
		EvaluateAndPrintForRange(i, pHostObject);
	}

	CUpti_Profiler_Host_Deinitialize_Params deinitializeParams = {CUpti_Profiler_Host_Deinitialize_Params_STRUCT_SIZE};
	deinitializeParams.pHostObject = pHostObject;
	cuptiProfilerHostDeinitialize(&deinitializeParams);
	pHostObject = nullptr;
}

void InitializeAndEnableRangeProfiler(CUcontext cuContext)
{
	// Initialize CUPTI Profiler
	CUpti_Profiler_Initialize_Params profilerInitializeParams = { CUpti_Profiler_Initialize_Params_STRUCT_SIZE };
	cuptiProfilerInitialize(&profilerInitializeParams);

	CUdevice device;
	cuCtxGetDevice(&device);
	CUpti_Device_GetChipName_Params getChipNameParams = { CUpti_Device_GetChipName_Params_STRUCT_SIZE };
	getChipNameParams.deviceIndex = (size_t)device;
	cuptiDeviceGetChipName(&getChipNameParams);
	g_chipName = std::string(getChipNameParams.pChipName);
	printf("Chip Name: %s\n", g_chipName.c_str());

	// Enable Range profiler
	CUpti_RangeProfiler_Enable_Params enableRange = { CUpti_RangeProfiler_Enable_Params_STRUCT_SIZE };
	enableRange.ctx = cuContext;
	cuptiRangeProfilerEnable(&enableRange);
	g_pRangeProfilerObject = enableRange.pRangeProfilerObject;
}

void CreateCounterDataImage(size_t maxNumOfRangesInCounterDataImage)
{
	// Get counter data size
	CUpti_RangeProfiler_GetCounterDataSize_Params ctDataSize = { CUpti_RangeProfiler_GetCounterDataSize_Params_STRUCT_SIZE };
	ctDataSize.pRangeProfilerObject = g_pRangeProfilerObject;
	ctDataSize.pMetricNames = g_metrics.data();
	ctDataSize.numMetrics = g_metrics.size();
	ctDataSize.maxNumOfRanges = maxNumOfRangesInCounterDataImage;
	ctDataSize.maxNumRangeTreeNodes = maxNumOfRangesInCounterDataImage;
	cuptiRangeProfilerGetCounterDataSize(&ctDataSize);

	// Initialize counter data image
	g_counterDataImage.resize(ctDataSize.counterDataSize);
	CUpti_RangeProfiler_CounterDataImage_Initialize_Params initCtImg = { CUpti_RangeProfiler_CounterDataImage_Initialize_Params_STRUCT_SIZE };
	initCtImg.pRangeProfilerObject = g_pRangeProfilerObject;
	initCtImg.pCounterData = g_counterDataImage.data();
	initCtImg.counterDataSize = g_counterDataImage.size();
	cuptiRangeProfilerCounterDataImageInitialize(&initCtImg);
}

void ConfigureRangeProfiler(CUpti_ProfilerRange range, CUpti_ProfilerReplayMode replayMode, size_t numOfRanges)
{
	// Create config image
	CreateConfigImage();

	// Create counter data image
	CreateCounterDataImage(numOfRanges);

	CUpti_RangeProfiler_SetConfig_Params setConfig = { CUpti_RangeProfiler_SetConfig_Params_STRUCT_SIZE };
	setConfig.pRangeProfilerObject = g_pRangeProfilerObject;
	setConfig.configSize = g_configImage.size();
	setConfig.pConfig = g_configImage.data();
	setConfig.counterDataImageSize = g_counterDataImage.size();
	setConfig.pCounterDataImage = g_counterDataImage.data();
	setConfig.range = range;
	setConfig.replayMode = replayMode;
	setConfig.maxRangesPerPass = numOfRanges;
	setConfig.numNestingLevels = 1;
	setConfig.minNestingLevel = 1;
	setConfig.passIndex = 0;
	setConfig.targetNestingLevel = 0;
	cuptiRangeProfilerSetConfig(&setConfig);
}

void StartRangeProfiler()
{
	CUpti_RangeProfiler_Start_Params startRangeProfiler = { CUpti_RangeProfiler_Start_Params_STRUCT_SIZE };
	startRangeProfiler.pRangeProfilerObject = g_pRangeProfilerObject;
	cuptiRangeProfilerStart(&startRangeProfiler);
}

void StopRangeProfiler()
{
	CUpti_RangeProfiler_Stop_Params stopRangeProfiler = { CUpti_RangeProfiler_Stop_Params_STRUCT_SIZE };
	stopRangeProfiler.pRangeProfilerObject = g_pRangeProfilerObject;
	cuptiRangeProfilerStop(&stopRangeProfiler);
}

void DecodeAndPrintProfilingData()
{
	// Decode profiling data
	CUpti_RangeProfiler_DecodeData_Params decodeData = { CUpti_RangeProfiler_DecodeData_Params_STRUCT_SIZE };
	decodeData.pRangeProfilerObject = g_pRangeProfilerObject;
	cuptiRangeProfilerDecodeData(&decodeData);

	// Get information about profiled ranges
	CUpti_RangeProfiler_GetCounterDataInfo_Params cdiParams = { CUpti_RangeProfiler_GetCounterDataInfo_Params_STRUCT_SIZE };
	cdiParams.pCounterDataImage = g_counterDataImage.data();
	cdiParams.counterDataImageSize = g_counterDataImage.size();
	cuptiRangeProfilerGetCounterDataInfo(&cdiParams);
	printf("Number of profiled ranges: %zu\n", cdiParams.numTotalRanges);

	// Evaluate and print profiling data
	const size_t numRangesToPrint = cdiParams.numTotalRanges > 10 ? 10 : cdiParams.numTotalRanges;
	EvaluateAndPrintAllRanges(numRangesToPrint);
}

void CleanupRangeProfiler()
{
	// Disable Range profiler
	CUpti_RangeProfiler_Disable_Params disableRangeProfiler = { CUpti_RangeProfiler_Disable_Params_STRUCT_SIZE };
	disableRangeProfiler.pRangeProfilerObject = g_pRangeProfilerObject;
	cuptiRangeProfilerDisable(&disableRangeProfiler);

	// Deinitialize profiler
	CUpti_Profiler_DeInitialize_Params profilerDeInitializeParams = { CUpti_Profiler_DeInitialize_Params_STRUCT_SIZE };
	cuptiProfilerDeInitialize(&profilerDeInitializeParams);
}

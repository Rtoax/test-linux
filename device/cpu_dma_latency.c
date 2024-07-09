/**
 * 控制电源管理过渡
 * 现代处理器积极地从较低的状态过渡到较高的节能状态（C状态）。不幸的是，从高省
 * 电状态过渡到运行状态可能会花费比实时应用最佳的时间。为了防止这些过渡，应用
 * 程序可以使用电源管理服务质量（PM QoS）接口。
 *
 * 使用PM QoS接口，系统可以模拟 idle=poll 和 processor.max_cstate=1 参数的行为
 * （如“为TSC时钟配置其他启动参数”中所列），但可以更精细地控制省电状态。
 *
 * 当应用程序使/dev/cpu_dma_latency文件保持打开状态时，PM QoS接口可防止处理器
 * 进入深度睡眠状态，这将在退出深度睡眠状态时引起意外延迟。关闭文件后，系统将
 * 返回节能状态。
 *
 * 打开/dev/cpu_dma_latency文件。在低延迟操作期间，请保持文件描述符处于打开状态。
 * 给它写一个32位数字。该数字表示最大响应时间（以微秒为单位）。要获得最快的响应
 * 时间，请使用0。
 */
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>


static int pm_qos_fd = -1;

void start_low_latency(void)
{
	int32_t target = 0;

	if (pm_qos_fd >= 0)
		return;
	pm_qos_fd = open("/dev/cpu_dma_latency", O_RDWR);
	if (pm_qos_fd < 0) {
		fprintf(stderr, "Failed to open PM QOS file: %s",
			strerror(errno));
		exit(errno);
	}
	write(pm_qos_fd, &target, sizeof(target));
}

void stop_low_latency(void)
{
	if (pm_qos_fd >= 0)
		close(pm_qos_fd);
}

int main(void)
{
	return 0;
}

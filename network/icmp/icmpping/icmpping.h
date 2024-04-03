/**
 *  实现 ICMP ping功能，检测 目的 IP地址通路，并计算时延
 *  
 *  作者： 荣涛
 *  日期： 2020年10月12日
 */
#ifndef __ICMP_PING_H
#define __ICMP_PING_H 1

/* icmp_ping 返回值 */
#define ICMPPING_SUCC   0   /* 成功 */
#define ICMPPING_FAIL   1   /* 失败 */

/**
 *  icmp_ping   - icmp ping
 *  
 *  param[in]   ipv4:       目的IPv4地址
 *  param[in]   timeout:    超时设置，若超出设定值，且ping不通情况下，函数自动返回
 *  param[in]   ntry:       ping的次数，发 req包数量
 *  param[in]   log:        打印调试信息，若为 NULL则不打印
 *  param[in]   latency:    计算平均时延，单位 微妙 micro second（参见结构 struct timeval）
 *                          该参数 填 NULL 时，不计算时延
 *
 *  return  成功返回 ICMPPING_SUCC， 失败返回 ICMPPING_FAIL
 */
int icmp_ping(const char *ipv4, unsigned int timeout, int ntry, 
                int (*log)(const char *fmt, ...), long int *latency);


#endif /*<__ICMP_PING_H>*/

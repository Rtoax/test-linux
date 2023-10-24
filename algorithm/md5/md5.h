#ifndef MD5_H
#define MD5_H

typedef struct
{
	unsigned int count[2];
	unsigned int state[4];
	unsigned char buffer[64];
} MD5_CTX;


#define F(x,y,z) ((x & y) | (~x & z))
#define G(x,y,z) ((x & z) | (y & ~z))
#define H(x,y,z) (x^y^z)
#define I(x,y,z) (y ^ (x | ~z))
#define ROTATE_LEFT(x,n) ((x << n) | (x >> (32-n)))
#define FF(a,b,c,d,x,s,ac) \
		{ \
		a += F(b,c,d) + x + ac; \
		a = ROTATE_LEFT(a,s); \
		a += b; \
		}
#define GG(a,b,c,d,x,s,ac) \
		{ \
		a += G(b,c,d) + x + ac; \
		a = ROTATE_LEFT(a,s); \
		a += b; \
		}
#define HH(a,b,c,d,x,s,ac) \
		{ \
		a += H(b,c,d) + x + ac; \
		a = ROTATE_LEFT(a,s); \
		a += b; \
		}
#define II(a,b,c,d,x,s,ac) \
		{ \
		a += I(b,c,d) + x + ac; \
		a = ROTATE_LEFT(a,s); \
		a += b; \
		}

/********************************************************
* 名    称: MD5Init()
* 功    能: 初始化MD5结构体
* 入口参数:
   context：要初始化的MD5结构体
* 出口参数: 无
*********************************************************/
void MD5Init(MD5_CTX *context);

/*********************************************************
* 名    称: MD5Update()
* 功    能: 将要加密的信息传递给初始化过的MD5结构体，无返回值
* 入口参数:
   context：初始化过了的MD5结构体
	input：需要加密的信息，可以任意长度
	inputLen：指定input的长度
* 出口参数: 无
*********************************************************/
void MD5Update(MD5_CTX *context,unsigned char *input,unsigned int inputlen);

/*********************************************************
* 名    称: MD5Update()
* 功    能: 将加密结果存储到，无返回值
* 入口参数:
   context：初始化过了的MD5结构体
	digest ：加密过的结果
* 出口参数: 无
*********************************************************/
void MD5Final(MD5_CTX *context,unsigned char digest[16]);
void MD5Transform(unsigned int state[4],unsigned char block[64]);
void MD5Encode(unsigned char *output,unsigned int *input,unsigned int len);
void MD5Decode(unsigned int *output,unsigned char *input,unsigned int len);

#endif
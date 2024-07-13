//int ASN1_parse_dump(BIO *bp, const unsigned char *pp, long len, int indent, int dump)
//本函数用于将pp 和len 指明的DER 编码值写在BIO 中，其中indent 和dump 用于
//设置打印的格式。indent 用来设置打印出来当列之间空格个数，ident 越小，打印内容越
//紧凑。dump 表明当asn1 单元为BIT STRING 或OCTET STRING 时，打印内容的字节
//数。示例如下：
//其中der.cer 为一个DER 编码的文件，比如一个数字证书。
#include <openssl/bio.h>
#include <openssl/asn1.h>

int main(void)
{
	int ret,len,indent,dump;
	BIO *bp;
	char *pp,buf[5000];
	FILE *fp;
	bp=BIO_new(BIO_s_file());
	BIO_set_fp(bp,stdout,BIO_NOCLOSE);
	fp=fopen("der.cer","rb");
	len=fread(buf,1,5000,fp);
	fclose(fp);
	pp=buf;
	indent=7;
	dump=11;
	ret=ASN1_parse_dump(bp,pp,len,indent,dump);
	BIO_free(bp);
	return 0;
}


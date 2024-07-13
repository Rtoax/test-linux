// 设置ASN1_STRING_set_by_NID 函数返回的ASN1_STRING 类型。mask 可以取如
// 下值： B_ASN1_BMPSTRING 、B_ASN1_UTF8STRING 、B_ASN1_T61STRING 和
// B_ASN1_UTF8STRING。
#include <stdio.h>
#include <string.h>
#include <openssl/asn1.h>
#include <openssl/obj_mac.h>

int main(void)
{
	int inlen,nid,inform,len;
	char in[100],out[100];
	unsigned char *p;
	ASN1_STRING *a;
	FILE *fp;

	strcpy(in,"ab");
	inlen=2;
	inform=MBSTRING_ASC;
	nid=NID_commonName;

	/* 设置生成的ASN1_STRING类型 */
	ASN1_STRING_set_default_mask(B_ASN1_UTF8STRING);
	a=ASN1_STRING_set_by_NID(NULL,in,inlen,inform,nid);
	switch (a->type) {
	case V_ASN1_T61STRING:
		printf("V_ASN1_T61STRING\n");
		break;
	case V_ASN1_IA5STRING:
		printf("V_ASN1_IA5STRING\n");
		break;
	case V_ASN1_PRINTABLESTRING:
		printf("V_ASN1_PRINTABLESTRING\n");
		break;
	case V_ASN1_BMPSTRING:
		printf("V_ASN1_BMPSTRING\n");
		break;
	case V_ASN1_UNIVERSALSTRING:
		printf("V_ASN1_UNIVERSALSTRING\n");
		break;
	case V_ASN1_UTF8STRING:
		printf("V_ASN1_UTF8STRING\n");
		break;
	default:
		printf("err");
		break;
	}
	p=out;
	len=i2d_ASN1_bytes(a,&p,a->type,V_ASN1_UNIVERSAL);
	fp=fopen("a.cer","w");
	fwrite(out,1,len,fp);
	fclose(fp);
	ASN1_STRING_free(a);
	getchar();
	return 0;
}
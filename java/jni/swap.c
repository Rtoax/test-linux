#include <jni.h>
#include <stdbool.h>
#include <unistd.h>
#include "swap.h"


void swap_float_4(float *tnf4)
{
	int *tni4=(int *)tnf4;
	*tni4 = (((*tni4>>24)&0xff) | ((*tni4&0xff)<<24) |
			((*tni4>>8)&0xff00) | ((*tni4&0xff00)<<8));
}

JNIEXPORT void JNICALL
Java_swap_swapFloatFile(JNIEnv *env, jclass cla, jstring in, jstring out)
{
	char *FN1;
	char *FN2;
	float val;
	FILE *fp1, *fp2;

	FN1 = (char*)(*env)->GetStringUTFChars(env, in, NULL);
	FN2 = (char*)(*env)->GetStringUTFChars(env, out, NULL);

	printf("FN1 = %s, FN2 = %s\n", FN1, FN2);

	fp1=fopen(FN1, "rb");
	fp2=fopen(FN2, "wb");

	for (;;) {
		if (fread(&val, sizeof(float), 1, fp1) == 0)
			break;

		swap_float_4(&val);
		fwrite(&val, sizeof(float), 1, fp2);
	}

	fclose(fp1);
	fclose(fp2);
}

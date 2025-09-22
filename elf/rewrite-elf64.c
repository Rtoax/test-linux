#include <elf.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	Elf64_Ehdr ehdr;

	if (argc < 3) {
		printf("Usage: %s [in] [out]\n", argv[0]);
		exit(1);
	}

	FILE *fpin = fopen(argv[1], "r");
	FILE *fpout = fopen(argv[2], "w");


	fread(&ehdr, sizeof(ehdr), 1, fpin);

	ehdr.e_machine = EM_AMDGPU;

	fwrite(&ehdr, sizeof(ehdr), 1, fpout);

	for (;!feof(fpin);) {
		char ch;
		fread(&ch, 1, 1, fpin);
		fwrite(&ch, 1, 1, fpout);
	}

	fclose(fpin);
	fclose(fpout);
}

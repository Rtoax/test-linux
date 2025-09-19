#include <elf.h>
#include <stdio.h>

int main(void)
{
	Elf64_Ehdr ehdr;

	FILE *fpin = fopen("parallel.hc_fatbin.elf", "r");
	FILE *fpout = fopen("parallel.hc_fatbin.elf.amdgpu", "w");


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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "exe.h"

int patch_executable() {
	FILE *input_f = fopen("BattleTraverse.exe", "rb");
	if (!input_f) {
		printf("ERROR: Could not find BattleTraverse.exe in the current working directory.\n");
		return -1;
	}
	
	//Read executable to memory
	struct stat st;
	fstat(fileno(input_f), &st);
	unsigned char *buf = malloc(st.st_size);
	fread(buf, st.st_size, 1, input_f);
	
	//Perform patching
	int list_len = sizeof(str_list) / sizeof(struct EX_PATCH);
	for (int i=0; i<list_len; i++) {
		struct EX_PATCH s = str_list[i];
		switch (s.type) {
			case EP_STR:
				memcpy(buf+s.pos, s.data.sval, strlen(s.data.sval)+1);
				break;
			case EP_PTR: {
				uint32_t epos = s.data.ival + 0x400000;
				memcpy(buf+s.pos, &epos, sizeof(uint32_t));
				}
				break;
			case EP_INT:
				memcpy(buf+s.pos, &s.data.ival, sizeof(uint32_t));
				break;
			case EP_BYTE:
				memcpy(buf+s.pos, &s.data.ival, sizeof(uint8_t));
				break;
			case EP_DOUBLE:
				memcpy(buf+s.pos, &s.data.dval, sizeof(double));
				break;
		}
	}
	
	//Output patched executable
	FILE *output_f = fopen("BattleTraverse_EN.exe", "wb");
	fwrite(buf, st.st_size, 1, output_f);
	free(output_f);
	
	//Clean
	free(buf);
	fclose(input_f);
	return 0;
}
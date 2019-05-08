//English patch for BATTLE TRAVERSE
//Written by YAM, July 2018

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <sys/stat.h>

/*
 * String patching
 */
typedef struct EX_STRING {
	uint32_t pos;		//String location in executable
	const char *str;	//String to insert (NULL to only perform relocation)
	uint32_t ptr_pos;	//Pointer location in executable (zero if no relocation is necessary)
} ExStr;

//Load string list from macro file
static ExStr str_list[] = {
	#define str(pos, string) {pos, string, 0},
	#define rloc(pos, ptr) {pos, NULL, ptr},
	#define str_rloc(pos, string, ptr) {pos, string, ptr},
	#include "btrav.inc"
	#undef str_rloc
	#undef rloc
	#undef str
};

int patch_strings() {
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
	
	//Replace strings
	int list_len = sizeof(str_list) / sizeof(struct EX_STRING);
	for (int i=0; i<list_len; i++) {
		ExStr s = str_list[i];
		if (s.str != NULL)
			memcpy(buf+s.pos, s.str, strlen(s.str)+1);
		
		//Relocate
		if (s.ptr_pos != 0) {
			uint32_t epos = s.pos + 0x400000;
			memcpy(buf+s.ptr_pos, &epos, sizeof(uint32_t));
		}
	}
	
	//Output patched executable
	FILE *output_f = fopen("BattleTraverse_EN.exe", "wb");
	fwrite(buf, st.st_size, 1, output_f);
	free(output_f);
	
	free(buf);
	fclose(input_f);
}

/*
 * Image patching
 */
static unsigned char *dxa_key = "\x8E\x47\xEB\xD8\x90\x9C\xCE\xD1\xA3\x1E\xF1\xA3";
struct DXA_HEAD {
	uint16_t id;		//ID
	uint16_t ver;		//Version
	uint32_t ft_len;	//Total length of filename, file, and directory tables

	uint32_t data_start;	//Location of file data
	uint32_t ntable_start;	//Location of filename table
	uint32_t ftable_start;	//Location of file table (offset from filename table position)
	uint32_t dtable_start;	//Location of directory table (offset from filename table position)
	
	uint32_t ccode_fmt;	//Encoding used by filenames
};

struct DXA_FILE {
	const char *fname;
	const unsigned char *data;
	unsigned int data_len;
	unsigned int pos;
	unsigned int fn_pos;
};

//Set up data for en01.dxa
#define img(fname, sym) \
	extern const char sym##_start; \
	extern const int sym##_size;
#include "img/en01.inc"
#undef img
static struct DXA_FILE en01_list[] = {
	#define img(fname, sym) {fname, &sym##_start, (int)&sym##_size, 0, 0},
	#include "img/en01.inc"
	#undef img
};

//Wrapper function for fread
size_t fwrite_enc(const void *ptr, size_t size, size_t nmemb, FILE *stream) {
	//Buffer for holding data to be encrypted
	//Automatically resized, freed when function is called with NULL as stream
	static unsigned char *buf = NULL;
	static unsigned int buf_size = 0;
	if (!stream) {
		if (!buf)
			free(buf);
		buf = NULL;
		buf_size = 0;
		return 0;
	}
	
	//Resize buffer if necessary
	if (!buf) {
		buf = malloc(size);
		buf_size = size;
	} else {
		if (size > buf_size) {
			buf = realloc(buf, size);
			buf_size = size;
		}
	}
	
	//Copy and encrypt data
	int pos = ftell(stream);
	memcpy(buf, ptr, size);
	for (int i=0; i<size; i++)
		buf[i] ^= dxa_key[(pos+i)%12];

	//Write data
	return fwrite(buf, size, nmemb, stream);
}

//Wrapper function for fputc
int fputc_enc(int c, FILE *stream) {
	fputc(dxa_key[ftell(stream)%12], stream);
}

int patch_images() {
	struct DXA_HEAD hdr = {0x5844, 0x04, 0, 0, 0, 0, 0, 0x3A4};
	
	//Open archive and write empty header
	FILE *output_f = fopen("data/en01.dxa", "wb");
	fwrite_enc(&hdr, sizeof(hdr), 1, output_f);
	
	//Write file data
	hdr.data_start = ftell(output_f);
	int list_len = sizeof(en01_list) / sizeof(struct DXA_FILE);
	for (int i=0; i<list_len; i++) {
		en01_list[i].pos = ftell(output_f) - hdr.data_start;
		fwrite_enc(en01_list[i].data, en01_list[i].data_len, 1, output_f);
		for (int j=0; j<ftell(output_f)%4; j++) //alignment
			fputc_enc('\x00', output_f); 
	}
	
	//Write filename table
	hdr.ntable_start = ftell(output_f);
	for (int i=0; i<4; i++)
		fputc_enc('\x00', output_f);
	for (int i=0; i<list_len; i++) {
		en01_list[i].fn_pos = ftell(output_f) - hdr.ntable_start;
		
		//Create an uppercase copy of the filename
		int fn_len = strlen(en01_list[i].fname);
		char fn_ucase[fn_len+1];
		for (int j=0; j<fn_len; j++)
			fn_ucase[j] = toupper(en01_list[i].fname[j]);
		fn_ucase[fn_len] = '\0';
		
		//Calculate parity and filename length in 4-byte chunks
		uint16_t fnc_len = (fn_len + 4) / 4;
		uint16_t parity = 0;
		for (int j=0; j<fn_len; j++)
			parity += fn_ucase[j];
		fwrite_enc(&fnc_len, 2, 1, output_f);
		fwrite_enc(&parity, 2, 1, output_f);

		//Write uppercase and lowercase filenames
		fwrite_enc(fn_ucase, fn_len, 1, output_f);
		for (int j=0; j<fnc_len*4-fn_len; j++)
			fputc_enc('\x00', output_f);
		fwrite_enc(en01_list[i].fname, fn_len, 1, output_f);
		for (int j=0; j<fnc_len*4-fn_len; j++)
			fputc_enc('\x00', output_f);
	}
	
	//Write file table
	hdr.ftable_start = ftell(output_f) - hdr.ntable_start;
	uint32_t base_entry[11] = {0, 16, 0, 0, 0, 0, 0, 0, 0, 0, -1};
	for (int i=0; i<11; i++)
		fwrite_enc(base_entry+i, 4, 1, output_f);
	for (int i=0; i<list_len; i++) {
		fwrite_enc(&en01_list[i].fn_pos, 4, 1, output_f);	//Filename position
		fwrite_enc("\x20\x00\x00\x00", 4, 1, output_f);		//Attributes (0x20 -> file)
		for (int j=0; j<0x18; j++)				//Time
			fputc_enc('\x00', output_f);
		fwrite_enc(&en01_list[i].pos, 4, 1, output_f);		//Data position
		fwrite_enc(&en01_list[i].data_len, 4, 1, output_f);	//Data length
		fwrite_enc("\xFF\xFF\xFF\xFF", 4, 1, output_f);		//Compression?
	}
	
	//Write directory table
	hdr.dtable_start = ftell(output_f) - hdr.ntable_start;		
	uint32_t base_dir[4] = {0, -1, list_len, 44};
	for (int i=0; i<4; i++)
		fwrite_enc(base_dir+i, 4, 1, output_f);
	
	//Write completed header
	hdr.ft_len = ftell(output_f) - hdr.ntable_start;
	fseek(output_f, 0, SEEK_SET);
	fwrite_enc(&hdr, sizeof(hdr), 1, output_f);
	
	//Close buffer and file
	fwrite_enc(NULL, 0, 0, NULL);
	fclose(output_f);
}

/*
 * Main
 */
int main(int argc, char **argv) {
	patch_strings();
	patch_images();
	
	return 0;
}
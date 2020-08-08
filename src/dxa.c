//English patch for BATTLE TRAVERSE
//Written by YAM, August 2020

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <sys/stat.h>
#include "dxa.h"

/* 
 * 12-byte key used to encrypt/decrypt the archives
 * derived from a password contained in the executable
 */
static unsigned char dxa_key[0xC];

/*
 * Wrapper functions for fwrite and fputc to use the archive's encryption
 */
size_t fwrite_enc(const void *ptr, size_t size, size_t nmemb, FILE *stream) {
	//Buffer for holding data to be encrypted
	//Automatically resized, freed when function is called with NULL as stream
	static unsigned char *buf = NULL;
	static unsigned int buf_size = 0;
	if (!stream) {
		if (buf)
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

int fputc_enc(int c, FILE *stream) {
	return fputc(dxa_key[ftell(stream)%12], stream);
}

/*
 * Reads the archive password from the executable and derives the encryption key from it
 */
#define PW_POS 0x00387A48
#define PW_LEN 0x7
#define ROL(v, n) (v << n) | (v >> 8-n)
#define ROR(v, n) (v >> n) | (v << 8-n)
int read_dxakey() {
	//Open the executable
	FILE *exe_f = fopen("BattleTraverse.exe", "rb");
	if (!exe_f) {
		printf("ERROR: Could not find BattleTraverse.exe in the current working directory.\n");
		return -1;
	}
	
	//Seek to and read the archive password
	fseek(exe_f, PW_POS, SEEK_SET);
	fread(dxa_key, PW_LEN, 1, exe_f);
	
	//Repeat the key until it is length 0xC
	for (int i=PW_LEN; i<0xC; i++)
		dxa_key[i] = dxa_key[i-PW_LEN];
	
	//Generate the key
	dxa_key[0x0] = ~dxa_key[0x0];
	dxa_key[0x1] = ROL(dxa_key[0x1], 4);
	dxa_key[0x2] ^= 0x8A;
	dxa_key[0x3] = ~(ROL(dxa_key[0x3], 4));
	dxa_key[0x4] = ~dxa_key[0x4];
	dxa_key[0x5] ^= 0xAC;
	dxa_key[0x6] = ~dxa_key[0x6];
	dxa_key[0x7] = ~(ROR(dxa_key[0x7], 3));
	dxa_key[0x8] = ROL(dxa_key[0x8], 3);
	dxa_key[0x9] ^= 0x7F;
	dxa_key[0xA] = ROL(dxa_key[0xA], 4) ^ 0xD6;
	dxa_key[0xB] ^= 0xCC;
	
	//Close the file
	fclose(exe_f);
	return 0;
}

/*
 * Performs data patching by creating a new data file to hold the translated data.
 * During executable patching, these files will be made to load from this new archive.
 */
int patch_archives() {
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
	return 0;
}
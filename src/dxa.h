//English patch for BATTLE TRAVERSE
//Written by YAM, May 2019

#ifndef DXA_H
#define DXA_H

//DXA archive header
struct DXA_HEAD {
	uint16_t id;			//ID
	uint16_t ver;			//Version
	uint32_t ft_len;		//Total length of filename, file, and directory tables

	uint32_t data_start;		//Location of file data
	uint32_t ntable_start;		//Location of filename table
	uint32_t ftable_start;		//Location of file table (offset from filename table position)
	uint32_t dtable_start;		//Location of directory table (offset from filename table position)
	
	uint32_t ccode_fmt;		//Encoding used by filenames
};

//DXA file entry
struct DXA_FILE {
	const char *fname;		//Name of the file
	const unsigned char *data;	//File data
	unsigned int data_len;		//Length of file data
	unsigned int pos;		//Position of data in archive
	unsigned int fn_pos;		//Position of filename in archive
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

//Function definitions
int read_dxakey();
int patch_archives();

#endif
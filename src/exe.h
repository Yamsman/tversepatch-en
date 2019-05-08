#ifndef EPATCH_H
#define EPATCH_H

#include <stdint.h>

enum EPATCH_TYPE {
	EP_STR,
	EP_PTR,
	EP_INT,
	EP_BYTE,
	EP_DOUBLE
};

//Holds a value for patching
struct EX_PATCH {
	uint32_t type;		//Type of patch
	uint32_t pos;		//Location in executable
	union {
		const char *sval;
		uint32_t ival;
		double dval;
	} data;			//Data to patch with
};

//Load string list from macro file
static struct EX_PATCH str_list[] = {
	#define str(pos, str) {EP_STR, pos, .data.sval = str},
	#define ptr(pos, ptr) {EP_PTR, pos, .data.ival = ptr},
	#define int(pos, val) {EP_INT, pos, .data.ival = val},
	#define byte(pos, val) {EP_BYTE, pos, .data.ival = val},
	#define double(pos, val) {EP_DOUBLE, pos, .data.dval = val},
	#include "btrav.inc"
	#undef double
	#undef byte
	#undef int
	#undef ptr
	#undef str
};

//Function definitions
int patch_executable();

#endif
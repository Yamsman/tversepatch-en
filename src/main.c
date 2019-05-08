//English patch for BATTLE TRAVERSE
//Written by YAM, May 2019

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <sys/stat.h>
#include "dxa.h"
#include "exe.h"

/*
 * Entry point
 */
int main(int argc, char **argv) {
	//Patch strings, addresses, etc in the executable
	patch_executable();
	
	//Get the archive key from the executable and use it to create a new
	//archive containing the english-translated images
	read_dxakey();
	patch_archives();
	
	return 0;
}
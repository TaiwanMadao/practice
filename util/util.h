#ifndef UTIL_H
#define UTIL_H

//COMMON LIB
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "memory.h"
//SCOPE & LINKAGE
#define import  extern//for declartions in header & C files to be imported from other TU
#define public  extern//for declartions in C files to be exported to other TU
#define private static//for declartions in C files local to the TU
#define local   static//for block-scope variables that should persist accross function invocations
//MACRO
#define memoffset(type, data) &((type *)0)->data
#define swap(a, b) do { typeof(a) tmp = a; a = b; b = tmp; } while(0)
#define MAX_STR_SIZE 256
	
#endif

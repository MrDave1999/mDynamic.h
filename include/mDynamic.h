/*
			mDynamic.h - Matrix Dynamic. Versión [2.0].
			Copyright (c) David Román. All rights reserved.
*/

#ifndef _INC_MDYNAMIC
#define _INC_MDYNAMIC

#include <stdint.h>
#include <stdio.h> 
#include <stdlib.h> 

struct _dim
{
	int32_t new_rows;
	int32_t old_rows;
	int32_t cols;
};

#ifndef MAX_MATRIX
	#error You must define the macro MAX_MATRIX.
#endif

struct _dim dim[MAX_MATRIX];
void* ptrtemp;
uint8_t id;
uint32_t it; 

#ifndef MESSAGE_ALLOC_ROW
	#define MESSAGE_ALLOC_ROW	"Error allocating memory for the rows"
#endif

#ifndef MESSAGE_ALLOC_COL
	#define MESSAGE_ALLOC_COL	"Error allocating memory for the columns"
#endif

#ifndef MESSAGE_REALLOC_ROW
	#define MESSAGE_REALLOC_ROW "Error (re)allocating memory for the rows"
#endif

#ifndef MESSAGE_REALLOC_COL
	#define MESSAGE_REALLOC_COL "Error (re)allocating memory for the columns"
#endif

#define getrows(matrixid) dim[matrixid].new_rows
#define getcols(matrixid) dim[matrixid].cols

#define setrows(matrixid, value) dim[matrixid].new_rows = value;
#define setcols(matrixid, value) dim[matrixid].cols = value;

#define getdata(matrixid, namearray, nameptr, numrow, numcol) (*(*(namearray[matrixid].nameptr + numrow) + numcol))
#define getadd(matrixid, namearray, nameptr, numrow) (*(namearray[matrixid].nameptr + numrow))
#define setdata(matrixid, namearray, nameptr, numrow, numcol, value) getdata(matrixid, namearray, nameptr, numrow, numcol) = value;

#define DELETE_MATRIX(nameptr, rows)																													\
for (it = 0; it != rows; ++it)																															\
	free(*(nameptr + it));																																\
free(nameptr);																																			\
nameptr = NULL;


#define FREE_MEMORY_ALL(namearray, nameptr)																												\
for (id = 0; id != MAX_MATRIX; ++id)																													\
{																																						\
	if (namearray[id].nameptr != NULL)																													\
	{																																					\
		DELETE_MATRIX(namearray[id].nameptr, dim[id].new_rows)																							\
	}																																					\
}


#define ALLOC_RC(matrixid, namearray, nameptr)																											\
namearray[matrixid].nameptr = malloc(dim[matrixid].new_rows * sizeof namearray[matrixid].nameptr);														\
if (namearray[matrixid].nameptr == NULL)																												\
{																																						\
	puts(""MESSAGE_ALLOC_ROW"");																														\
	FREE_MEMORY_ALL(namearray, nameptr)																													\
	return EXIT_FAILURE;																																\
}																																						\
for (it = 0; it != dim[matrixid].new_rows; ++it)																										\
{																																						\
	*(namearray[matrixid].nameptr + it) = malloc(dim[matrixid].cols * sizeof **namearray[matrixid].nameptr);											\
	if (*(namearray[matrixid].nameptr + it) == NULL)																									\
	{																																					\
		puts(""MESSAGE_ALLOC_COL"");																													\
		dim[matrixid].new_rows = it;																													\
		DELETE_MATRIX(namearray[matrixid].nameptr, dim[matrixid].new_rows)																				\
		FREE_MEMORY_ALL(namearray, nameptr)																												\
		return EXIT_FAILURE;																															\
	}																																					\
}																																						\
dim[matrixid].old_rows = dim[matrixid].new_rows;


#define REALLOC_COLS(matrixid, namearray, nameptr)																										\
for (it = 0; it != dim[matrixid].new_rows; ++it)																										\
{																																						\
	ptrtemp = *(namearray[matrixid].nameptr + it);																										\
	*(namearray[matrixid].nameptr + it) = realloc(*(namearray[matrixid].nameptr + it), dim[matrixid].cols * sizeof **namearray[matrixid].nameptr);		\
	if (*(namearray[matrixid].nameptr + it) == NULL)																									\
	{																																					\
		*(namearray[matrixid].nameptr + it) = ptrtemp;																									\
		puts(""MESSAGE_REALLOC_COL"");																													\
		DELETE_MATRIX(namearray[matrixid].nameptr, dim[matrixid].new_rows)																				\
		FREE_MEMORY_ALL(namearray, nameptr)																												\
		return EXIT_FAILURE;																															\
	}																																					\
}																						


#define REALLOC_ROWS(matrixid, namearray, nameptr)																										\
if (dim[matrixid].new_rows < dim[matrixid].old_rows)																									\
{																																						\
	for (it = dim[matrixid].new_rows; it != dim[matrixid].old_rows; ++it)																				\
		free(*(namearray[matrixid].nameptr + it));																										\
}																																						\
ptrtemp = namearray[matrixid].nameptr;																													\
namearray[matrixid].nameptr = realloc(namearray[matrixid].nameptr, dim[matrixid].new_rows * sizeof namearray[matrixid].nameptr);						\
if (namearray[matrixid].nameptr == NULL)																												\
{																																						\
	puts(""MESSAGE_REALLOC_ROW"");																														\
	if(ptrtemp != NULL)																																	\
	{																																					\
		namearray[matrixid].nameptr = ptrtemp;																											\
		DELETE_MATRIX(namearray[matrixid].nameptr, dim[matrixid].old_rows)																				\
	}																																					\
	FREE_MEMORY_ALL(namearray, nameptr)																													\
	return EXIT_FAILURE;																																\
}																																						\
if (dim[matrixid].new_rows > dim[matrixid].old_rows)																									\
{																																						\
	for (it = dim[matrixid].old_rows; it != dim[matrixid].new_rows; ++it)																				\
	{																																					\
		*(namearray[matrixid].nameptr + it) = malloc(dim[matrixid].cols * sizeof **namearray[matrixid].nameptr);										\
		if (*(namearray[matrixid].nameptr + it) == NULL)																								\
		{																																				\
			puts(""MESSAGE_ALLOC_COL"");																												\
			dim[matrixid].new_rows = it;																												\
			DELETE_MATRIX(namearray[matrixid].nameptr, dim[matrixid].new_rows)																			\
			FREE_MEMORY_ALL(namearray, nameptr)																											\
			return EXIT_FAILURE;																														\
		}																																				\
	}																																					\
}																																						\
dim[matrixid].old_rows = dim[matrixid].new_rows;

#endif /* _INC_MDYNAMIC */

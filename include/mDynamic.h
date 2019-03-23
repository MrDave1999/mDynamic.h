/*
			mDynamic.h - Matrix Dynamic.
			Copyright (c) David Román. All rights reserved.
*/

#ifndef _INC_MDYNAMIC
#define _INC_MDYNAMIC

#include <stdio.h> /* for puts */
#include <stdlib.h> /* for malloc, realloc and free */

#ifndef FREE_MA_FUNCTION
	#error You must define the macro FREE_MA_FUNCTION
#endif

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

#define EXISTS_MATRIX(nameptr, rows) if (nameptr != NULL) { DELETE_MATRIX(nameptr, rows) }
#define DERROR() !!(error != 0) /* Detect error */ 

void* ptrtemp = NULL;
unsigned int error;
unsigned int it; /* count iterations in loops/bucles */

#define DELETE_MATRIX(nameptr, rows)													\
for (it = 0; it != rows; ++it)															\
	free(*(nameptr + it));																\
free(nameptr);																			\
nameptr = NULL;


#define CREATE_MATRIX(typedata, nameptr, rows, cols)									\
error = 0;																				\
nameptr = (typedata**)malloc(rows * sizeof nameptr);									\
if (nameptr == NULL)																	\
{																						\
	puts(""MESSAGE_ALLOC_ROW"");														\
	error = 1;																			\
}																						\
else																					\
{																						\
	for (it = 0; it != rows; ++it)														\
	{																					\
		*(nameptr + it) = (typedata*)malloc(cols * sizeof **nameptr);					\
		if (*(nameptr + it) == NULL)													\
		{																				\
			puts(""MESSAGE_ALLOC_COL"");												\
			error = 1;																	\
			rows = it;																	\
			DELETE_MATRIX(nameptr, rows)												\
			break;																		\
		}																				\
	}																					\
}if(FREE_MA_FUNCTION == NULL) return NULL;


#define REALLOC_COLS(typedata, nameptr, rows, newcols)									\
error = 0;																				\
for (it = 0; it != rows; ++it)															\
{																						\
	ptrtemp = *(nameptr + it);															\
	*(nameptr + it) = (typedata*)realloc(*(nameptr + it), newcols * sizeof **nameptr);	\
	if (*(nameptr + it) == NULL)														\
	{																					\
		*(nameptr + it) = (typedata*)ptrtemp;											\
		puts(""MESSAGE_REALLOC_COL"");													\
		error = 1;																		\
		DELETE_MATRIX(nameptr, rows)													\
		break;																			\
	}																					\
}if(FREE_MA_FUNCTION == NULL) return NULL;																								


#define REALLOC_ROWS(typedata, nameptr, new_rows, old_rows, cols)						\
error = 0;																				\
if (new_rows < old_rows)																\
{																						\
	for (it = new_rows; it != old_rows; ++it)											\
		free(*(nameptr + it));															\
}																						\
ptrtemp = (void**)nameptr;																\
nameptr = (typedata**)realloc(nameptr, new_rows * sizeof nameptr);						\
if (nameptr == NULL)																	\
{																						\
	puts(""MESSAGE_REALLOC_ROW"");														\
	error = 1;																			\
	if(ptrtemp != NULL)																	\
	{																					\
		nameptr = (typedata**)ptrtemp;													\
		DELETE_MATRIX(nameptr, old_rows)												\
	}																					\
}																						\
else																					\
{																						\
	if (new_rows > old_rows)															\
	{																					\
		for (it = old_rows; it != new_rows; ++it)										\
		{																				\
			*(nameptr + it) = (typedata*)malloc(cols * sizeof **nameptr);				\
			if (*(nameptr + it) == NULL)												\
			{																			\
				puts(""MESSAGE_ALLOC_COL"");											\
				new_rows = it;															\
				error = 1;																\
				DELETE_MATRIX(nameptr, new_rows)										\
				break;																	\
			}																			\
		}																				\
	}																					\
}if(FREE_MA_FUNCTION == NULL) return NULL;

#endif /* _INC_MDYNAMIC */

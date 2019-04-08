/*
			mDynamic.h - Matrix Dynamic. Versión [3.0]
			Copyright (c) David Román. All rights reserved.
*/

#ifndef _INC_MDYNAMIC
#define _INC_MDYNAMIC

#include <stdint.h>
#include <stdio.h> 
#include <stdlib.h> 

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

#ifndef MAX_MATRIX 
	#error You must define the macro MAX_MATRIX.
#endif

/* Tipo de dimensión o el modo de re-dimensionar */
typedef enum
{
	ROWS,
	COLS,
	ROWS_COLS
}_mode;

/* Almacenamiento de dimensiones de cada matriz */
struct _dim
{
	int32_t new_rows;
	int32_t old_rows;
	int32_t cols;
}dim[MAX_MATRIX];

void** buf_ptr[MAX_MATRIX]; /* Búfer de punteros dobles */

/* Modifica/accede a un respectivo elemento de un búfer de punteros */
#define MOD_BUF_PTR (*(*(buf_ptr + matrixid) + i))

/* Obtiene la cantidad de filas y columnas de una matriz */
#define getrows(matrixid) dim[matrixid].new_rows
#define getcols(matrixid) dim[matrixid].cols

/* Asigna un número de filas y columnas para una matriz  */
#define setrows(matrixid, value) dim[matrixid].new_rows = value
#define setcols(matrixid, value) dim[matrixid].cols = value

/* gd = getdata -> Obtiene un dato de una respectiva columna */
#define gd(typedata, matrixid, i, j) (*((typedata*)*(*(buf_ptr + matrixid) + i) + j))

/* ga = getaddress -> Obtiene la dirección de memoria del primer elemento de cualquier columna */
#define ga(matrixid, i) (*(*(buf_ptr + matrixid) + i))

/* sd = setdata -> Asigna un dato a una respectiva columna de una fila */
#define sd(typedata, matrixid, i, j, value) gd(typedata, matrixid, i, j) = value

/* Detecta si la matriz fue re-dimensionada o no */
#define RE_ASSIGN							\
for(i = 0; i != MAX_MATRIX; ++i)			\
	if (dim[i].new_rows != dim[i].old_rows) \
		dim[i].new_rows = dim[i].old_rows

#ifndef error
/* Detecta si una función personalizada tuvo algún error durante la asignación de memoria */
	#define error(namefunc, ...) if(namefunc(__VA_ARGS__) == EXIT_FAILURE) return EXIT_FAILURE
#endif

/* Macro para la asignación de memoria */
#define alloc_m(typedata, matrixid) if(_alloc_m(matrixid, sizeof(typedata)) == NULL) return EXIT_FAILURE

/* Macro para la re-asignación de memoria (filas/columnas) */
#define realloc_m(typedata, matrixid, mode) if(_realloc_m(matrixid, sizeof(typedata), mode) == NULL) return EXIT_FAILURE

/* Delete-matrix = Libera la memoria de una específica matriz */
#define dmat_m(matrixid)													\
for (uint32_t __i___g = 0; __i___g != dim[matrixid].new_rows; ++__i___g)	\
free(ga(matrixid, __i___g));												\
free(*(buf_ptr + matrixid));												\
*(buf_ptr + matrixid) = NULL;												\
dim[matrixid].new_rows = 0;													\
dim[matrixid].old_rows = 0;													\
dim[matrixid].cols = 0		

/* Sirve para liberar la memoria de todas las matrices dinámicas que estén el heap/montón */
#define free_m()															\
for (uint8_t matrixid = 0; matrixid != MAX_MATRIX; ++matrixid)				\
{																			\
	if (*(buf_ptr + matrixid) != NULL)										\
	{																		\
		dmat_m(matrixid);													\
	}																		\
}

/* Función para reservar memoria para filas y columnas */
void* _alloc_m(const uint8_t matrixid, const uint8_t size)
{
	/* Reserva memoria para un búfer de punteros */
	*(buf_ptr + matrixid) = (void**)malloc(dim[matrixid].new_rows * sizeof **(buf_ptr + matrixid));
	if (*(buf_ptr + matrixid) == NULL)
	{
		puts(""MESSAGE_ALLOC_ROW"");
		return NULL;
	}
	for (uint32_t i = 0; i != dim[matrixid].new_rows; ++i)
	{
		/* Reserva memoria para un búfer de X elementos donde cada elemento del búfer de punteros apuntará hacia el */
		MOD_BUF_PTR = malloc(dim[matrixid].cols * size);
		if (MOD_BUF_PTR == NULL)
		{
			puts(""MESSAGE_ALLOC_COL"");
			dim[matrixid].new_rows = i;
			return NULL;
		}
	}
	dim[matrixid].old_rows = dim[matrixid].new_rows;
	return *(buf_ptr + matrixid);
}

/*
	Función que re-dimensiona una determinada matriz dinámica.
	Puede re-dimensionar tres cosas:
	- Filas y columnas. 
	- Únicamente filas. 
	- Únicamente columnas.
*/
void* _realloc_m(const uint8_t matrixid, const uint8_t size, const _mode mode)
{
	void* ptrtemp;
	uint32_t i;
	if (mode == ROWS || mode == ROWS_COLS)
	{
		if (dim[matrixid].new_rows < dim[matrixid].old_rows)
		{
			/* Caso 1: Código que sirve para liberar la memoria de las columnas que no se van a usar más. */
			for (i = dim[matrixid].new_rows; i != dim[matrixid].old_rows; ++i)
				free(MOD_BUF_PTR);
			dim[matrixid].old_rows = dim[matrixid].new_rows;
		}
		ptrtemp = *(buf_ptr + matrixid);
		/* Re-dimensiona el búfer de punteros de una matriz */
		*(buf_ptr + matrixid) = (void**)realloc(ptrtemp, dim[matrixid].new_rows * sizeof **(buf_ptr + matrixid));
		if (*(buf_ptr + matrixid) == NULL)
		{
			puts(""MESSAGE_REALLOC_ROW"");
			if (ptrtemp != NULL)
			{
				*(buf_ptr + matrixid) = (void**)ptrtemp;
				dim[matrixid].new_rows = dim[matrixid].old_rows;
			}
			RE_ASSIGN;
			return NULL;
		}
		if (dim[matrixid].new_rows > dim[matrixid].old_rows)
		{
			/* Caso 2: Código que sirve para reservar memoria para las columnas faltantes */
			for (i = dim[matrixid].old_rows; i != dim[matrixid].new_rows; ++i)
			{
				MOD_BUF_PTR = malloc(dim[matrixid].cols * size);
				if (MOD_BUF_PTR == NULL)
				{
					puts(""MESSAGE_ALLOC_COL"");
					dim[matrixid].new_rows = i;
					dim[matrixid].old_rows = i;
					RE_ASSIGN;
					return NULL;
				}
			}
		}
	}
	if (mode == COLS || mode == ROWS_COLS)
	{
		for (i = 0; i != dim[matrixid].old_rows; ++i)
		{
			ptrtemp = MOD_BUF_PTR;
			/* Re-dimensiona el tamaño de columnas de dicha matriz */
			MOD_BUF_PTR = realloc(ptrtemp, dim[matrixid].cols * size);
			if (MOD_BUF_PTR == NULL)
			{
				MOD_BUF_PTR = ptrtemp;
				puts(""MESSAGE_REALLOC_COL"");
				dim[matrixid].old_rows = dim[matrixid].new_rows;
				RE_ASSIGN;
				return NULL;
			}
		}
	}
	dim[matrixid].old_rows = dim[matrixid].new_rows;
	return *(buf_ptr + matrixid);
}

/* Hook/enganche a main */

int mDynamic_main();

int main(void)
{
	uint8_t xx = mDynamic_main();
	free_m();
	return xx;
}

#ifndef _ALS_main
	#define _ALS_main
#else
	#undef main
#endif
#define main mDynamic_main

#endif /* _INC_MDYNAMIC */

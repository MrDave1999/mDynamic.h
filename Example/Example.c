#include <pscanf.h>
#include <assertx.h>
#include <random.h>

#define FREE_MA_FUNCTION BorrarMemoria() 

#include "mDynamic.h"

enum
{
	MATRIZ_A,
	MATRIZ_B
};

typedef struct 
{
	int** ptr;
	int fila_actual;
	int fila_antigua;
	int col;
	uint8_t letra;
}dim;

dim matriz[2];

int* BorrarMemoria(void)
{
	if (DERROR())
	{
		EXISTS_MATRIX(matriz[MATRIZ_A].ptr, matriz[MATRIZ_A].fila_actual)
		EXISTS_MATRIX(matriz[MATRIZ_B].ptr, matriz[MATRIZ_B].fila_actual)
		pauseprogram();
		return NULL;
	}
	return (int*)0x0001;
}

int** IngresoFC_Matriz(const uint8_t id1, const uint8_t id2)
{
	while (1)
	{
		dataread("%d", &matriz[id1].fila_actual, "Ingrese la cantidad de filas de la matriz %c:", matriz[id1].letra);
		assertc(matriz[id1].fila_actual >= 1, "\nError: El numero de filas debe ser mayor a 0.")
		break;
	}
	while (1)
	{
		dataread("%d", &matriz[id1].col, "Ingrese la cantidad de columnas de la matriz %c:", matriz[id1].letra);
		assertc(matriz[id1].col >= 1, "\nError: El numero de columnas debe ser mayor a 0.")
		break;
	}
	REALLOC_ROWS(int, matriz[id1].ptr, matriz[id1].fila_actual, matriz[id1].fila_antigua, matriz[id1].col)
	REALLOC_COLS(int, matriz[id1].ptr, matriz[id1].fila_actual, matriz[id1].col)
	matriz[id1].fila_antigua = matriz[id1].fila_actual;
	return matriz[id1].ptr;
}

void ImprimirDatos(const uint8_t id)
{
	uint32_t i, j;
	printf("Matriz %c (%d x %d)\n\n", matriz[id].letra, matriz[id].fila_actual, matriz[id].col);
	for (i = 0; i != matriz[id].fila_actual; ++i)
	{
		for (j = 0; j != matriz[id].col; ++j)
			matriz[id].ptr[i][j] = randomEx(2, 10);
	}
	printf("-> Direcciones de memoria:\n\n");
	for (i = 0; i != matriz[id].fila_actual; ++i)
	{
		for (j = 0; j != matriz[id].col; ++j)
			printf("%d\t", &matriz[id].ptr[i][j]);
		printf("\n");
	}
	printf("-> Datos:\n\n");
	for (i = 0; i != matriz[id].fila_actual; ++i)
	{
		for (j = 0; j != matriz[id].col; ++j)
			printf("%d\t", matriz[id].ptr[i][j]);
		printf("\n");
	}
}

int main(void)
{
	int opcion = 0;
	matriz[0].letra = 'A';
	matriz[1].letra = 'B';
	while (1)
	{
		puts("-> Menu de Opciones:");
		puts("1. Imprimir direcciones de memoria/datos de la matriz A");
		puts("2. Imprimir direcciones de memoria/datos de la matriz B");
		puts("3. Salir del programa");
		dataread("%d", &opcion, "Ingrese una opcion <1-3>:");
		assertc(opcion >= 1 && opcion <= 3, "\nError: Opcion incorrecta.\n")
		switch (opcion)
		{
			case 1: 
				if (IngresoFC_Matriz(MATRIZ_A, MATRIZ_B) == NULL) return EXIT_FAILURE;
				ImprimirDatos(MATRIZ_A);
				break;
			case 2: 
				if (IngresoFC_Matriz(MATRIZ_B, MATRIZ_A) == NULL) return EXIT_FAILURE;
				ImprimirDatos(MATRIZ_B);
				break;
			case 3:
				error = 1;
				BorrarMemoria();
				return EXIT_SUCCESS;
		}
		pauseprogram();
	}   
	return EXIT_SUCCESS;
}   

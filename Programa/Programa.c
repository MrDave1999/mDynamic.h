/*
	El siguiente ejemplo se basa en tres matrices:
	- Las dimensiones y los datos de la matriz A deben ser pedidos por el usuario y se debe
	calcular el promedio de todos los elementos de dicha matriz.
	- Las dimensiones y los datos de la matriz B y C deben ser calculados de forma aleatoria y
	se debe calcular la suma total de sus elementos de cada matriz. La matriz B y C son de tipo "int".
	Además de eso cada vez que se muestre el resultado, se debe mostrar después de eso al usuario
	que si quiere seguir con el programa, si selecciona N, el programa termina, de lo contrario, sigue ejecutándose.
*/

#include <random.h>
#include <assertx.h>
#include <pscanf.h>

#define MAX_MATRIX 3
#include "mDynamic.h"

enum ID_MATRIZ
{
	MA, //Matriz A
	MB, //Matriz B
	MC  //Matriz C
};

uint8_t CrearMatrizA(void)
{
	uint32_t i, j;
	do
	{
		dataread("%d", &getrows(MA), "Ingrese la cantidad de filas de la matriz A:");
		assertc(getrows(MA) >= 1, "Error: El numero de filas debe ser mayor a 0.")
		break;
	} while (1);
	do
	{
		dataread("%d", &getcols(MA), "Ingrese la cantidad de columnas de la matriz A:");
		assertc(getcols(MA) >= 1, "Error: El numero de columnas debe ser mayor a 0.")
		break;
	} while (1);
	alloc_m(float, MA);
	for (i = 0; i != getrows(MA); ++i)
	{
		for (j = 0; j != getcols(MA); ++j)
		{ //Aquí si es necesario las llaves, la macro "dataread" expande tres códigos 
			dataread("%f", &gd(float, MA, i, j), "Ingrese un dato en la fila: %d con respecto a la columna: %d", i + 1, j + 1);
		}
	}
	return EXIT_SUCCESS;
}

float CalcularPromedio_MA(void)
{
	float suma = 0;
	uint32_t i, j;
	for (i = 0; i != getrows(MA); ++i)
	{
		for (j = 0; j != getcols(MA); ++j)
			suma += gd(float, MA, i, j);
	}
	return suma / (getrows(MA)* getcols(MA));
}

uint8_t CrearMatrizBC(const uint8_t matriz_id)
{
	uint32_t i, j;
	int32_t suma = 0;
	setrows(matriz_id, randomEx(1, 5));
	setcols(matriz_id, randomEx(1, 5));
	realloc_m(int, matriz_id, ROWS_COLS);
	for (i = 0; i != getrows(matriz_id); ++i)
	{
		for (j = 0; j != getcols(matriz_id); ++j)
			sd(int, matriz_id, i, j, random(10));
	}
	printf("\nMatriz %c (%d x %d)\n\n", (matriz_id == MB) ? 'B' : 'C', getrows(matriz_id), getcols(matriz_id));
	for (i = 0; i != getrows(matriz_id); ++i)
	{
		for (j = 0; j != getcols(matriz_id); ++j)
		{
			printf("%d\t", gd(int, matriz_id, i, j));
			suma += gd(int, matriz_id, i, j);
		}
		puts("");
	}
	printf("\nLa suma total de todos los elementos de la matriz %c fue de %d\n", (matriz_id == MB) ? 'B' : 'C', suma);
	return EXIT_SUCCESS;
}

int main(void)
{
	char opcion = -1;
	//Si hubo algún error al momento de reservar memoria para la matriz A, el programa termina.
	error(CrearMatrizA);
	printf("El promedio de elementos de la matriz A fue de %f\n\n", CalcularPromedio_MA());
	pauseprogram();
	while (1)
	{
		if (opcion != -1)
		{
			dataread("%c", &opcion, "Deseas seguir re-dimensionando? Ingresa S/N - S de SI/N de NO");
			assertc(opcion == 'S' || opcion == 'N', "Error: Debes ingresar S o N\n")
			if (opcion == 'N') break;
		}
		error(CrearMatrizBC, MB);
		error(CrearMatrizBC, MC);
		pauseprogram();
		opcion = -2;
	}
	return EXIT_SUCCESS;
}

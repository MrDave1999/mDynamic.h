# mDynamic.h
[![Matrix Dynamic](https://shields.southcla.ws/badge/C-mDynamic.h-2f2f2f.svg?style=flat-square)](https://github.com/MrDave1999/mDynamic.h)

Este archivo de inclusión fue creado especialmente para no tener la necesidad de trabajar con punteros a cada rato al momento de crear una matriz dinámica, donde las dimensiones deben ser introducidas por algún usuario en tiempo de ejecución.

# Instalación

Debes agregar `mDynamic.h` en la carpeta `include`, la que viene de forma pre-determinada en el IDE (Entorno de Desarrollo Integrado).
Luego de eso, necesitarás abrir el programa fuente y incluir el archivo de esta manera:
```C
#include <mDynamic.h>
```
Sí tienes algún problema en buscar esa carpeta, también puedes agregar `mDynamic.h` en el directorio donde esté el programa fuente y lo incluyes de esta forma:
```C
#include "mDynamic.h"
```
El requisito para poder compilar este include, es el siguiente: Necesitas definir la macro `FREE_MA_FUNCTION` antes de incluir
`mDynamic.h`.
```C
#define FREE_MA_FUNCTION MY_FUNCTION()
#include "mDynamic.h"
```
Esta macro es esencial definirla porqué de esto depende que las matrices dinámicas que hayan sido reservadas, se liberen de forma éxitosa, claro, siempre y cuando suceda algún fallo al momento de hacer alguna (re)-asignación de memoria.

# Macros

- EXISTS_MATRIX:
  
  Te permite saber si una matriz dinámica fue creada en la memoria o no.
  
- DERROR:

  Te permite detectar si hubo algún error al momento de (re)-asignar memoria para la matriz dinámica.

- DELETE_MATRIX:

  Libera una matriz dinámica de la memoria y hace que el puntero que hayas pasado a la macro, apunte a NULL.

- CREATE_MATRIX:

  Asigna memoria tanto para las filas y columnas. Esta macro tiene dos casos posibles para que falle al momento de reservar memoria.
  
  **1. Caso:** Si no se pudo reservar memoria para las filas.    
  
  **2. Caso:** Sí no se pudo reservar memoria para las columnas.
  Sí cualquiera de estos dos casos se cumplen, la macro libera las demás matrices dinámicas que estén en la memoria.
  
- REALLOC_COLS:
  
  Re-asigna memoria, esto permite aumentar/disminuir el tamaño de las columnas de una determinada matriz dinámica.
  Sí no hay espacio disponible para agrandar más el tamaño, la macro libera la memoria.
  
- REALLOC_ROWS:

  Esta macro sirve para aumentar/disminuir el tamaño de las filas de una determinada matriz dinámica, a la vez también te puede permitir
  asignar memoria como lo hace la macro `CREATE_MATRIX`; sin embargo, para usar esta característica, deberás pasar un puntero nulo.
  Además de eso, necesitarás agregar un número cero en el cuarto argumeno de dicha macro.
  Así quedaría la estructura:
  ```C
  REALLOC_ROWS(char, nombreDelpuntero, numeroDeFilas, 0, numeroDeColumnas)	
  ```
**Nota:** Ninguna macro debería llevar punto y coma.
  
# Uso

Primero que nada, se debe crear una función donde se agrega la macros necesarias para la liberación de memoria. Después se debe colocar el nombre de dicha función, en la macro `FREE_MA_FUNCTION`. 
La estructura sería así:
```C
#define FREE_MA_FUNCTION LiberarMemoria() 
#include "mDynamic.h"

int* LiberarMemoria(void)
{
	if (DERROR())
	{
		EXISTS_MATRIX(nombreDelPuntero_A, numeroDeFilas_A)
		EXISTS_MATRIX(nombreDelPuntero_B, numeroDeFilas_B)
		return NULL;
	}
	return (int*)0x0001;
}
```
En el segundo argumento de la macro `EXISTS_MATRIX` se debe agregar la cantidad de filas de dicha matriz. 

- Ejemplo:

```C
#define FREE_MA_FUNCTION LiberarMemoria() 
#include "mDynamic.h"

enum
{
	MATRIZ_A,
	MATRIZ_B
};

struct _dim
{
	int fila;
	int col;
};
struct _dim dim[2] = 
{
	{5, 3},
	{3, 2}
};
int** matrizA;
char** matrizB;

int* LiberarMemoria(void)
{
	if (DERROR())
	{
		EXISTS_MATRIX(matrizA, dim[MATRIZ_A].fila)
		EXISTS_MATRIX(matrizB, dim[MATRIZ_B].fila)
		return NULL;
	}
	return (int*)0x0001;
}

int main(void)
{
	int fila_antigua = dim[MATRIZ_A].fila;
	CREATE_MATRIX(int, matrizA, dim[MATRIZ_A].fila, dim[MATRIZ_A].col)

	dim[MATRIZ_A].fila = 9;
	REALLOC_ROWS(int, matrizA, dim[MATRIZ_A].fila, fila_antigua, dim[MATRIZ_A].col)

	CREATE_MATRIX(char, matrizB, dim[MATRIZ_B].fila, dim[MATRIZ_B].col)
	dim[MATRIZ_B].col = 5;
	REALLOC_COLS(int, matrizB, dim[MATRIZ_B].fila, dim[MATRIZ_B].col)

	DELETE_MATRIX(matrizA, dim[MATRIZ_A].fila)
	DELETE_MATRIX(matrizB, dim[MATRIZ_B].fila)
	return EXIT_SUCCESS;
}   
```
El algoritmo sería así:
1. Se determina cual es el tamaño de filas antiguo de la matriz A.
2. Se reserva memoria para las filas y columnas y de ese modo, se tiene creada la matriz.
3. Se actualiza el número de filas de la matriz A.
4. Aumentamos el tamaño de filas de la matriz A, ahora sus dimensiones son 9x3.
5. Reservamos memoria para las filas y columnas de la matriz B.
6. Modificamos el nuevo tamaño de columnas de la matriz B.
7. Re-asignamos las columnas de la matriz B y ahora sus dimensiones serían 3x5.
8. Por último si no hubo ningún error al momento de asignar memoria, se lo libera con la macro `DELETE_MATRIX`.

De este modo no necesitas preocuparte de cuando necesitas liberar la memoria, tan solo con colocar la función "LiberarMemoria", estaría hecho todo de forma automática.
Incluso, las macros:
`CREATE_MATRIX`, `REALLOC_COLS`, `REALLOC_ROWS` llaman/invocan de manera automática la función "LiberarMemoria". Por esa razón todo es más sencillo.

En el siguiente enlace encontrarás un código de ejemplo completo sobre la aplicación de este include: [Programa](https://github.com/MrDave1999/mDynamic.h/blob/master/Example/Example.c)

# Créditos

- [MrDave](https://github.com/MrDave1999)
  - Por crear mDynamic.h
- [Microsoft](https://www.microsoft.com/es-ec/)
  - Se hizo uso de algunos archivos de cabecera estándares como stdio.h & stdlib.h

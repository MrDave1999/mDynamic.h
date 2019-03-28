# mDynamic.h
[![Matrix Dynamic](https://shields.southcla.ws/badge/C-mDynamic.h-2f2f2f.svg?style=flat-square)](https://github.com/MrDave1999/mDynamic.h)

Este archivo de inclusión fue creado especialmente para no tener la necesidad de trabajar con punteros a cada rato al momento de crear una matriz dinámica, donde las dimensiones deben ser introducidas por algún usuario en tiempo de ejecución.

# <a name= "indice"></a> Índice
- [Instalación](#instalacion)
- [Requisitos](#requisitos)
- [Macros](#macros)
- [Uso](#uso)
- [Recomendación](#recomendacion)
- [Créditos](#creditos)

# <a name= "instalacion"></a> Instalación

Debes agregar `mDynamic.h` en la carpeta `include`, la que viene de forma pre-determinada en el IDE (Entorno de Desarrollo Integrado).
Luego de eso, necesitarás abrir el programa fuente y incluir el archivo de esta manera:
```C
#include <mDynamic.h>
```
Sí tienes algún problema en buscar esa carpeta, también puedes agregar `mDynamic.h` en el directorio donde esté el programa fuente y lo incluyes de esta forma:
```C
#include "mDynamic.h"
```
[Volver al índice](#indice)

# <a name= "requisitos"></a> Requisitos 

- Necesitas definir la macro `MAX_MATRIX` antes de incluir `mDynamic.h`.

	Esta macro es esencial definirla porqué el include necesita saber el número de matrices que serán usados en el programa.
```C
	#define MAX_MATRIX (2) /* Se especifica la cantidad de matrices dinámicas que tendrá el programa */
	#include "mDynamic.h"
```

- Cada matriz debe tener un puntero doble y necesita ser miembro de un "union". 

	Para saber la identificación de la matriz, se puede usar un "enum".
	
	Por ejemplo:
```C
	#define MAX_MATRIX 2
	#include <mDynamic.h>

	enum
	{
		MA,
		MB
	};

	union punteros
	{
		int** ptr_a; //El puntero doble de la matriz A
		char** ptr_b; //El puntero doble de la matriz B
	};

	union punteros matriz[MAX_MATRIX]; //Se declara un arreglo/array de tipo "union"

	int main(void)
	{
		/*
			Por defecto el puntero doble debe apuntar a NULL.
			Ahora puedes usar el arreglo de esta manera:
		*/
		matriz[MA].ptr_a = NULL; 
		matriz[MB].ptr_b = NULL;
		return 0;
	}   
```
[Volver al índice](#indice)

# <a name="macros"></a> Macros 
  
- `FREE_MEMORY_ALL(namearray, nameptr)`:

  Libera la memoria de todas las matrices dinámicas que existan en el montón/heap.

- `setrows(matrixid, value)`:

	Establece/asigna la cantidad de filas a una matriz.
	
- `setcols(matrixid, value)`:

	Establece/asigna la cantidad de columnas a una matriz.

- `ALLOC_RC(matrixid, namearray, nameptr)	`: 

  Asigna memoria tanto para las filas y columnas. Sí no se pudo asignar memoria, la macro hace que el programa finalice su ejecución.
	
	**Uso:**
```C
	int main(void)
	{
		setrows(MA, 5)// Asigna una fila a la matriz A
		setcols(MA, 3)// Asigna una columna a la matriz A
		ALLOC_RC(MA, matriz, ptr_a) //Reservamos memoria para las filas y columnas de la matriz A

		FREE_MEMORY_ALL(matriz, ptr_a) //Liberamos la matriz A
		return 0;
	}   
```
  
- `REALLOC_COLS(matrixid, namearray, nameptr)`: 
  
  Re-asigna memoria para aumentar/disminuir el tamaño de las columnas de una determinada matriz dinámica.
  Sí no hay espacio disponible para agrandar más el tamaño, la macro libera la memoria y el programa termina su ejecución.
	
	**Uso:**
	
```C
	int main(void)
	{
		setrows(MA, 5)// Asigna una fila a la matriz A
		setcols(MA, 3)// Asigna una columna a la matriz A
		ALLOC_RC(MA, matriz, ptr_a) //Reservamos memoria para las filas y columnas de la matriz A

		setcols(MA, 5)// Nueva columna para la matriz A
		REALLOC_COLS(MA, matriz, ptr_a) //Aumentamos el tamaño de columnas de la matriz A

		FREE_MEMORY_ALL(matriz, ptr_a) //Liberamos la matriz A
		return 0;
	}   
```
 
- `REALLOC_ROWS(matrixid, namearray, nameptr)`:

  Aumenta/disminuye el tamaño de las filas de una determinada matriz dinámica, a la vez también te puede permitir
  asignar memoria como lo hace la macro `ALLOC_RC`; sin embargo, para usar esta característica, deberás pasar un puntero nulo.
  Sí la macro no puede (re)-asignar memoria, libera la memoria y efectúa un "return" para que el programa termine su ejecución.

	**Uso:**
```C
	int main(void)
	{
		setrows(MA, 5)// Asigna una fila a la matriz A
		setcols(MA, 3)// Asigna una columna a la matriz A
		
		//REALLOC_ROWS actúa en este caso como ALLOC_RC.
		REALLOC_ROWS(MA, matriz, ptr_a) //Reservamos memoria para las filas y columnas de la matriz A. 

		setrows(MA, 7)// Nueva fila para la matriz A
		REALLOC_ROWS(MA, matriz, ptr_a)// Aumentamos el tamaño de filas de la matriz A

		FREE_MEMORY_ALL(matriz, ptr_a) //Liberamos la memoria de la matriz A
		return 0;
	}   
```

- `getrows(matrixid)`:

	Obtiene la cantidad de filas de una matriz.
	
	**Uso:**
```C
	int main(void)
	{
		setrows(MA, 5)
		setcols(MA, 3)
		ALLOC_RC(MA, matriz, ptr_a) 

		printf("Cantidad de filas de la matriz A: %d\n", getrows(MA));

		FREE_MEMORY_ALL(matriz, ptr_a) 
		return 0;
	}   
```

- `getcols(matrixid)`:

	Obtiene la cantidad de columnas de una matriz.
	
	**Uso:**
```C
	int main(void)
	{
		setrows(MA, 5)
		setcols(MA, 3)
		ALLOC_RC(MA, matriz, ptr_a) 

		printf("Cantidad de columnas de la matriz A: %d\n", getcols(MA));

		FREE_MEMORY_ALL(matriz, ptr_a) 
		return 0;
	}   
```
	
- `setdata(matrixid, namearray, nameptr, numrow, numcol, value)`:

	Establece/asigna un dato a una columna con respecto a una fila.
	
	**Uso:**
```C
	int main(void)
	{
		setrows(MA, 5)
		setcols(MA, 3)
		ALLOC_RC(MA, matriz, ptr_a) 

		/*
			Asigna un número 20 al índice 0 de una fila con respecto al índice 1 de una columna.
		*/
		setdata(MA, matriz, ptr_a, 0, 1, 20) //Es equivalente a esto: matriz[MA].ptr_a[0][1] = 20;

		FREE_MEMORY_ALL(matriz, ptr_a) 
		return 0;
	}   
```

- `getdata(matrixid, namearray, nameptr, numrow, numcol)`:

	Obtiene un dato de una columna con respecto a una fila.
	
	**Uso:**
```C
	int main(void)
	{
		setrows(MA, 5)
		setcols(MA, 3)
		ALLOC_RC(MA, matriz, ptr_a) 

		setdata(MA, matriz, ptr_a, 0, 1, 20)
		/* Dará como resultado un 20 */
		printf("Valor: %d\n", getdata(MA, matriz, ptr_a, 0, 1)); //Es equivalente a esto: matriz[MA].ptr_a[0][1] 

		FREE_MEMORY_ALL(matriz, ptr_a) 
		return 0;
	}  
```

- `getadd(matrixid, namearray, nameptr, numrow)`:

	Obtiene la dirección de memoria del primer elemento de una fila.
	
	**Uso:**
```C
	int main(void)
	{
		unsigned int i;
		setrows(MA, 5)
		setcols(MA, 3)
		ALLOC_RC(MA, matriz, ptr_a) 

		/*
			Dará como resultado las direcciones de memoria del primer elemento de cada fila
		*/
		for (i = 0; i != getrows(MA); ++i)
			printf("%d\n", getadd(MA, matriz, ptr_a, i));//Es equivalente a esto: matriz[MA].ptr_a[i] 

		FREE_MEMORY_ALL(matriz, ptr_a) 
		return 0;
	}   
```
[Volver al índice](#indice)

# <a name="uso"></a> Uso

El siguiente ejemplo se basa en tres matrices:

A. Las dimensiones y los datos de la matriz A deben ser pedidos por el usuario y se debe calcular el promedio de todos los elementos de dicha matriz.

B. Las dimensiones y los datos de la matriz B y C deben ser calculados de forma aleatoria y se debe calcular la suma total de sus
elementos de cada matriz. La matriz B y C son de tipo "int". 
Además de eso cada vez que se muestre el resultado, se debe mostrar después de eso al usuario que si quiere seguir con el programa, si selecciona N, el programa termina, de lo contrario, sigue ejecutándose.

Se va a usar tres `header files` para el desarrollo de este programa:

- [pscanf.h](https://github.com/MrDave1999/pscanf.h)
- [random.h](https://github.com/MrDave1999/random.h)
- [assertx.h](https://github.com/MrDave1999/assertx.h)

Este programa de ejemplo será construido de forma modular, a base de funciones.

Lo primero para resolver este problema, es declarando un array de tipo "union" con sus respectivos miembros. El "union" es diferente al "structs", debido que únicamente se ocupa un espacio de memoria para todos los miembros, por esa razón usar "union" es lo esencial para que el include `mDynamic.h` funcione correctamente.
```C
#include <random.h>
#include <assertx.h>
#include <pscanf.h>

#define MAX_MATRIX 3 /* Se especifica el número de matrices que se van a usar */
#include <mDynamic.h>

enum ID_MATRIZ
{ 
	MA, //Matriz A
	MB, //Matriz B
	MC  //Matriz C
};

union pun
{
	float** pa; //Puntero doble de la matriz A 
	int** pbc; //Puntero doble de la matriz B y C
};

union pun matriz[MAX_MATRIX];
```
El literal A nos pide esto:

A. Las dimensiones y los datos de la matriz A deben ser pedidos por el usuario y se debe calcular el promedio de todos los elementos de dicha matriz.

La función a utilizar será `CrearMatrizA`:
```C
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
	ALLOC_RC(MA, matriz, pa)
	for (i = 0; i != getrows(MA); ++i)
	{
		for (j = 0; j != getcols(MA); ++j)
		{ //Aquí si es necesario las llaves, la macro "dataread" expande tres códigos 
			dataread("%f", &matriz[MA].pa[i][j], "Ingrese un dato en la fila: %d con respecto a la columna: %d", i+1, j+1);
		}
	}
	return EXIT_SUCCESS; //Equivalente a esto: <return 0;>
}
```
La función `CrearMatrizA` devuelve dos valores, 0 si la macro ALLOC_RC pudo reservar memoria para la matriz A, de lo contrario hace que la función devuelva 1.

Ahora por último nos falta la función para calcular el promedio de todos los elementos de la matriz A, esta sería la función:
```C
float CalcularPromedio_MA(void)
{
	float suma = 0;
	uint32_t i, j;
	for (i = 0; i != getrows(MA); ++i)
	{
		for (j = 0; j != getcols(MA); ++j)
			suma += matriz[MA].pa[i][j];
	}
	return suma / (getrows(MA)* getcols(MA));
}
```
Ahora sólo falta llamar ambas funciones en la función principal:
```C
int main(void)
{
	char opcion = -1; //Esta variable la usaremos después, para el literal B del problema
	//Si hubo algún error al momento de reservar memoria para la matriz A, el programa termina.
	if (CrearMatrizA() == EXIT_FAILURE)
	{
		pauseprogram();
		return EXIT_FAILURE;
	}
	printf("El promedio de elementos de la matriz A fue de %f\n\n", CalcularPromedio_MA());
	pauseprogram();
```
Sigamos con el problema, nos vamos al literal B y dice lo siguiente:

B. Las dimensiones y los datos de la matriz B y C deben ser calculados de forma aleatoria y se debe calcular la suma total de sus
elementos de cada matriz. La matriz B y C son de tipo "int". 
Además de eso cada vez que se muestre el resultado, se debe mostrar después de eso al usuario que si quiere seguir con el programa, si selecciona N, el programa termina, de lo contrario, sigue ejecutándose.

Ok, debemos crear una función llamada `CrearMatrizBC` y que lleve un parámetro para agregar la identificación de la matriz al momento de invocar dicha subrutina. 
```C
uint8_t CrearMatrizBC(const uint8_t matriz_id)
{
	uint32_t i, j;
	int32_t suma = 0;
	setrows(matriz_id, randomEx(1, 5))
	setcols(matriz_id, randomEx(1, 5))
	REALLOC_ROWS(matriz_id, matriz, pbc)
	REALLOC_COLS(matriz_id, matriz, pbc)

	for (i = 0; i != getrows(matriz_id); ++i)
	{
		for (j = 0; j != getcols(matriz_id); ++j)
			matriz[matriz_id].pbc[i][j] = random(10);
	}
	printf("\nMatriz %c (%d x %d)\n\n", (matriz_id == MB) ? 'B' : 'C', getrows(matriz_id), getcols(matriz_id));
	for (i = 0; i != getrows(matriz_id); ++i)
	{
		for (j = 0; j != getcols(matriz_id); ++j)
		{
			printf("%d\t", matriz[matriz_id].pbc[i][j]);
			suma += matriz[matriz_id].pbc[i][j];
		}
		puts("");
	}
	printf("\nLa suma total de todos los elementos de la matriz %c fue de %d\n", (matriz_id == MB) ? 'B' : 'C', suma);
	return EXIT_SUCCESS;
}
```
Para finalizar el literal B, debemos terminar el código que dejamos anteriormente en la función principal.
```C
int main(void)
{
	char opcion = -1;
	//Si hubo algún error al momento de reservar memoria para la matriz A, el programa termina.
	if (CrearMatrizA() == EXIT_FAILURE)
	{
		pauseprogram();
		return EXIT_FAILURE;
	}
	printf("El promedio de elementos de la matriz A fue de %f\n\n", CalcularPromedio_MA());
	pauseprogram();
	while (1)
	{
		if (opcion != -1)
		{
			dataread("%c", &opcion, "Deseas seguir re-dimensionando? Ingresa S/N - S de SI/N de NO");
			assertc(opcion == 'S' || opcion == 'N', "Error: Debes ingresar S o N\n")
			if (opcion == 'N')
			{
				FREE_MEMORY_ALL(matriz, pa)/* Hay que liberar la memoria de las matrices activas en el heap */
				return EXIT_SUCCESS;
			}
		}
		if (CrearMatrizBC(MB) == EXIT_FAILURE || CrearMatrizBC(MC) == EXIT_FAILURE)
		{
			pauseprogram();
			return EXIT_FAILURE;
		}
		pauseprogram();
		opcion = -2;
	}
	return EXIT_SUCCESS;
}   
```
**Nota:** El identificador `uint32_t` es un simple alias de `unsigned int` y esta definición viene en el archivo de cabecera estándar `stdint.h`

Aquí te dejo el programa completo con su respectivo código fuente y ejecutable: [Programa](https://github.com/MrDave1999/mDynamic.h/tree/master/Programa)

[Volver al índice](#indice)

# <a name="recomendacion"></a> Recomendación

Se recomienda llevar este orden al momento de pedir / asignar las filas y columnas de una matriz.

El ordenamiento sería así:
```C
#define MAX_MATRIX 2
#include <mDynamic.h>

enum { MA, MB };

union pun
{
	char** pa;
	int** pb;
};

union pun matriz[MAX_MATRIX];

int main(void)
{
	/* 1. Se reservaría memoria para la matriz A */
	setrows(MA, 6)
	setcols(MA, 4)
	ALLOC_RC(MA, matriz, pa)

	/* 2. Se reservaría memoria para la matriz B */
	setrows(MB, 5)
	setcols(MB, 5)
	ALLOC_RC(MB, matriz, pb)

	/* 3. Se aumenta las filas de la matriz A */
	setrows(MA, 8)
	REALLOC_ROWS(MA, matriz, pa)

	/* 4. Se aumenta las filas de la matriz B */
	setrows(MB, 6)
	REALLOC_ROWS(MB, matriz, pb)

	/* 5. Se disminuye las columnas de la matriz A */
	setcols(MA, 3)
	REALLOC_COLS(MA, matriz, pa)

	/* 6. Se disminuye las columnas de la matriz B */
	setcols(MB, 4)
	REALLOC_COLS(MB, matriz, pb)

	/* Fin algoritmo */
	return 0;
}
```
Te preguntarás porqué la recomendación y eso se debe porqué puede ocurrir un problema si no se cumple con un buen orden al momento de
escribir las macros de asignación de memoria.

Mira el siguiente orden y se irá explicando paso a paso el código hasta encontrar el error:
```C
int main(void)
{
	/* 1. Se reservaría memoria para la matriz A */
	setrows(MA, 6)
	setcols(MA, 4)
	ALLOC_RC(MA, matriz, pa)

	/* 2. Se reservaría memoria para la matriz B */
	setrows(MB, 5)
	setcols(MB, 5)
	ALLOC_RC(MB, matriz, pb)

	/* 3. Se asigna las nuevas filas para la matriz A y B */
	setrows(MA, 8)
	setrows(MB, 6)

	/* 4. Se aumenta las filas de la matriz A y B */
	REALLOC_ROWS(MA, matriz, pa)
	REALLOC_ROWS(MB, matriz, pb)

	/* 5. Se disminuye las columnas de la matriz A */
	setcols(MA, 3)
	REALLOC_COLS(MA, matriz, pa)

	/* 6. Se disminuye las columnas de la matriz B */
	setcols(MB, 4)
	REALLOC_COLS(MB, matriz, pb)

	/* Fin algoritmo */
	return 0;
}
```
**El paso 1 y 2** están bien, pues sólo se asigna memoria para ambas matrices. Dimensiones: Matriz A: 6x4, Matriz B: 5x5.

**El paso 3** tampoco hay problemas, sólo se determina las nuevas filas de la matriz A y B.

**El paso 4** es donde está el inconveniente y no es algo notable en tiempo de ejecución, por lo tanto no te darás cuenta, ya que el error sucederá cuando la macro REALLOC_ROWS no pueda re-asignar más memoria.

**Analizemos la situación:**
Primero se re-asigna memoria para las filas de la matriz A; pero imagínate que ya no hay más espacio disponible en el montón/heap para re-asignar memoria y por ende, la macro detiene la ejecución del código y libera primero la memoria de la matriz A, luego la matriz B.

Aquí está el grave error, la macro para poder liberar la memoria de la matriz B, necesita la cantidad de filas actuales de la matriz B; sin embargo, le cambiamos la dimensión antes de re-dimensionar la matriz B, eso quiere decir que la macro se quedará con el tamaño de 6 y debería ser 5, porqué aún no RE-DIMENSIONAMOS la matriz B.

¿Qué consecuencias trae esto? En este caso ocurriría un desbordamiento de búfer, en otro caso podría ocasionar fuga de memoria (pérdida de memoria).

Por esa razón la solución más rápida es llevar un orden estándar:
```C
/* Se aumenta las filas de la matriz A */
setrows(MA, 8)
REALLOC_ROWS(MA, matriz, pa)

/* Se aumenta las filas de la matriz B */
setrows(MB, 6)
REALLOC_ROWS(MB, matriz, pb)
```
[Volver al índice](#indice)

# <a name="creditos"></a> Créditos

- [MrDave](https://github.com/MrDave1999)
  - Por crear `mDynamic.h`
- [Microsoft](https://www.microsoft.com/es-ec/)
  - Se hizo uso de algunos archivos de cabecera estándares como `stdio.h` & `stdlib.h`
- [P.J.Plauger](https://en.wikipedia.org/wiki/P._J._Plauger)
	- Por crear `stdint.h` 
	- [The Standard C Library source code by P.J. Plauger](https://github.com/Justme0/CLIB)

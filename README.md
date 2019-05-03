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

#  Requisitos 

- Necesitas definir la macro `MAX_MATRIX` antes de incluir `mDynamic.h`.

Esta macro es esencial definirla porqué el include necesita saber el número de matrices que serán usados en el programa.
```C
#define MAX_MATRIX 2 /* Se especifica la cantidad de matrices dinámicas que tendrá el programa */
#include "mDynamic.h"
```

- Las identificaciones de las matrices deben comenzar desde 0, de lo contrario, ocurriría un desbordamiento de búfer y eso ocasiona que el programa deje de funcionar.

Incorrecto:
```C
#define MA 2 //matriz A
#define MA 3 //matriz B
```

Correcto:
```C
#define MA 0 //matriz A
#define MA 1 //matriz B
```

# Macros 
  
- `getrows(matrixid)`: Obtiene la cantidad de filas de una matriz dinámica.
- `getcols(matrixid)`: Obtiene la cantidad de columnas de una matriz dinámica.
- `setrows(matrixid, value)`: Asigna un número de filas a una matriz.
- `setcols(matrixid, value)`: Asigna un número de columnas a una matriz.
- `dmat_m(matrixid)`: Libera la memoria de una determinada matriz.
- `free_m()`: Libera la memoria de todas las matrices dinámicas.
- `alloc_m(typedata, matrixid)`: 

Reserva memoria para las filas y columnas de una matriz. La macro hace que la función retorne 1 sí hubo algún fallo durante la asignación de memoria.

**Ejemplo:**
```C
#define MAX_MATRIX 2
#include <mDynamic.h>

enum ID_MATRIZ
{
	MA, //Matriz A de tipo entero
	MB, //Matriz B de tipo flotante
};

int main(void)
{
	/* Asignamos el número de filas y columnas para la matriz A y B */
	setrows(MA, 6);
	setcols(MA, 3);
	setrows(MB, 3);
	setcols(MB, 2);

	/* Reservamos las filas y columnas de la matriz A y B */
	alloc_m(int, MA);
	alloc_m(float, MB);

	/* La memoria se libera automáticamente */
	return 0;
}
```

- `realloc_m(typedata, matrixid, mode)`: 

Hace una re-asignación de memoria para las filas o columnas. La macro también hace que la función retorne 1 sí hubo algún error durante la re-asignación de memoria.

**Parámetros:**

typedata: El tipo de dato de la matriz.
	
matrixid: La identificación de la matriz.
	
mode: El modo a re-dimensionar.

**Existen tres modos:**

***ROWS***: Re-asigna memoria únicamente para las filas. 

**Ejemplo 1:**
```C
int main(void)
{
	setrows(MA, 6);
	setcols(MA, 3);
	setrows(MB, 3);
	setcols(MB, 2);
	alloc_m(int, MA);
	alloc_m(float, MB);

	/* Nuevas filas de la matriz A y B */
	setrows(MA, 9);
	setrows(MB, 2);

	/* Re-asignamos las filas de la matriz A y B */
	realloc_m(int, MA, ROWS);
	realloc_m(float, MB, ROWS);

	/* La memoria se libera automáticamente */
	return 0;
}
```

***COLS:*** Re-asigna memoria únicamente paras las columnas.

**Ejemplo 2:**
```C
int main(void)
{
	setrows(MA, 6);
	setcols(MA, 3);
	setrows(MB, 3);
	setcols(MB, 2);
	alloc_m(int, MA);
	alloc_m(float, MB);

	/* Nuevas columnas para la matriz A y B */
	setcols(MA, 5);
	setcols(MB, 1);

	/* Re-asignamos las columnas de la matriz A y B */
	realloc_m(int, MA, COLS);
	realloc_m(float, MB, COLS);

	/* La memoria se libera automáticamente */
	return 0;
}
```

***ROWS_COLS:*** Re-asigna memoria para las filas y columnas.

**Ejemplo 3:**
```C
int main(void)
{
	setrows(MA, 6);
	setcols(MA, 3);
	setrows(MB, 3);
	setcols(MB, 2);
	alloc_m(int, MA);
	alloc_m(float, MB);

	/* Nuevas filas y columnas de la matriz A y B */
	setrows(MA, 9);
	setrows(MB, 2);
	setcols(MA, 5);
	setcols(MB, 1);

	/* Re-asignamos las filas y columnas de la matriz A y B */
	realloc_m(int, MA, ROWS_COLS);
	realloc_m(float, MB, ROWS_COLS);

	/* La memoria se libera automáticamente */
	return 0;
}
```


- `gd(typedata, matrixid, i, j)`:

El nombre `gd` significa `getdata` y sirve para obtener un dato de una columna con respecto a una fila.

**Parámetros:**

typedata: El tipo de dato de la matriz.

matrixid: La identificación de la matriz.

i: El número de una respectiva fila.

j: El número de una respectiva columna.

**Ejemplo:**
```C
#define MAX_MATRIX 1
#include <mDynamic.h>
#define MA 0

int main(void)
{
	int i, j;
	setrows(MA, 6);
	setcols(MA, 3);
	alloc_m(int, MA);
	/* Imprime todo el contenido de la matriz A  */
	for (i = 0; i != getrows(MA); ++i)
	{
		for (j = 0; j != getcols(MA); ++j)
			printf("%d\t", gd(int, MA, i, j));
		printf("\n");
	}
	/* La memoria se libera automáticamente */
	return 0;
}
```

- `ga(matrixid, i)`: 

El nombre `ga` significa `getAddress` y sirve para obtener la dirección de memoria del primer dato de una columna con respecto a una fila. Esta macro es especialmente para matrices dinámicas que manejen cadenas.

**Ejemplo:**
```C
#define MAX_MATRIX 1
#include <mDynamic.h>
#define MA 0

int main(void)
{
	setrows(MA, 6);
	setcols(MA, 5);
	/* Matriz que guarda cadenas */
	alloc_m(char, MA);
	/* Mandamos la primera dirección de memoria de la segunda columna */
	printf("Ingrese una cadena:\n");
	scanf("%s", ga(MA, 1));
	printf("%s\n", ga(MA, 1));
	
	/* La memoria se libera automáticamente */
	return 0;
}
```


- `sd(typedata, matrixid, i, j, value)`: 

El nombre `sd` significa `setdata` y sirve para asignar un dato a una columna con respecto a una fila.
```C
#define MAX_MATRIX 1
#include <mDynamic.h>
#define MA 0

int main(void)
{
	int i, j;
	setrows(MA, 6);
	setcols(MA, 3);
	alloc_m(int, MA);
	/* Rellena de datos a la matriz A  */
	for (i = 0; i != getrows(MA); ++i)
	{
		for (j = 0; j != getcols(MA); ++j)
			sd(int, MA, i, j, 20);
	}
	/* La memoria se libera automáticamente */
	return 0;
}
```

- `error(namefunc, ...)`: 

Detecta si una función tuvo algún fallo al momento de asignar memoria y hace detener la ejecución del programa.

**Parámetros:**

namefunc: Nombre de la función.

<...> : Argumentos que tenga dicha función.

**Ejemplo:**
```C
#define MAX_MATRIX 1
#include <mDynamic.h>
#define MA 0

int myfunc(void)
{
	setrows(MA, 6);
	setcols(MA, 5);
	alloc_m(char, MA);
	return 0;
}

int main(void)
{
	/* Detecta si hubo fallo en la asignación de memoria durante la ejecución de "myfunc" */
	error(myfunc);
	/* La memoria se libera automáticamente */
	return 0;
}
```


# Uso

Un uso completo sobre las macros de `mDynamic.h`.

En este ejemplo se utilizó los siguientes archivos de cabeceras:
- [random.h](https://github.com/MrDave1999/random.h)
- [assertx.h](https://github.com/MrDave1999/assertx.h)
- [pscanf.h](https://github.com/MrDave1999/pscanf.h)
```C
#define MAX_MATRIX 2 /* Dos matrices dinámicas usará el programa */
#include <mDynamic.h> /* Inclusión del archivo */
#include <pscanf.h> /* Para poder usar la macro dataread y strread */
#include <assertx.h> /* Para poder usar la macro assertc */
#include <random.h> /* Por la macro randomEx */
#include <stdint.h> /* Por el uso del alias uint8_t, equivalente a la expresión: unsigned char */

enum ID_MATRIX
{
	MA_STRING, //Matriz A de tipo char
	MB_INT //Matriz B de tipo int
};

uint8_t CreateMatrix_String(void)
{
	while (1)
	{
		dataread("%d", &getrows(MA_STRING), "Ingrese la cantidad de cadenas para la matriz:");
		assertc(getrows(MA_STRING) >= 1, "Error: La cantidad de cadenas debe ser mayor a 0");
		break;
	}
	while (1)
	{
		dataread("%d", &getcols(MA_STRING), "Ingrese la longitud maxima de caracteres:");
		assertc(getcols(MA_STRING) >= 1, "Error: La longitud debe ser mayor a 0");
		break;
	}
	/* 
		Reservamos memoria para una matriz de cadenas, donde la cantidad de filas es igual al número de cadenas
		y la cantidad de columnas es igual al número de caracteres máximo que puede tener cada cadena.
	*/
	alloc_m(char, MA_STRING); 
	for (uint32_t i = 0; i != getrows(MA_STRING); ++i)
	{
		strread(ga(MA_STRING, i), getcols(MA_STRING), "Ingrese una cadena (NUM: %d):", i + 1);
	}
	return EXIT_SUCCESS;
}

uint8_t CreateMatrix_Int(const uint32_t rows, const uint32_t cols)
{
	uint8_t i, j;
	/* Asignación de filas y columnas para la matriz */
	setrows(MB_INT, rows);
	setcols(MB_INT, cols);
	/* Re-asignamos memoria para las filas y columnas */
	realloc_m(int, MB_INT, ROWS_COLS);
	/* Rellenamos de datos a la matriz */
	for (i = 0; i != getrows(MB_INT); ++i)
		for (j = 0; j != getcols(MB_INT); ++j)
			sd(int, MB_INT, i, j, random(10));
	/* Imprime los datos actualizados de la matriz B */
	for (i = 0; i != getrows(MB_INT); ++i)
	{
		for (j = 0; j != getcols(MB_INT); ++j)
			printf("%d\t", gd(int, MB_INT, i, j));
		printf("\n");
	}
	printf("\n");
	return EXIT_SUCCESS;
}

int main(void)
{
	uint8_t rows, cols, i;
	error(CreateMatrix_String); /* Llama a la función y detecta algún error en la asignación de memoria */
	/* Imprime las cadenas de la matriz A */
	for (i = 0; i != getrows(MA_STRING); ++i)
		printf("%s\n", ga(MA_STRING, i));
	printf("\n");
	/* Re-asignamos tres veces la matriz B */
	for (i = 0; i != 3; ++i)
	{
		rows = randomEx(1, 5);
		cols = randomEx(2, 7);
		error(CreateMatrix_Int, rows, cols);
	}
	pauseprogram(); /* macro de pscanf.h */
	return EXIT_SUCCESS;
}
```
Aquí dejo un programa completo con su respectivo código fuente y ejecutable: [Programa](https://github.com/MrDave1999/mDynamic.h/tree/master/Programa)

Para la realización de este programa, se usó los siguientes `header files`:
- [random.h](https://github.com/MrDave1999/random.h)
- [assertx.h](https://github.com/MrDave1999/assertx.h)
- [pscanf.h](https://github.com/MrDave1999/pscanf.h)


# Créditos

- [MrDave](https://github.com/MrDave1999) 
	- Por el desarrollo de mDynamic.h
- [Microsoft Corporation](https://github.com/Microsoft) 
	- Se usó el compilador `cl.exe` para poder compilar los códigos de prueba, de ese modo se comprueba sí no hubo algún error.

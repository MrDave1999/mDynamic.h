#define MAX_MATRIX 2
#include "mDynamic.h"

enum
{
	MA,
	MB
};

union poin
{
	int** pa;
	double** pb;
};

union poin mx[MAX_MATRIX];

void PrintData(void)
{
	int i, j;
	printf("\n");
	printf("Matriz A: (%d x %d)\n", getrows(MA), getcols(MA));
	for (i = 0; i != getrows(MA); ++i)
	{
		for (j = 0; j != getcols(MA); ++j)
			printf("%d\t", &getdata(MA, mx, pa, i, j));
		printf("\n");
	}
	printf("\n");
	printf("Matriz B: (%d x %d)\n", getrows(MB), getcols(MB));
	for (i = 0; i != getrows(MB); ++i)
	{
		for (j = 0; j != getcols(MB); ++j)
			printf("%d\t", &getdata(MB, mx, pb, i, j));
		printf("\n");
	}
	printf("\n");
}

int main(void)
{
	setrows(MA, 5)
	setcols(MA, 3)
	ALLOC_RC(MA, mx, pa)

	setrows(MB, 4)
	setcols(MB, 4)
	ALLOC_RC(MB, mx, pb)

	/* DimA = 5x3 , DimB = 4x4 */
	PrintData();
	
	setrows(MA, 7)
	REALLOC_ROWS(MA, mx, pa)

	setrows(MB, 2)
	REALLOC_ROWS(MB, mx, pb)

	/* DimA = 7x3, DimB = 2x4 */
	printf("\nRows updates:\n\n");
	PrintData();

	setcols(MA, 5)
	REALLOC_COLS(MA, mx, pa)

	setcols(MB, 7)
	REALLOC_COLS(MB, mx, pb)

	/* DimA = 7x5, DimB = 2x7 */
	printf("\nColumns updates:\n\n");
	PrintData();

	FREE_MEMORY_ALL(mx, pa)
	getchar();
	return EXIT_SUCCESS;
}   


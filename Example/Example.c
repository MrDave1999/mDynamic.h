#define MAX_MATRIX 2
#include "mDynamic.h"

enum
{
	MA,
	MB
};

void asignar(const unsigned char mid)
{
	int i, j;
	for (i = 0; i != getrows(mid); ++i)
	{
		for (j = 0; j != getcols(mid); ++j)
			sd(int, mid, i, j, 20);
	}
}

void PrintData(void)
{
	int i, j;
	printf("\n");
	printf("Matriz A: (%d x %d)\n", getrows(MA), getcols(MA));
	for (i = 0; i != getrows(MA); ++i)
	{
		for (j = 0; j != getcols(MA); ++j)
			printf("%d\t", &gd(int, MA, i, j));
		printf("\n");
	}
	printf("\n");
	printf("Matriz B: (%d x %d)\n", getrows(MB), getcols(MB));
	for (i = 0; i != getrows(MB); ++i)
	{
		for (j = 0; j != getcols(MB); ++j)
			printf("%d\t", &gd(int, MB, i, j));
		printf("\n");
	}
	printf("\n");
}

int main(void)
{
	setrows(MA, 5);
	setcols(MA, 3);
	alloc_m(int, MA);

	asignar(MA);

	setrows(MB, 4);
	setcols(MB, 4);
	alloc_m(int, MB);

	asignar(MB);

	PrintData();

	printf("\nRows AND columns updates:\n\n");

	setrows(MA, 7);
	setcols(MA, 5);
	realloc_m(int, MA, ROWS_COLS);

	asignar(MA);

	setrows(MB, 2);
	setcols(MB, 7);
	realloc_m(int, MB, ROWS_COLS);

	asignar(MB);

	PrintData();
	getchar();
	return EXIT_SUCCESS;
}


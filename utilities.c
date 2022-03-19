//Copyright Sturzoiu Ioan-Teofil 311CA 2022
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void free_matrix(int rows, int columns, matrix **a)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++)
			free(a[i][j].pixel);
		free(a[i]);
	}
	free(a);
}

matrix **read_matrix(int rows, int columns, int rgb, int ok, FILE *filename)
{
	matrix **a;
	a = malloc(rows * sizeof(matrix *));
	if (!a) {
		printf("Error memory allocation!\n");
		return NULL;
	}
	for (int i = 0; i < rows; i++) {
		a[i] = malloc(columns * sizeof(matrix *));
		if (!a[i]) {
			printf("Error memory allocation!\n");
			return NULL;
		}
		int nr_pixels = 1;
		if (rgb == 2)
			nr_pixels = 3;
		for (int j = 0; j < columns; j++) {
			a[i][j].pixel = malloc(nr_pixels * sizeof(double));
			if (!a[i][j].pixel) {
				printf("Error memory allocation!\n");
				return NULL;
			}
			for (int k = 0; k < nr_pixels; k++) {
				unsigned char buff;
				if (ok != 2) {
					fscanf(filename, "%hhu", &buff);
					a[i][j].pixel[k] = (double)buff;
				} else {
					fread(&buff, sizeof(unsigned char), 1, filename);
					a[i][j].pixel[k] = (double)buff;
				}
			}
		}
	}
	return a;
}

matrix **alloc_matrix(int rows, int columns, int rgb)
{
	matrix **a;
	a = malloc(rows * sizeof(matrix *));
	if (!a) {
		printf("Error memory allocation!\n");
		return NULL;
	}
	for (int i = 0; i < rows; i++) {
		a[i] = malloc(columns * sizeof(matrix *));
		if (!a[i]) {
			printf("Error memory allocation!\n");
			return NULL;
		}
		int nr_pixels = 1;
		if (rgb == 2)
			nr_pixels = 3;
		for (int j = 0; j < columns; j++) {
			a[i][j].pixel = malloc(nr_pixels * sizeof(double));
			if (!a[i][j].pixel) {
				printf("Error memory allocation!\n");
				return NULL;
			}
		}
	}
	return a;
}

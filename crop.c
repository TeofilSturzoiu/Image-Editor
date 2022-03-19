//Copyright Sturzoiu Ioan-Teofil 311CA 2022
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void crop_photo(photo_struct *photo)
{
	if (!(*photo).photo_matrix) {
		printf("No image loaded\n");
		return;
	}

	int rows = (*photo).y2 - (*photo).y1;
	int columns = (*photo).x2 - (*photo).x1;
	matrix **a;
	a = malloc(rows * sizeof(matrix *));

	for (int i = 0; i < rows; i++) {
		a[i] = malloc(columns * sizeof(matrix *));
		int nr_pixels = 1;

		if ((*photo).rgb == 2)
			nr_pixels = 3;

		for (int j = 0; j < columns; j++) {
			a[i][j].pixel = malloc(nr_pixels * sizeof(double));

			for (int k = 0; k < nr_pixels; k++)
				a[i][j].pixel[k] = (*photo).photo_matrix[i + (*photo).y1][j +
				(*photo).x1].pixel[k];
		}
	}

	free_matrix((*photo).rows, (*photo).columns, (*photo).photo_matrix);
	(*photo).photo_matrix = a;
	(*photo).rows = rows;
	(*photo).columns = columns;
	(*photo).x1 = (*photo).y1 = 0;
	(*photo).x2 = columns;
	(*photo).y2 = rows;
	
	printf("Image cropped\n");
}

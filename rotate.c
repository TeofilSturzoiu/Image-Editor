//Copyright Sturzoiu Ioan-Teofil 311CA 2022
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void reverse_rows(photo_struct *photo)
{
	int rows, columns, selection = 0;

	if ((*photo).x1 == -1 ||
		(((*photo).y2 - (*photo).y1 == (*photo).rows) &&
		((*photo).x2 - (*photo).x1 == (*photo).columns))) {
		rows = (*photo).rows;
		columns = (*photo).columns;
	} else {
		rows = (*photo).y2 - (*photo).y1;
		columns = (*photo).x2 - (*photo).x1;
		selection = 1;
	}

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns / 2; j++) {
			if (selection == 1) {
				matrix aux = (*photo).photo_matrix[i +
				(*photo).y1][j + (*photo).x1];
				(*photo).photo_matrix[i + (*photo).y1][j + (*photo).x1] =
						(*photo).photo_matrix[i + (*photo).y1][columns -
						 j + (*photo).x1 - 1];
				(*photo).photo_matrix[i + (*photo).y1][columns - j
				 + (*photo).x1 - 1] = aux;
			} else {
				matrix aux = (*photo).photo_matrix[i][j];
				(*photo).photo_matrix[i][j] =
				(*photo).photo_matrix[i][columns - j - 1];
				(*photo).photo_matrix[i][columns - j - 1] = aux;
			}
		}
	}
}

void transpose_matrix(photo_struct *photo)
{
	// Initializing a new matrix with number of rows and columns
	int selection = 0;
	matrix **new_matrix;
	int number_rows, number_columns;
	if ((*photo).x1 == -1 ||
	    (((*photo).y2 - (*photo).y1 == (*photo).rows) &&
	    ((*photo).x2 - (*photo).x1 == (*photo).columns))) {
		selection = 0;
		number_rows = (*photo).columns;
		number_columns = (*photo).rows;
	} else {
		selection = 1;
		number_rows = (*photo).x2 - (*photo).x1;
		number_columns = (*photo).y2 - (*photo).y1;
	}
	new_matrix = alloc_matrix(number_rows, number_columns, (*photo).rgb);

	// Copying the elements in the new transposed matrix
	int nr_pixels = 1;
	if ((*photo).rgb == 2)
		nr_pixels = 3;
	for (int i = 0; i < number_columns; i++) {
		for (int j = 0; j < number_rows; j++) {
			for (int k = 0; k < nr_pixels; k++) {
				if (selection == 0) {
					new_matrix[j][i].pixel[k] =
					(*photo).photo_matrix[i][j].pixel[k];
				} else {
					new_matrix[j][i].pixel[k] =
							(*photo).photo_matrix[i + (*photo).y1][j +
							(*photo).x1].pixel[k];
				}
			}
		}
	}

	if (selection == 0) {
		// Freeing the memory used for the old matrix
		free_matrix((*photo).rows, (*photo).columns, (*photo).photo_matrix);

		// Storing the new transposed matrix
		(*photo).rows = number_rows;
		(*photo).columns = number_columns;
		(*photo).photo_matrix = new_matrix;
		(*photo).x1 = (*photo).y1 = 0;
		(*photo).x2 = number_columns;
		(*photo).y2 = number_rows;
	} else {
		for (int i = 0; i < number_columns; i++) {
			for (int j = 0; j < number_rows; j++) {
				for (int k = 0; k < nr_pixels; k++) {
					(*photo).photo_matrix[i + (*photo).y1][j +
								(*photo).x1].pixel[k] =
						new_matrix[i][j].pixel[k];
				}
			}
		}

		free_matrix(number_rows, number_columns, new_matrix);
	}
}

void rotate_photo(photo_struct *photo, char *details)
{
	if (!(*photo).photo_matrix) {
		printf("No image loaded\n");
		return;
	}

	if (!((*photo).y2 - (*photo).y1 == (*photo).rows &&
		  (*photo).x2 - (*photo).x1 == (*photo).columns)) {
		if (((*photo).y2 - (*photo).y1) != (*photo).x2 - (*photo).x1) {
			printf("The selection must be square\n");
			return;
		}
	}

	//Sau ii pun strstr("+90")?
	if (strcmp(details, "0") == 0) {
		printf("Rotated %s\n", details);
		return;
	}

	if (strcmp(details, "+90") == 0 || strcmp(details, "90") == 0) {
		transpose_matrix(photo);
		reverse_rows(photo);
		printf("Rotated %s\n", details);
		return;
	}

	if (strcmp(details, "+180") == 0 || strcmp(details, "180") == 0) {
		transpose_matrix(photo);
		reverse_rows(photo);
		transpose_matrix(photo);
		reverse_rows(photo);
		printf("Rotated %s\n", details);
		return;
	}

	if (strcmp(details, "+270") == 0 || strcmp(details, "270") == 0) {
		reverse_rows(photo);
		transpose_matrix(photo);
		printf("Rotated %s\n", details);
		return;
	}

	if (strcmp(details, "+360") == 0 || strcmp(details, "360") == 0) {
		printf("Rotated %s\n", details);
		return;
	}

	if (strcmp(details, "-90") == 0) {
		reverse_rows(photo);
		transpose_matrix(photo);
		printf("Rotated %s\n", details);
		return;
	}

	if (strcmp(details, "-180") == 0) {
		reverse_rows(photo);
		transpose_matrix(photo);
		reverse_rows(photo);
		transpose_matrix(photo);
		printf("Rotated %s\n", details);
		return;
	}

	if (strcmp(details, "-270") == 0) {
		transpose_matrix(photo);
		reverse_rows(photo);
		printf("Rotated %s\n", details);
		return;
	}

	if (strcmp(details, "-360") == 0) {
		printf("Rotated %s\n", details);
		return;
	}
	
	printf("Unsupported rotation angle\n");
}

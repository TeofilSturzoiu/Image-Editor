//Copyright Sturzoiu Ioan-Teofil 311CA 2022
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

void get_kernel_matrix(char *details, double kernel_matrix[3][3])
{
	double edge_detection[3][3] = {{-1., -1., -1.},
							{-1., 8., -1.},
							{-1., -1., -1.}};
	double sharpen[3][3] = {{0., -1., 0.},
							{-1., 5., -1.},
							{0., -1., 0.}};
	double box_blur[3][3] = {{1, 1, 1},
							{1, 1, 1},
							{1, 1, 1}};
	double gaussian_blur[3][3] = {{1, 2, 1},
							{2, 4, 2},
							{1, 2, 1}};

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (strcmp(details, "EDGE") == 0) {
				kernel_matrix[i][j] = edge_detection[i][j];
			} else {
				if (strcmp(details, "SHARPEN") == 0) {
					kernel_matrix[i][j] = sharpen[i][j];
				} else {
					if (strcmp(details, "BLUR") == 0)
						kernel_matrix[i][j] = (double)1 / 9 *
						box_blur[i][j];
					else
						kernel_matrix[i][j] = (double)1 / 16 *
						gaussian_blur[i][j];
				}
			}
		}
	}
}

double apply_on_pixel(photo_struct photo,
					  int row,
					  int column,
					  int channel,
					  char *details)
{
	double sum = 0;
	double kernel[3][3];
	get_kernel_matrix(details, kernel);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			double aux =
				photo.photo_matrix[i + row - 1][j + column - 1].pixel[channel];
			aux = aux * (double)kernel[i][j];
			sum += aux;
		}
	}

	if (sum < 0)
		sum = 0;
	if (sum > 255)
		sum = 255;

	return (double)sum;
}

void apply_photo(photo_struct *photo, char *details)
{
	if (!(*photo).photo_matrix) {
		printf("No image loaded\n");
		return;
	}

	if (strcmp(details, "EDGE") && strcmp(details, "SHARPEN") &&
		strcmp(details, "BLUR") && strcmp(details, "GAUSSIAN_BLUR")) {
		printf("APPLY parameter invalid\n");
		return;
	}

	if ((*photo).rgb == 1) {
		printf("Easy, Charlie Chaplin\n");
		return;
	}

	// Verify if the photo is coloured.
	int temp_y1, temp_y2, temp_x1, temp_x2;
	matrix **new_matrix;
	temp_y1 = (*photo).y1;
	temp_y2 = (*photo).y2;
	temp_x1 = (*photo).x1;
	temp_x2 = (*photo).x2;

	if ((*photo).y1 == 0)
		temp_y1 = 1;
	if ((*photo).y2 == (*photo).rows)
		temp_y2 = (*photo).rows - 1;
	if ((*photo).x1 == 0)
		temp_x1 = 1;
	if ((*photo).x2 == (*photo).columns)
		temp_x2 = (*photo).columns - 1;

	new_matrix = alloc_matrix((*photo).rows, (*photo).columns, (*photo).rgb);
	
	for (int i = temp_y1; i < temp_y2; i++) {
		for (int j = temp_x1; j < temp_x2; j++) {
			for (int k = 0; k < 3; k++)
				new_matrix[i][j].pixel[k] =
					apply_on_pixel((*photo), i, j, k, details);
		}
	}

	for (int i = temp_y1; i < temp_y2; i++) {
		for (int j = temp_x1; j < temp_x2; j++) {
			for (int k = 0; k < 3; k++) {
				(*photo).photo_matrix[i][j].pixel[k] =
					new_matrix[i][j].pixel[k];
			}
		}
	}

	free_matrix((*photo).rows, (*photo).columns, new_matrix);
	printf("APPLY %s done\n", details);
}

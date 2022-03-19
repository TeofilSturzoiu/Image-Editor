//Copyright Sturzoiu Ioan-Teofil 311CA 2022
#ifndef _PHOTO_H
#define _PHOTO_H

typedef struct {
	double *pixel; //maybe make it unsigned (or unsigned char).
} matrix;

typedef struct {
	matrix **photo_matrix;
	// maybe move coordinates into SELECT / LOAD function
	int x1, y1, x2, y2, rows, columns, max_value;
	//char type[3];
	int rgb, ok;
} photo_struct;

/**
 * @brief Function that frees the matrix
 *
 * @param rows Number of rows
 *
 * @param columns Number of columns
 *
 * @param a Matrix of pixels
 */
void free_matrix(int rows, int columns, matrix **a);

/**
 * @brief Function that frees the matrix
 *
 * @param rows Number of rows
 *
 * @param columns Number of columns
 *
 * @param rgb Variable I use to check if the photo is RGB or not
 *
 * @param ok Variable to check if the photo should be stored as ASCII
 *
 * @param filename The file where I store the photo
 */
matrix **read_matrix(int rows, int columns, int rgb, int ok, FILE *filename);

/**
 * @brief Function that allocates the matrix
 *
 * @param rows Number of rows
 *
 * @param columns Number of columns
 *
 * @param rgb Variable I use to check if the photo is RGB or not
 */
matrix **alloc_matrix(int rows, int columns, int rgb);

#endif

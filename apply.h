//Copyright Sturzoiu Ioan-Teofil 311CA 2022
#ifndef _APPLY_H
#define _APPLY_H

/**
 * @brief Function that decides the kernel matrix
 *
 * @param details String that represents the name of the filter
 *
 * @param kernel_matrix Returned kernel matrix
 *
 */
void get_kernel_matrix(char *details, double kernel_matrix[3][3]);

/**
 * @brief Function that applies the filter on each filter
 *
 * @param photo Struct that stores the photo
 *
 * @param row The row we modify
 *
 * @param column The column we modify
 *
 * @param channel The R/G/B channel we modify
 *
 * @param details String that represents the name of the filter
 *
 */
double apply_on_pixel(photo_struct photo, int row,
					  int column, int channel, char *details);

/**
 * @brief Function that applies the filter on all photo
 *
 * @param details String that represents the name of the filter
 *
 */
void apply_photo(photo_struct *photo, char *details);

#endif

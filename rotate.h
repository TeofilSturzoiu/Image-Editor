//Copyright Sturzoiu Ioan-Teofil 311CA 2022
#ifndef _ROTATE_H
#define _ROTATE_H

/**
 * @brief Function that reverses all the rows of a matrix
 *
 * @param photo Struct that stores the photo
 *
 */
void reverse_rows(photo_struct *photo);

/**
 * @brief Function that transposes the matrix
 *
 * @param photo Struct that stores the photo
 *
 */
void transpose_matrix(photo_struct *photo);

/**
 * @brief Function that rotates all photo
 *
 * @param photo Struct that stores the photo
 *
 * @param details String that gets the degrees for rotation
 */
void rotate_photo(photo_struct *photo, char *details);

#endif

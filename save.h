//Copyright Sturzoiu Ioan-Teofil 311CA 2022
#ifndef _SAVE_H
#define _SAVE_H

/**
 * @brief Function that prints the photo
 *
 * @param a The struct where I stored the matrix
 *
 * @param filename String that represents the name of the file
 *
 * @param ascii int that checks if the file is ASCII or not
 */
void print_photo(photo_struct a, FILE *filename, int ascii);

/**
 * @brief Function that saves the photo in output file
 *
 * @param photo The struct where I stored the matrix
 *
 * @param details String that represents the name of the file where I store
 * the matrix
 *
 */
void save_photo(photo_struct photo, char *details);

#endif

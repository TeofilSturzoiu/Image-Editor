//Copyright Sturzoiu Ioan-Teofil 311CA 2022
#ifndef _LOAD_H
#define _LOAD_H

/**
 * @brief Function to get type of file (ascii/binary)
 *
 * @param type string I received from file
 *
 * @return An integer for ascii/binary file
 */
int get_type_of_file(char *type);

/**
 * @brief Function to get type of photo (ppm/pgm)
 *
 * @param type string I received from file
 *
 * @return An integer for coloured/gray photo
 */
int get_type_of_photo(char *type);

/**
 * @brief Function to read comments inside a file
 *
 * @param filename String that represents the name of the file
 *
 */
void read_comment(FILE *filename);

/**
 * @brief Function to check if there are comments inside a file
 *
 * @param filename String that represents the name of the file
 *
 * @param verify int that checks if there are more comments
 */
void check_comments(FILE *filename, int *verify);

/**
 * @brief Function to load the photo
 *
 * @param photo The struct where I stored the matrix
 *
 * @param name_string String that represents the name of the file
 */
void load_image(photo_struct *photo, char *name_string);

#endif

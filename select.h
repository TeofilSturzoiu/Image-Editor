//Copyright Sturzoiu Ioan-Teofil 311CA 2022
#ifndef _SELECT_H
#define _SELECT_H

/**
 * @brief Function that checks if the input is wrong
 *
 * @param coordinates String that stores the coordinates
 */
int check_any_letters(char *coordinates);

/**
 * @brief Function that selects the given pixels
 *
 * @param photo Struct that stores all details of the photo
 *
 * @param coordinates String that stores the coordinates
 */
void select_photo(photo_struct *photo, char *coordinates);

#endif

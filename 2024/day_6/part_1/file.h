
#ifndef FILE_H
#define FILE_H


/**
 * \brief get the width of the field
 * \param filename name of the file
 */
int f_get_width_of_field(char* filename);

/**
 * \brief get the height of the field
 * \param filename name of the file
 */
int f_get_height_of_filed(char* filename);

/**
 * \brief fill the 2d array with the contents of the file
 * \param filename file to read from
 * \param array the array to fill the data into
 * \param width width of the 2d array
 * \param height height of the 2d array
 */
void f_fill_field(char* filename, int* array, int width, int height);

#endif

#ifndef FILE_H
#define FILE_H

#include "vector.h"

/**
 * \brief get the size of the field
 * \param filename name of the file to open
 * \return vector of the size
 */
vector_t f_get_sie_of_field(char* filename);

/**
 * \brief fill the filed from a file
 * \param filename name of the file
 * \param field field to fill
 * \param size size of the field
 */
void f_fill_field(char* filename, int field[], vector_t size);

/**
 * \brief count the amount of times a number is in a field
 * \param field field to look through
 * \param size size of the field
 * \param number number to look for
 * \return amount of times number shows up in the field
 */
int f_count_numbers(int field[], vector_t size, int number);


#endif
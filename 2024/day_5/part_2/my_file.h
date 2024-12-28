
#ifndef MY_FILE
#define MY_FILE

#include "linked.h"


/**
 * \brief find the amount of numbers in a comma separated line
 * \param line string to check
 */
int f_find_length_of_csl(char* line);


/**
 * \brief fill the line array
 * \param line string to parse
 * \param array array to fill
 * \param length length of the array
 */
void f_fill_line_array(char* line, int* array, int length);


/**
 * \brief get length of the sort array
 * \param filename name of the file 
 * \return length of the sort array
 */
int f_length_of_sort(char* filename);


/**
 * \brief fill the sort arrays
 * \param filename the filename of the file to open
 * \param first_numbers array for the first numbers
 * \param second_numbers array for the second numbers
 * \param length length of the arrays
 */
void f_fill_sort_arrays(char* filename, int* first_numbers, int* second_numbers, int length);



#endif
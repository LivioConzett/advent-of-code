
#ifndef GUARD_H
#define GUARD_H


typedef struct{
    int x;
    int y;
} vector_t;


enum characters{
    EMPTY = '.',
    BLOCK = '#',
    UP = '^',
    DOWN = 'v',
    LEFT = '<',
    RIGHT = '>'
};


/**
 * \brief print the vector
 * \param vector vector to print
 */
void g_print_vector(vector_t vector);


/**
 * \brief get the size of the field
 * \param filename name of the file
 */
vector_t g_get_size_of_field(char* filename);


/**
 * \brief fill the 2d array with the contents of the file
 * \param filename file to read from
 * \param array the array to fill the data into
 * \param size vector of the size of the field
 */
void g_fill_field(char* filename, char* array, vector_t size);


/**
 * \brief print out the 2d array
 * \param array array to print
 * \param size vector of the size
 */
void g_print_field(char* array, vector_t size);


/**
 * \brief find the position of the guard
 * \param array the field to search through
 * \param size size of the field
 * \return position of the guard. (-1,-1) if no guard was found.
 */
vector_t get_position_of_guard(char* array, vector_t size);

#endif

#ifndef FILE_H
#define FILE_H


typedef struct {
    int x;
    int y;
} vector_t;


enum Characters{
    EMPTY = '.',
    NODE = '#'
};


/**
 * \brief get the size of the field
 * \param filename name of the file
 * \return vector with the size of the field
 */
vector_t f_get_field_size(char* filename);

/**
 * \brief fill the field array from the file
 * \param filename name of the file
 * \param field field to fill
 * \param size size of the field
 */
void f_fill_field(char* filename, char field[], vector_t size);

/**
 * \brief empty the field array
 * \param field field to fill
 * \param size size of the field
 */
void f_empty_field(char field[], vector_t size);



#endif
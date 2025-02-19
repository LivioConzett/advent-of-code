
#ifndef GUARD_H
#define GUARD_H


typedef struct{
    int x;
    int y;
} vector_t;


enum Characters{
    EMPTY = '.',
    BLOCK = '#',
    TOUCHED = 'x',
    TRIED = '+',
    OBSTACLE = 'O',
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
 * \param field the array to fill the data into
 * \param size vector of the size of the field
 */
void g_fill_field(char* filename, char* field, vector_t size);


/**
 * \brief print out the 2d array
 * \param field array to print
 * \param size vector of the size
 */
void g_print_field(char* field, vector_t size);


/**
 * \brief find the position of the guard
 * \param field the field to search through
 * \param size size of the field
 * \return position of the guard. (-1,-1) if no guard was found.
 */
vector_t get_position_of_guard(char* field, vector_t size);

/**
 * \brief move the guard by one. Updates the position of the guard.
 * \param field the field
 * \param size the size of the field
 * \param position the position of the guard
 * \param mark_touched 1 the fields that are touched are marked, 0 they ar not
 * \return 1 if the guard left the field, else 0
 */
int g_move(char* field, vector_t size, vector_t* position, int mark_touched);

/**
 * \brief count the number of touched fields
 * \param field field to check
 * \param size size of the field
 * \return number of fields touched
 */
int g_count_touched_fields(char* field, vector_t size);

/**
 * \brief place the guard back to his original place
 * \param field field playing
 * \param size size of the field
 * \param position position to place the guard at
 * \param guard character of the guard.
 */
void g_set_guard(char* field, vector_t size, vector_t position, char guard);

/**
 * \brief set an obstacle on a touched field.
 * \param field field playing
 * \param size size of the filed
 * \return 1 if an obstacle was set, 0 if not (no more places to place an obstacle)
 */
int g_set_obstacle(char* field, vector_t size);

#endif

#ifndef VECTOR_H
#define VECTOR_H

typedef struct {
    int x;
    int y;
} vector_t;


static const vector_t  N_V = {0,-1};
static const vector_t NE_V = {1,-1};
static const vector_t  E_V = {1,0};
static const vector_t SE_V = {1,1};
static const vector_t  S_V = {0,1};
static const vector_t SW_V = {-1,1};
static const vector_t  W_V = {-1,0};
static const vector_t NW_V = {-1,-1};


/**
 * \brief print the vector
 * \param vector vector to print
 * \param newline print a new line or not
 */
void v_print(const vector_t* vector, int newline);

/**
 * \brief add the second vector to the first
 * \param one first vector
 * \param two second vector
 */
void v_add(vector_t* one, vector_t* two);

/**
 * \brief subtract the second vector from the first
 * \param one first vector
 * \param two second vector
 */
void v_subtract(vector_t* one, vector_t* two);

/**
 * \brief multiply the vector by a number
 * \param vector vector to multiply
 * \param multiplier number to multiply by
 */
void v_multiply(vector_t* vector, int multiplier);

/**
 * \brief divide the vector by a number
 * \param vector vector to divide
 * \param divisor number to divide by
 */
void v_divide(vector_t* vector, int divisor);

/**
 * \brief get the higher of the two numbers in the vector
 * \param vector vector to get number from
 * \return the higher of the two numbers in the vector
 */
int v_get_higher(vector_t* vector);

/**
 * \brief get the lower of the two numbers in the vector
 * \param vector vector to get number from
 * \return the lower of the two numbers in the vector
 */
int v_get_lower(vector_t* vector);

/**
 * \brief check if the vector is within some bounds
 * \param vector vector to check
 * \param bounds the bounds to check if the vector is in
 * \return 1 if vector is in bounds, else 0
 */
int v_in_bound(vector_t* vector, vector_t* bounds);

/**
 * \brief flip the vector
 * \param vector vector to flip
 */
void v_flip(vector_t* vector);

/**
 * \brief check if two vectors are the same
 * \param one first vector
 * \param two second vector
 * \return 1 if both vectors are the same, else 0
 */
int v_equal(vector_t* one, vector_t* two);

/**
 * \brief get the magnitude of a vector
 * \param vector vector to get magnitude of
 * \return magnitude of vector
 */
double v_get_magnitude(vector_t* vector);

/**
 * \brief get the unit vector of a vector
 * \param vector vector to get unit vector from
 * \return unit vector
 */
vector_t v_get_unit_vector(vector_t* vector);

/**
 * \brief get the direction of the vector in a grid system
 * \param vector vector to get the direction from
 * \return vector of the direction
 */
vector_t v_get_direction(vector_t* vector);


#endif

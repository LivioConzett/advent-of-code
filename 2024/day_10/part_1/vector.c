
#include <stdio.h>
#include <math.h>

#include "vector.h"

/**
 * \brief get the Greatest Common Denominator of two numbers
 * \param one first number
 * \param two second number
 * \return gcd of the two numbers
 */
int v_gcd(int one, int two){

    int result;

    if(one < two) result = one;
    else result = two;

    while(result > 0){
        if(one % result == 0 && two % result == 0){
            break;
        }
        result --;
    }
    return result;
}

/**
 * See header
 */
void v_print(const vector_t* vector, int newline){
    printf("%d : %d", vector->x, vector->y);
    if(newline) printf("\n");
}


/**
 * See header
 */
void v_add(vector_t* one, vector_t* two){
    one->x += two->x;
    one->y += two->y;
}

/**
 * See header
 */
vector_t v_add_n(vector_t* one, vector_t* two){

    vector_t new = {0,0};
    new.x = one->x + two->x;
    new.y = one->y + two->y;

    return new;
}


/**
 * See header
 */
void v_subtract(vector_t* one, vector_t* two){
    one->x -= two->x;
    one->y -= two->y;
}

/**
 * See header
 */
void v_multiply(vector_t* vector, int multiplier){
    vector->x *= multiplier;
    vector->y *= multiplier;
}

/**
 * See header
 */
void v_divide(vector_t* vector, int divisor){
    vector->x /= divisor;
    vector->y /= divisor;
}

/**
 * See header
 */
int v_get_higher(vector_t* vector){

    if(vector->x > vector->y) return vector->x;

    return vector->y;
}

/**
 * See header
 */
int v_get_lower(vector_t* vector){

    if(vector->x < vector->y) return vector->x;

    return vector->y;
}

/**
 * See header
 */
int v_in_bound(vector_t* vector, vector_t* bounds){

    if(vector->x < 0 || vector->x >= bounds->x) return 0;
    if(vector->y < 0 || vector->y >= bounds->y) return 0;
    return 1;
}

/**
 * See header
 */
void v_flip(vector_t* vector){
    v_multiply(vector,-1);
}

/**
 * See header
 */
int v_equal(vector_t* one, vector_t* two){
    return one->x == two->x && one->y == two->y;
}

/**
 * See header
 */
double v_get_magnitude(vector_t* vector){
    return sqrt(pow(vector->x,2) + pow(vector->y, 2));
}

/**
 * See header
 */
vector_t v_get_unit_vector(vector_t* vector){
    vector_t result;

    double magnitude = v_get_magnitude(vector);

    result.x = vector->x / magnitude;
    result.y = vector->y / magnitude;

    return result;
}

/**
 * See header
 */
vector_t v_get_direction(vector_t* vector){

    int denominator = v_gcd(vector->x, vector->y);

    vector_t result = *vector;

    v_divide(&result, denominator);

    return result;
}


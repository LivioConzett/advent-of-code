
#include <stdio.h>

#include "vector.h"


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


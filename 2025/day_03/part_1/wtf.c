

/**
 * gcc -std=c99 -Wall -Werror
 */

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef struct{
    int columns;
    int rows;
} array_size_t;


int main(int argc, char* argv[]){


    // char* string = "1234";


    array_size_t array_size = {4,3};

    printf("%d %d\n", array_size.rows, array_size.columns);

    int array[array_size.rows * array_size.columns];

    // int array[3][4];

    for(int i = 0; i < 3; i++){
        for(int ii = 0; ii < 4; ii++){
            // printf("%c",string[ii]);
            array[(i * array_size.columns) + ii] = ii;
        }
        printf("-\n");
    }


    for(int i = 0; i < 3; i++){
        for(int ii = 0; ii < 4; ii++){
            printf("%d", array[(i * array_size.columns)+ii]);
            // printf("%d", array[i][ii]);
        }
        printf("\n");
    }

    return 0;
}

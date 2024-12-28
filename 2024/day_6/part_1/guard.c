
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "guard.h"


/**
 * See header
 */
void g_print_vector(vector_t vector){
    printf("%d : %d", vector.x, vector.y);
}


/**
 * See header
 */
vector_t g_get_size_of_field(char* filename){

    FILE* file_ptr;
    file_ptr = fopen(filename,"r");

    // make sure the file could be opend
    if (file_ptr == NULL){
        printf("Cannot open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    size_t read = 0;
    char* line = NULL;
    size_t len = 0;

    vector_t size;
    size.x = 0;
    size.y = 0;

    while(read != -1){
        
        read = getline(&line, &len, file_ptr);
        if(read == -1) break;

        size.y ++;
        
        if(strlen(line) - 1 > size.x) size.x = strlen(line) - 1;

    }

    return size;
}

/**
 * See header
 */
void g_fill_field(char* filename, char* array, vector_t size){

    FILE* file_ptr;
    file_ptr = fopen(filename,"r");

    // make sure the file could be opend
    if (file_ptr == NULL){
        printf("Cannot open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    size_t read = 0;
    char* line = NULL;
    size_t len = 0;

    int y = 0;

    while(read != -1){
        
        read = getline(&line, &len, file_ptr);

        if(read == -1) break;

        for(int x = 0; x < size.x; x++){
            array[(y * size.x) + x] = line[x];
        }

        y++;

        if(y > size.y) break;
    }
}


/**
 * See header
 */
void g_print_field(char* array, vector_t size){

    for(int y = 0; y < size.y; y++){
        for(int x = 0; x < size.x; x++){
            printf("%c",array[(y * size.x) + x]);
        }
        printf("\n");
    }
}


/**
 * See header
 */
vector_t get_position_of_guard(char* array, vector_t size){

    vector_t position = {-1,-1};

    for(int y = 0; y < size.y; y++){
        for(int x = 0; x < size.x; x++){
            char c = array[(y * size.x) + x];
            if(c == UP || c == DOWN || c == LEFT || c == RIGHT){
                position.x = x;
                position.y = y;
                break;
            }
        }
    }

    return position;
}


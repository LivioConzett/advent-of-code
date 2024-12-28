
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"


/**
 * See header
 */
int f_get_width_of_field(char* filename){

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

    while(read != -1){
        
        read = getline(&line, &len, file_ptr);
        if(read == -1) break;

        // -1 because of the newline character
        return strlen(line) - 1;

    }

    return 0;
}


/**
 * See header
 */
int f_get_height_of_filed(char* filename){

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
    int counter = 0;

    while(read != -1){
        
        read = getline(&line, &len, file_ptr);
        if(read == -1) break;
        counter++;
    }

    return counter;
}

/**
 * See header
 */
void f_fill_field(char* filename, int* array, int width, int height){

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

    while(read != -1){
        
        read = getline(&line, &len, file_ptr);
        if(read == -1) break;

        

    }
}

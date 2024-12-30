
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"




/**
 * See header
 */
vector_t f_get_field_size(char* filename){

    FILE* file;

    file = fopen(filename, "r");

    if(file == NULL){
        printf("could not open file\n");
        exit(EXIT_FAILURE);
    }

    char* line = NULL;
    size_t len = 0;

    vector_t size = {0,0};

    while((getline(&line, &len, file)) != -1){

        int len = strlen(line);

        // -1 because we don't want the newline
        if(len > size.x) size.x = len-1;

        size.y++;
    }

    return size;
}


/**
 * See header
 */
void f_fill_field(char* filename, char field[], vector_t size){

    FILE* file;

    file = fopen(filename, "r");

    if(file == NULL){
        printf("cannot open file\n");
        exit(EXIT_FAILURE);
    }

    char* line = NULL;
    size_t len;

    int y = 0;
    int x = 0;

    while((getline(&line, &len, file)) != -1){

        for(int i = 0; i < size.x; i++){
            field[(y * size.x) + i] = line[i];
        }

        y++;
    }
}

/**
 * See header
 */
void f_empty_field(char field[], vector_t size){

    for(int y = 0; y < size.y; y++){
        for(int x = 0; x < size.x; x++){
            field[(y * size.x) + x] = EMPTY;
        }
    }
}



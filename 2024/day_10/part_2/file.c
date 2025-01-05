
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"


/**
 * See header
 */
vector_t f_get_sie_of_field(char* filename){

    FILE* file = fopen(filename, "r");

    if(file == NULL){
        printf("Can not open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    size_t len = 0;
    char* line = NULL;

    vector_t size = {0,0};


    while(getline(&line, &len, file) != -1){
        
        // -1 because we don't want the newline
        if(strlen(line) - 1 >= size.x) size.x = strlen(line) - 1;

        size.y++;
    }

    fclose(file);

    return size;
}

/**
 * See header
 */
void f_fill_field(char* filename, int field[], vector_t size){

    FILE* file = fopen(filename, "r");

    if(file == NULL){
        printf("Can not open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    size_t len = 0;
    char* line = NULL;

    vector_t counter = {0,0};


    while(getline(&line, &len, file) != -1){
        
        // -1 because we don't want the newline character
        int len = strlen(line) - 1;

        for(int i = 0; i < len; i++){
            char c = line[i];
            
            field[(counter.y * size.x) + counter.x] = atoi(&c);

            counter.x++;
            if(counter.x >= size.x) break;
        }

        counter.x = 0;
        counter.y++;
        if(counter.y >= size.y) break;
    }

    fclose(file);
}

/**
 * See header
 */
int f_count_numbers(int field[], vector_t size, int number){

    int counter = 0;

    for(int y = 0; y < size.y; y++){
        for(int x = 0; x < size.x; x++){
            if(field[(y * size.x) + x] == number) counter++;
        }
    }

    return counter;
}



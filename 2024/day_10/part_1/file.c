
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

    return size;
}

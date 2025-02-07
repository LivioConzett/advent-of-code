
#define  _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "vector.c"



/**
 * Get the file size of a field
 */
vector_t get_field_size(FILE* file){

    size_t len = 0;
    char* line = NULL;

    vector_t size = {0,0};

    while(getline(&line, &len, file) != -1){
        
        // -1 because we don't want the newline
        if(strlen(line) - 1 >= size.x) size.x = strlen(line) - 1;

        size.y++;
    }

    free(line);

    return size;
}






/**
 * Main entry point
 */
int main(int argc, char* argv[]){

    char* filename = argv[1];

    FILE* file = fopen(filename, "r");
    if(file == NULL){
        printf("Error opening file %s\n", filename);
        exit(0);
    }


    vector_t size = get_field_size(file);

    v_print(&size, 1);


    fclose(file);

    return 0;
}


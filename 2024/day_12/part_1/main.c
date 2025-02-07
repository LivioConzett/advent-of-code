
#define  _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "vector.c"



/**
 * Get the file size of a field
 */
vector_t get_field_size(char* filename){

    FILE* file = fopen(filename, "r");
    if(file == NULL){
        printf("Error opening file %s\n", filename);
        exit(0);
    }

    size_t len = 0;
    char* line = NULL;

    vector_t size = {0,0};

    while(getline(&line, &len, file) != -1){
        
        // -1 because we don't want the newline
        if(strlen(line) - 1 >= size.x) size.x = strlen(line) - 1;

        size.y++;
    }

    free(line);

    fclose(file);

    return size;
}

/**
 * Fill the field 
 */
void fill_field(char* field, vector_t size, char* filename){

    FILE* file = fopen(filename, "r");
    if(file == NULL){
        printf("Error opening file %s\n", filename);
        exit(0);
    }

    size_t len = 0;
    char* line = NULL;

    vector_t counter = {0,0};


    while(getline(&line, &len, file) != -1){

        // -1 because we don't want the newline character
        int len = strlen(line) - 1;

        for(int i = 0; i < len; i++){
            char c = line[i];
            field[(counter.y * size.x) + counter.x] = c;

            counter.x++;
            if(counter.x >= size.x) break;
        }

        counter.x = 0;
        counter.y++;
        if(counter.y >= size.y) break;
    }

    free(line);
    fclose(file);
}


/**
 * Walk over the connected fields
 */
int16_t walk(char* field, int8_t* visited, vector_t size, vector_t current_pos, char current_char){

    int16_t result = 1;

    // set the cell as visited
    visited[(current_pos.y * size.x) + current_pos.x] = 1;

    for(int8_t i = 0; i < 4; i++){

        vector_t search = v_add_n(&current_pos, &NESW[i]);

        // v_print(&search, 1);

        if(!v_in_bound(&search, &size)) continue;

        if(field[(search.y * size.x) + search.x] != current_char) continue;

        if(visited[(search.y * size.x) + search.x]) continue;

        result += walk(field, visited, size, search, current_char);
    }

    return result;
}


/**
 * Main entry point
 */
int main(int argc, char* argv[]){

    char* filename = argv[1];


    vector_t size = get_field_size(filename);

    v_print(&size, 1);

    // game field
    char field[size.x * size.y];
    // array to check off what was visited already
    int8_t visited[size.x * size.y];


    // init the visited with 0
    for(int y = 0; y < size.y; y++){
        for(int x = 0; x < size.x; x++){
            visited[(y * size.x) + x] = 0;
        }
    }

    // fill the field
    fill_field(field, size, filename);


    // go through the array
    for(int y = 0; y < size.y; y++){
        for(int x = 0; x < size.x; x++){

            if(visited[(y * size.x) + x]) continue;

            printf("%d\n", walk(field, visited, size, (vector_t) {x,y}, field[(y * size.x) + x]));

        }
    }



    return 0;
}


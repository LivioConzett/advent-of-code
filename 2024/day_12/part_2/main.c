
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
vector_t walk(char* field, int8_t* visited, int8_t* visited_perimeter, vector_t size, vector_t current_pos, char current_char, int8_t perimeter_done){
    
    vector_t result = {1, 0};

    if(!perimeter_done){
        walk_perimeter(field, visited_perimeter, size, current_pos, current_char, 1);
        perimeter_done = 1;
    }


    // set the cell as visited
    visited[(current_pos.y * size.x) + current_pos.x] = 1;

    for(int8_t i = 0; i < 4; i++){

        vector_t search = v_add_n(&current_pos, &NESW[i]);

        // v_print(&search, 1);

        if(!v_in_bound(&search, &size)){
            // add a fence
            result.y++;
            continue;
        }

        if(field[(search.y * size.x) + search.x] != current_char){
            // add a fence
            result.y++;
            continue;
        }

        if(visited[(search.y * size.x) + search.x]) continue;

        vector_t new = walk(field, visited, visited_perimeter, size, search, current_char, perimeter_done);
        v_add(&result, &new);
    }

    return result;
}


/**
 * Walk around the perimeter and count the sides
 */
int16_t walk_perimeter(char* field, int8_t* visited_perimeter, vector_t size, vector_t current_pos, char current_char, int8_t direction){
    
    int16_t result = 1;

    int8_t left_direction = (direction + 3) % 4;
    int8_t right_direction = (direction + 1) % 4;
    vector_t cw = NESW[left_direction];

    vector_t on_the_left = v_add_n(&current_pos, &cw);
    vector_t in_front = v_add_n(&current_pos, &NESW[direction]);

    // if the left is in bound
    if(v_in_bound(&on_the_left, &size) && field[(on_the_left.y * size.x) + on_the_left.x] == current_char){

        // go to that field and try again.
        result += walk_perimeter(field, visited_perimeter, size, current_pos, current_char, left_direction);

    }
    // if the left is not in bound or the left is not 
    else if((!v_in_bound(&on_the_left, &size) || !field[(on_the_left.y * size.x) + on_the_left.x] == current_char) 
                && field[(in_front.y * size.x) + in_front.x] == current_char){
        
        walk_perimeter(field, visited_perimeter, size, current_pos, current_char, direction);

    }
    else if((!v_in_bound(&on_the_left, &size) || !field[(on_the_left.y * size.x) + on_the_left.x] == current_char) 
                && field[(in_front.y * size.x) + in_front.x] != current_char){
        
        result += walk_perimeter(field, visited_perimeter, size, current_pos, current_char, right_direction);
    }

    return result;
}


/**
 * Main entry point
 */
int main(int argc, char* argv[]){

    char* filename = argv[1];


    vector_t size = get_field_size(filename);

    //v_print(&size, 1);

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

    int8_t visited_perimeter[size.x * size.y];

    // init the visited_perimeter with 0
    for(int y = 0; y < size.y; y++){
        for(int x = 0; x < size.x; x++){
            visited_perimeter[(y * size.x) + x] = 0;
        }
    }

    // fill the field
    fill_field(field, size, filename);

    int32_t result = 0;

    // go through the array
    for(int y = 0; y < size.y; y++){
        for(int x = 0; x < size.x; x++){

            if(visited[(y * size.x) + x]) continue;

            vector_t amount = walk(field, visited, visited_perimeter, size, (vector_t) {x,y}, field[(y * size.x) + x], 0);

            result += amount.x * amount.y;
        }
    }

    printf("%d\n", result);

    return 0;
}


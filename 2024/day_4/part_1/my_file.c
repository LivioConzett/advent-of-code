
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_file.h"




/**
 * See header file
 */
int amount_of_lines(char* filename){
    
    // opent the file
    FILE* file_ptr;
    file_ptr = fopen(filename,"r");

    int line_counter = 0;

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
        line_counter++;
    }


    // close the file
    fclose(file_ptr);

    return line_counter;
}

/**
 * See header file
 */
int amount_of_columns(char* filename){

    // opent the file
    FILE* file_ptr;
    file_ptr = fopen(filename,"r");

    int max_column = 0;

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
        
        if(strlen(line) > max_column) max_column = strlen(line);

    }


    // close the file
    fclose(file_ptr);

    return max_column;

}

/**
 * \brief turn the string into an array
 * \param line string to put into the array
 * \param array array to place the string into
 * \param length length of the array
 * \param border border around the array
 */
static void line_to_array(char* line, int array[], int length, int border){

    int string_length = strlen(line);

    for(int i = border; i < string_length; i++){

        // make sure we don't write outside of the array
        if(i > length - border) break;

        array[i] = line[i-border];

    }

}


/**
 * See header file
 */
void read_file_to_array(int* array, int width, int height, int border, char* filename){
    
    // opent the file
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

    int array_counter = border;

    while(read != -1){
        read = getline(&line, &len, file_ptr);
        if(read == -1) break;
        
        line_to_array(line, &array[array_counter], width, border);
        array_counter++;
    }   


    // close the file
    fclose(file_ptr);
}


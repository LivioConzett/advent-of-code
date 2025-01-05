
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_file.h"
#include "linked.h"
#include "topo.h"




/**
 * See header
 */
int f_find_length_of_csl(char* line){
    int length = strlen(line);
    int counter = 0;

    for(int i = 0; i < length; i++){
        if(line[i] == ',') counter ++;
    }

    // + 1 because of the ladder problem
    return counter + 1;
}

/**
 * See header
 */
void f_fill_line_array(char* line, int* array, int length){

    char number[100];
    int number_index = 0;
    int array_index = 0;

    for(int i = 0; i < strlen(line); i++){

        if(array_index > length) return;
        if(number_index > 100) return;

        if(line[i] == ',' || line[i] == '\n'){
            array[array_index] = atoi(number);
            number[0] = 0;
            number_index = 0;
            array_index++;
            continue;
        }

        number[number_index] = line[i];
        number_index++;
    }
}


/**
 * See header
 */
int f_length_of_sort(char* filename){

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
        // only read up to the empty line
        if(strlen(line) <= 1) break;

        counter++;

    }

    return counter;
}


/**
 * See header file
 */
void f_fill_sort_arrays(char* filename, int* first_numbers, int* second_numbers, int length){

    // opent the file
    FILE* file_ptr;
    file_ptr = fopen(filename,"r");

    // make sure the file could be opend
    if (file_ptr == NULL){
        printf("Cannot open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    // create the list
    lnk_node_t* list = lnk_create_list();

    size_t read = 0;
    char* line = NULL;
    size_t len = 0;

    int index_counter = 0;

    while(read != -1 && index_counter < length){

        read = getline(&line, &len, file_ptr);
        if(read == -1) break;
        // only read up to the empty line
        if(strlen(line) <= 1) break;

        char first_num[100];
        char second_num[100];
        int delimiter_found = 0;
        int counter = 0;

        // parse the line
        for(int i = 0; i < strlen(line);i++){
            
            // handel the delimiter
            if(line[i] == '|'){
                // close the string
                first_num[counter] = 0;
                delimiter_found = 1;
                counter = 0;
                continue;
            }

            // handel the newline
            if(line[i] == '\n'){
                // close the string
                second_num[counter] = 0;
                break;
            }

            if(!delimiter_found){
                first_num[counter] = line[i];
            }
            else{
                second_num[counter] = line[i];
            }

            counter++;
        }

        first_numbers[index_counter] = atoi(first_num);
        second_numbers[index_counter] = atoi(second_num);

        index_counter++;

    }
}





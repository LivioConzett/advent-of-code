
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_file.h"


static char delimiter = ' ';

enum Line_read_state{
    NO_READ,
    DELIMITER,
    READ
};


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
int get_number_from_line(char* line, int column){

    int line_length = strlen(line);
    int column_count = 0;
    char num[line_length];
    int num_counter = 0;
    
    enum Line_read_state state = NO_READ;

    // if we want the first column, we need to start reading 
    // from the start
    if(column_count == column) state = READ;

    // go through the line char by char
    for(int i = 0; i < line_length; i++){

        char character = line[i];

        switch (state){
            case NO_READ:

                if(character == delimiter){
                    state = DELIMITER;
                }

                break;
            case DELIMITER:
                
                if(character != delimiter) column_count++;

                if(column_count > column) break;


                if(column_count == column){
                    state = READ;
                    num[num_counter] = character;
                    num_counter++;

                } else{
                    state = NO_READ;
                }

                break;
            case READ:

                if(character == delimiter){
                    state = DELIMITER;
                    break;
                }

                if(character == '\n') break;

                num[num_counter] = character;
                num_counter++;

                break;
            default:
                break;
        }

    }

    // add this to terminate the string
    num[num_counter] = 0;

    return atoi(num);
}



/**
 * See header file
 */
void read_file_to_array(int array[], int length, int column, char* filename){
    
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
    int line_counter = 0;

    while(read != -1){
        read = getline(&line, &len, file_ptr);
        if(read == -1) break;
        array[line_counter] = get_number_from_line(line, column);
        line_counter++;
    }
}

/**
 * See header file
 */
int get_length_of_array(char* line){

    // one element is always there
    int counter = 1;

    for(int i = 0; i < strlen(line); i++){

        if(line[i] == delimiter) counter ++;
    }

    return counter;
}

/**
 * See header file
 */
void create_array(int array[], char* line){

    int max_length = strlen(line);

    int counter = 0;

    char num[max_length];
    int num_counter = 0;

    for(int i = 0; i < max_length; i++){


        if((line[i] != delimiter) && (line[i] != '\n')){
            num[num_counter] = line[i];
            num_counter++;
        }
        else{
            // end the string
            num[num_counter] = 0;
            // reset the string
            num_counter = 0;

            // add the number to the array
            array[counter] = atoi(num);
            counter++;
        }

    }
    

}


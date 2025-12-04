/**
 * gcc -std=c99 -Wall -Werror
 */

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>


// define a vector for the size of the array
typedef struct{
    int columns;
    int rows;
} array_size_t;




/**
 * \brief get the size of the array from the file data
 */
array_size_t get_array_size(char* filename){


    FILE* file_ptr;
    file_ptr = fopen(filename, "r");

    // make sure file exists
    if(file_ptr == NULL){
        printf("Error: File %s does not exist!\n", filename);
        exit(EXIT_FAILURE);
    }

    size_t read = 0;
    char* line = NULL;
    size_t len = 0;
    int line_counter = 0;
    int column_counter = 0;

    while(read != -1){
        read = getline(&line, &len, file_ptr);
        if(read == -1) break;

        line_counter++;

        char character = ' ';
        uint8_t char_counter = 0;

        while(character != '\n'){
            char_counter++;
            character = line[char_counter];
        }

        if(char_counter > column_counter) column_counter = char_counter;

    }

    // free the memory space allocated by getline.
    free(line);

    return (array_size_t){column_counter, line_counter};
}


/**
 * \brief fill the array from the file
 * \param array array to fill
 * \param size size of the array
 * \param filename name of the file to fill from
 */
void fill_array(char* array, array_size_t size, char* filename){

    FILE* file_ptr;
    file_ptr = fopen(filename,"r");

    if(file_ptr == NULL){
        printf("Error: File %s does not exist!\n", filename);
        exit(EXIT_FAILURE);
    }


    size_t read = 0;
    char* line = NULL;
    size_t len = 0;

    char character[2];


    for(int i = 0; i < size.rows; i++){
        read = getline(&line, &len, file_ptr);
        if(read == -1) break;

        character[0] = 0;
        character[1] = 0;

        for(int ii = 0; ii < size.columns; ii++){

            character[0] = line[ii];

            array[(i * size.columns) + ii] = atoi(character);

        }
    }
    free(line);
}


/**
 * \brief main entry point
 */
int main(int argc, char* argv[]){

    // make sure a file name is given
    if(argc < 2){
        printf("Error: no file name given!\n");
        exit(EXIT_FAILURE);
    }

    // get the filename
    char* filename = argv[1];

    // get the size the array needs to be.
    array_size_t array_size = get_array_size(filename);

    char array[array_size.rows * array_size.columns];

    fill_array(array, array_size, filename);

    uint8_t digits[12];
    uint8_t digit_indexes[12];
    // uint8_t current_digit = 12;

    uint64_t total = 0;

    // go through the ranges
    for(int range = 0; range < array_size.rows; range++){

        // empty out the arrays
        for(int i = 0; i < 12; i++){
            digits[i] = 0;
            digit_indexes[i] = 0;
        }
        
        // get the 12 digits
        for(int digit = 0; digit < 12; digit++){
            
            uint8_t last_index = 0;

            if(digit > 0){
                last_index = digit_indexes[digit-1] + 1;
            }
        
            // start from the last index saved. Go until only enough digits are left
            // to create a 12 digit number
            for(int i = last_index; i < array_size.columns - (12 - (digit+1)); i++){
                
                // printf("%d",array[(range * array_size.columns) + i]);

                if(array[(range * array_size.columns) + i] > digits[digit]){
                    digits[digit] = array[(range * array_size.columns) + i];
                    digit_indexes[digit] = i;
                }

            }

            // printf("\n");

        }

        for(int iii = 0; iii < 12; iii++){
            total += digits[iii] * powl(10, 11-iii);
        }
    }

    printf("%ld\n", total);

    return 0;
}
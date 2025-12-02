/**
 * gcc -std=c99 -Wall -Werror
 */

#define _GNU_SOURCE

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>


#define LENGTH_OF_NUMBER 6


/**
 * \brief Get the amount of lines in a file. Needed to create the array to hold the values in.
 * \param filename name of the file to open
 * \return the number of lines in the file
 */
uint16_t get_amount_of_lines(char* filename){
    
    // opent the file
    FILE* file_ptr;
    file_ptr = fopen(filename,"r");

    uint16_t line_counter = 0;

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
 * \brief Read the file into the array.
 * \param array array to read into
 * \param length length of the array
 * \param filename name of the file to read
 */
void read_file_to_array(char array[][LENGTH_OF_NUMBER], int length, char* filename){
    
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
        
        char character = line[0];
        uint8_t char_counter = 0;

        while(character != 0 && character != '\n'){
            array[line_counter][char_counter] = character;
            char_counter ++;
            character = line[char_counter];
        }

        line_counter ++;
    }
}

/**
 * \brief add to the dial
 * \param dial the number the dial is currently on
 * \param amount the amount to add
 * \return the amount of times 0 is crossed
 */
int add_to_dial(int* dial, int amount){

    int number = *dial;
    int amount_zero_cross = 0;

    for(int i = 0; i < amount; i++){

        number++;

        if(number > 99) number = 0;

        if(number == 0) amount_zero_cross ++;
    }

    *dial = number;

    return amount_zero_cross;
}


/**
 * \brief remove from the dial
 * \param dial the number the dial is currently on
 * \param amount the amount to remove
 * \return the amount of times 0 is crossed
 */
int remove_from_dial(int* dial, int amount){
    
    int number = *dial;
    int amount_zero_cross = 0;

    for(int i = 0; i < amount; i++){

        number--;

        if(number == 0) amount_zero_cross++;

        if(number < 0) number = 99;

    }

    *dial = number;

    return amount_zero_cross;
}


/**
 * Main entry point of r the program
 */
int main(int argc, char* argv[]){


    // the number the dial is pointing to
    int dial = 50;
    // the amount of 0s found
    uint16_t amount_of_zeros = 0;


    // make sure a file name is given
    if(argc < 2){
        printf("ERROR: No file given\n");
        exit(EXIT_FAILURE);
    }

    // get the filename from the comand line
    char* filename = argv[1];

    // get the amount of lines in the file
    uint16_t line_amount = get_amount_of_lines(filename);

    // create the array
    char array[line_amount][LENGTH_OF_NUMBER];

    // empty the array
    for(int i = 0; i < line_amount; i++){
        for(int ii = 0; ii < LENGTH_OF_NUMBER; ii++){
            array[i][ii] = 0;
        }
    }

    // read the contents of the file into the array
    read_file_to_array(array, line_amount, filename);


    // go through the array and 
    for(int i = 0; i < line_amount; i++){
        
        char direction = array[i][0];
        int amount = atoi(&array[i][1]);

        printf("%d %s = ", dial, array[i]);

        // handle the L case
        if(direction == 'L'){
            amount_of_zeros += remove_from_dial(&dial, amount);
        }
        else if(direction == 'R'){
            amount_of_zeros += add_to_dial(&dial, amount);
        }

        printf("%d\n", dial);
    }


    printf("%d\n", amount_of_zeros);

    return 0;
}

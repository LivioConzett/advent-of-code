/**
 * gcc -std=c99 -Wall -Werror
 */

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define LENGTH_OF_RANGES 40

/**
 * \brief Get the amount of ranges in a file. Needed to create the array to hold the values in.
 * \param filename name of the file to open
 * \return the number of lines in the file
 */
uint16_t get_amount_of_ranges(char* filename){
    
    // opent the file
    FILE* file_ptr;
    file_ptr = fopen(filename,"r");

    uint16_t range_counter = 0;

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
        
        for(int i = 0; i < len; i++){
            if(line[i] == ',') range_counter++;
        }
    }


    // close the file
    fclose(file_ptr);

    // plus one because of the "ladder rung" problem
    return range_counter + 1;
}


/**
 * \brief fill the array with the ranges from the file
 * \param array array to fill
 * \param filename name of file to use
 */
void fill_array_from_file(char array[][LENGTH_OF_RANGES], char* filename){
    
    // opent the file
    FILE* file_ptr;
    file_ptr = fopen(filename,"r");

    uint16_t range_counter = 0;

    // make sure the file could be opend
    if (file_ptr == NULL){
        printf("Cannot open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    size_t read = 0;
    char* line = NULL;
    size_t len = 0;

    int char_counter = 0;

    while(read != -1){
        read = getline(&line, &len, file_ptr);
        if(read == -1) break;
        
        int i = 0;

        while(line[i] != 0 && line[i] != '\n'){

            if(line[i] == ','){
                // add a null terminator to the end of the string
                array[range_counter][char_counter] = 0;
                range_counter++;
                char_counter = 0;
                i++;
            }

            array[range_counter][char_counter] = line[i];
            char_counter++;
            i++;
        }

        array[range_counter][char_counter] = 0;

    }


    // close the file
    fclose(file_ptr);

    return;
}

/**
 * \brief get the length of a string
 * \param string string to get length of
 * \return length of string
 */
int get_length_of_string(char* string){

    int i = 0;
    while(string[i] != 0) i++;
    return i;
}


/**
 * \brief find out if a number has repeating digits in it
 * \param number number to check
 * \return 1 if number is repeating, 0 is not
 */
int is_number_repeating(uint64_t number){

    char string[LENGTH_OF_RANGES];

    sprintf(string, "%ld", number);

    int string_length = get_length_of_string(string); 

    // if the length is uneven it can't be made up of two
    // repeating numbers
    if(string_length %2 != 0) return 0;

    int string_length_half = string_length / 2;

    // check if the string is made up of two repeating numbers
    for(int i = 0; i < string_length_half; i++){
        if(string[i] != string[i+string_length_half]){
            return 0;
        }
    }

    return 1;
}


/**
 * \brief main entry point
 */
int main(int argc, char* argv[]){

    if(argc < 2){
        printf("Error: No file given!\n");
        exit(EXIT_FAILURE);
    }

    char* filename = argv[1];

    uint16_t amount_of_ranges = get_amount_of_ranges(filename);

    // create the array for the ranges
    char array[amount_of_ranges][LENGTH_OF_RANGES];

    fill_array_from_file(array, filename);

    uint64_t total = 0;

    // go through the array
    for(int range = 0; range < amount_of_ranges; range++){
        
        char first_number[LENGTH_OF_RANGES];
        char second_number[LENGTH_OF_RANGES];
        int i = 0;
        int second = 0;
        int char_counter = 0;

        while(array[range][i] != 0){

            if(array[range][i] == '-'){
                second = 1;
                // cap off the string
                first_number[char_counter] = 0;
                char_counter = 0;
                // skip the '-'
                i++;
            }

            if(second){
                second_number[char_counter] = array[range][i];
            }
            else{
                first_number[char_counter] = array[range][i];
            }

            i++;
            char_counter++;
        }
        
        // cap off the string
        second_number[char_counter] = 0;

        // printf("\n%s : %s\n", first_number, second_number);

       

        // go through the range
        for(uint64_t ii = atoll(first_number); ii <= atoll(second_number); ii++){

            // printf("%ld", ii);

            if(is_number_repeating(ii)){
                total += ii;
                // printf(" - yes\n");
            } 
            // else {
            //     printf("\n");
            // }
        
        }
    }

    printf("%ld\n", total);

    return 0;
}
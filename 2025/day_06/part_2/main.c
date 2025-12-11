/**
 * gcc -std=c99 -Wall -Werror main.c -lm
 */

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

typedef struct {
    uint16_t x;
    uint16_t y;
} vector_t;


/**
 * \brief get the size of the array that needs to be allocated
 * \param filename nae of the file
 * \return a vector with the width and hight
 */
vector_t get_array_size_spaces(const char* filename){

    FILE* file_ptr;
    file_ptr = fopen(filename, "r");

    if(file_ptr == NULL){
        printf("Error: File %s does not exist\n", filename);
        exit(EXIT_FAILURE);
    }


    size_t read = 0;
    char* line = NULL;
    size_t len = 0;

    int line_number = 0;
    int columns = 0;

    uint8_t space_mode = 0;

    while(read != -1){
        read = getline(&line, &len, file_ptr);
        if(read == -1) break;

        int char_index = 0;
        columns = 0;
        space_mode = 0;

        while(line[char_index] != '\n'){
            
            if(space_mode){
                if(line[char_index] != ' '){
                    space_mode = 0;
                }
            }

            if(!space_mode){
                if(line[char_index] == ' '){
                    columns++;
                    space_mode = 1;
                }
            }


            char_index++;
        }

        line_number++;
    }

    free(line);

    return (vector_t){line_number, columns};
}


/**
 * \brief get the size of the array that needs to be allocated
 * \param filename nae of the file
 * \return a vector with the width and hight
 */
vector_t get_array_size_characters(const char* filename){

    FILE* file_ptr;
    file_ptr = fopen(filename, "r");

    if(file_ptr == NULL){
        printf("Error: File %s does not exist\n", filename);
        exit(EXIT_FAILURE);
    }


    size_t read = 0;
    char* line = NULL;
    size_t len = 0;

    int line_number = 0;
    int columns = 0;

    while(read != -1){
        read = getline(&line, &len, file_ptr);
        if(read == -1) break;

        columns = 0;

        while(line[columns] != '\n'){

            columns++;
        }

        line_number++;
    }

    free(line);

    return (vector_t){line_number, columns};
}


/**
 * \brief fill the numbers array with the numbers
 * \param numbers array to put numbers into
 * \param size size of the array
 * \param filename name of the file
 */
void fill_number_array(uint16_t numbers[], vector_t size, char* filename){


    FILE* file_ptr;
    file_ptr = fopen(filename, "r");

    if(file_ptr == NULL){
        printf("Error: File %s does not exist\n", filename);
        exit(EXIT_FAILURE);
    }


    size_t read = 0;
    char* line = NULL;
    size_t len = 0;

    int char_index = 0;

    for(int i = 0; i < size.x; i++){
        read = getline(&line, &len, file_ptr);
        if(read == -1) break;

        char_index = 0;

        while(line[char_index] != '\n'){
            
            numbers[(i * size.y) + char_index] = line[char_index];

            char_index++;
        }
    }

    free(line);
}


/**
 * \brief fill the operators array
 * \param operators array for the operators
 * \param size size of the array
 * \param filename name of files
 */
void fill_operators(char operators[], vector_t size, const char* filename){

    FILE* file_ptr;
    file_ptr = fopen(filename, "r");

    if(file_ptr == NULL){
        printf("Error: File %s does not exist\n", filename);
        exit(EXIT_FAILURE);
    }


    size_t read = 0;
    char* line = NULL;
    size_t len = 0;

    int line_counter = 0;
    int char_index = 0;
    uint8_t space_mode = 0;
    int column = 0;


    while(read != -1){
        read = getline(&line, &len, file_ptr);
        if(read == -1) break;

        // get to the last line
        if(line_counter < size.x-1){
            line_counter++;
            continue;
        }

        while(line[char_index] != '\n'){

            if(space_mode){
                if(line[char_index] != ' '){
                    space_mode = 0;
                }
            }

            if(!space_mode){
                if(line[char_index] == ' '){
                    space_mode = 1;
                }
                else{
                    operators[column] = line[char_index];
                    column++;
                }
            }
            
            char_index++;
        }
    }

    free(line);
}


/**
 * \brief get the number of digits in the number
 * \param number number to get digits from
 * \return number of digits in number
 */
uint8_t get_number_of_digits(int number){

    char string[10];

    snprintf(string, 10, "%d",number);



    for(int i = 0; i < 10; i++){
        if(string[i] == 0) return i;
    }

    return 0;
}


/**
 * \brief check if the string only consists of spaces
 * \param string string to check
 * \return 1 if only spaces
 */
uint8_t check_if_string_is_only_spaces(char string[100]){

    uint8_t return_value = 1;

    for(int i = 0; i < 100; i++){

        if(string[i] == 0) break;

        if(string[i] != ' ') return_value = 0;
    }

    return return_value;
}

/**
 * \brief main entry point
 */
int main(int argc, char* argv[]){

    // make sure there are enough parameters
    if(argc < 2){
        printf("Error: No file given!\n");
        exit(EXIT_FAILURE);
    }

    char* filename = argv[1];

    vector_t array_size_spaces = get_array_size_spaces(filename);
    vector_t array_size_full = get_array_size_characters(filename);

    // get rid of the last line
    array_size_full.x--;

    // create the array for the numbers
    // one row less, since the last row is the operators
    uint16_t characters[(array_size_full.x) * array_size_full.y];

    // create the array for the operators
    char operators[array_size_spaces.y];

    fill_number_array(characters, array_size_full, filename);
    fill_operators(operators, array_size_spaces, filename);


    uint64_t total = 0;

    char string[100];
    int string_index = 0;

    uint64_t zwischen_total = 0;
    uint16_t operator_index = 0;

    switch(operators[operator_index]){
        case '*':
            zwischen_total = 1;
            break;
        case '+':
            zwischen_total = 0;
            break;
        
    }


    for(int col = 0; col < array_size_full.y; col++){
        string_index = 0;
        for(int row = 0; row < array_size_full.x; row++){
            string[string_index] = characters[(row * array_size_full.y) + col];
            string_index++;
        }

        // cap the string
        string[string_index] = 0;
        
        uint64_t number = atoll(string);

        if(check_if_string_is_only_spaces(string)){
            // printf("%c %ld\n\n", operators[operator_index], zwischen_total);
            // printf("%c\n", operators[operator_index]);

            operator_index++;
            total += zwischen_total;


            switch(operators[operator_index]){
                case '*':
                    zwischen_total = 1;
                    break;
                case '+':
                    zwischen_total = 0;
                    break;
                
            }
        }
        else{
            switch(operators[operator_index]){

                case '*':
                    zwischen_total *= number;
                    break;
                case '+':
                    zwischen_total += number;
                    break;

            }
            // printf("%ld\n", number);
        }


    }

    // printf("%c %ld\n\n", operators[operator_index], zwischen_total);
    // printf("%c\n", operators[operator_index]);
    

    total += zwischen_total;


    printf("%ld\n", total);


    // for(int i = 0; i < array_size_spaces.y; i++){
    //     printf("%c\n", operators[i]);
    // }

    return 0;
}



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
vector_t get_array_size(const char* filename){

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
    int column = 0;
    uint8_t space_mode = 0;
    uint8_t first_char = 1;
    char number_string[10];
    uint8_t number_string_index = 0;

    for(int i = 0; i < size.x - 1; i++){
        read = getline(&line, &len, file_ptr);
        if(read == -1) break;

        char_index = 0;
        column = 0;
        space_mode = 0;
        first_char = 1;
        number_string_index = 0;

        while(line[char_index] != '\n'){
            
            if(first_char && line[char_index] == ' '){
                    char_index++;
                    continue;
            }
            else{
                first_char = 0;
            }


            if(space_mode){
                if(line[char_index] != ' '){
                    space_mode = 0;
                }
            }

            if(!space_mode){

                if(line[char_index] == ' '){
                    space_mode = 1;

                    // cap off the string
                    number_string[number_string_index] = 0;

                    numbers[(i * size.y) + column] = atoi(number_string);

                    number_string_index = 0;
                    column++;
                    
                }
                else{
                    number_string[number_string_index] = line[char_index];
                    number_string_index++;
                }

            }


            char_index++;
        }

         // cap off the string
        number_string[number_string_index] = 0;

        numbers[(i * size.y) + column] = atoi(number_string);
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
 * \brief main entry point
 */
int main(int argc, char* argv[]){

    // make sure there are enough parameters
    if(argc < 2){
        printf("Error: No file given!\n");
        exit(EXIT_FAILURE);
    }

    char* filename = argv[1];

    vector_t array_size = get_array_size(filename);

    // create the array for the numbers
    // one row less, since the last row is the operators
    uint16_t numbers[(array_size.x - 1) * array_size.y];

    // create the array for the operators
    char operators[array_size.y];

    fill_number_array(numbers, array_size, filename);

    fill_operators(operators, array_size, filename);

    // for(int i = 0; i < array_size.x -1; i++){

    //     for(int ii = 0; ii < array_size.y; ii++){
    //         printf("%d ", numbers[(i * array_size.y) + ii]);
    //     }
    //     printf("\n");
    // }

    // for(int i = 0; i < array_size.y; i++){
    //     printf("%c ", operators[i]);
    // }
    // printf("\n");

    uint64_t total = 0;
    // uint64_t result = 0;

    // go through the arrays and calculate it all
    // for(int column = 0; column < array_size.y; column++){

    //     if(operators[column] == '+') result = 0; 
    //     if(operators[column] == '*') result = 1; 

    //     for(int row = 0; row < array_size.x-1; row++){

    //         switch(operators[column]){

    //             case '*':
    //                 result *= numbers[(row * array_size.y) + column];
    //                 break;
    //             case '+':
    //                 result += numbers[(row * array_size.y) + column];
    //                 break;
    //         }
    //     }

    //     total += result;
    // }



    // 1) find the largest number in the column
    // 2) see how many digits it has
    // 3) create a new array with as many elements as the original has rows
    // 4) fill each position in the array with the numbers divided by ten * column pos
    // 5) calculate normal
    // 6) ??
    // 7) profit

    for(int main_column = 0; main_column < 1; main_column++){

        int largest_number = 0;

        // find the largest number in the column
        for(int row = 0; row < array_size.x - 1; row++){
            if(numbers[(row * array_size.y) + main_column] > largest_number){
                largest_number = numbers[(row * array_size.y) + main_column];
            }
        }
        int number_of_digits = get_number_of_digits(largest_number);
        printf("%d %d\n", largest_number, number_of_digits);

        // create an array for the numbers
        int array[number_of_digits];

        for(int i = number_of_digits - 1; i >= 0; i--){

            for(int row = 0; row < array_size.x - 1; row++){

                int digit = numbers[(row * array_size.y) + main_column] / pow(10, i);
                // int num = digit * pow(10,i);

                array[i] += digit * pow(10, (array_size.x -1)-row);

            }



        }


        for(int i = 0; i < number_of_digits; i++){
            printf("%d ",array[i]);
        }

        printf("\n");

        
    }


    printf("%ld\n", total);

    return 0;
}


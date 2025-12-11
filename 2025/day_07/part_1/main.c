/**
 * gcc -std=c99 -Wall -Werror main.c -lm
 */

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef struct {
    int16_t x;
    int16_t y;
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
 * \param array array to put numbers into
 * \param size size of the array
 * \param filename name of the file
 */
void fill_array(char array[], vector_t size, char* filename){


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
            
            array[(i * size.y) + char_index] = line[char_index];

            char_index++;
        }
    }

    free(line);
}


/**
 * \brief prints ou the array
 * \param array array to print
 * \param size size of the array
 */
void print_array(char array[], vector_t size){

    for(int row = 0; row < size.x; row++){
        for(int col = 0; col < size.y; col++){
            printf("%c", array[(row * size.y) + col]);
        }
        printf("\n");
    }
}


/**
 * \brief go through the array recursive
 * \param array the array
 * \param size the size of the array
 * \param start starting position 
 */
void go_through_array_recursive(char array[], vector_t size, vector_t start){

    // go to next row
    start.x++;


    while(start.x < size.x){

        char* character = &array[(start.x * size.y) + start.y];

        if(*character != '^'){
            *character = '|';
        }
        else {
            
            if(start.y - 1 > 0) go_through_array_recursive(array, size, (vector_t){start.x, start.y-1});
            if(start.y + 1 < size.y) go_through_array_recursive(array, size, (vector_t){start.x, start.y+1});
            return;
        }

        start.x++;
    }

}


/**
 * \brief go through a row in the array
 * \param array array of the characters
 * \param size size of the array
 * \param row we are on
 * \return the number of '^' with a '|' above them in that row
 */
uint16_t go_through_row(char array[], vector_t size, uint16_t row){

    uint16_t count = 0;

    if(row == 0) return 0;

    for(int i = 0; i < size.y; i++){
        // if the character 1 row above is a '|'
        if(array[((row - 1) * size.y) + i] == '|'){

            // if the current character is a '^'
            if(array[(row * size.y) + i] == '^'){
                count++;

                if(i > 0) array[(row * size.y) + i - 1] = '|';
                if(i < size.y - 1) array[(row * size.y) + i + 1] = '|';
            }
            else{
                array[(row * size.y) + i] = '|';
            }
        }
    }

    return count;
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
    
    // array for the characters
    char array[array_size.x * array_size.y];

    fill_array(array, array_size, filename);

    // print_array(array, array_size);

    // find the S in the first line
    for(int i = 0; i < array_size.y; i++){
        if(array[i] == 'S'){
            array[i] = '|';
            break;
        }
    }


    uint32_t total = 0;

    // go_through_array(array, array_size, starting_pos);

    for(int i = 0; i < array_size.x; i++){
        total += go_through_row(array, array_size, i);
    }

    print_array(array, array_size);

    printf("%d\n", total);

    return 0;
}

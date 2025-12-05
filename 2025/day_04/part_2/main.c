/**
 * gcc -std=c99 -Wall -Werror
 */

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>



typedef struct {
    int32_t rows;
    int32_t columns;
 } array_size_t;



// array with the positions to check
const array_size_t POSITIONS[] = {{-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1}};

/**
 * \brief add two vectors together
 * \param first first vector. The second vector will be added to this one
 * \param second the second vector will be added to added t the first
 * \return the vectors added 
 */
array_size_t add_vectors(const array_size_t* first, const array_size_t* second){

    return (array_size_t) {first->rows + second->rows, first->columns + second->columns};
}


/**
 * \brief get the size of the array needed for the file
 * \param filename name of the file
 * \return size of the array
 */
array_size_t get_array_size_from_file(char* filename){

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
 * \brief fills the array with the data from the file
 * \param array array to fill
 * \param size size of he array
 * \param filename name of the file
 */
void fill_array_from_file(char array[], array_size_t size, char* filename){

    FILE* file_ptr;
    file_ptr = fopen(filename,"r");

    if(file_ptr == NULL){
        printf("Error: File %s does not exist!\n", filename);
        exit(EXIT_FAILURE);
    }


    size_t read = 0;
    char* line = NULL;
    size_t len = 0;

    int line_number = 0;

    while(read != -1){
        read = getline(&line, &len, file_ptr);
        if(read == -1) break;

        int index = 0;

        while(line[index] != '\n'){

            // + 1 in order for the border around the array
            array[((line_number + 1) * size.columns) + index + 1] = line[index];

            index++;
        }

        line_number++;
    }
    free(line);
}

/**
 * \brief check the surrounding fields 
 * \param array array
 * \param size size of the array
 * \param row row position of the field to check
 * \param column column position of the field to check
 * \return 1 if there are fewer then 4 spaces around it with a '@'
 */
uint8_t check_surrounding_fields(const char array[], array_size_t size, int row, int column){

    uint8_t total = 0;

    array_size_t pos = {row, column};

    for(int i = 0; i < 8; i++){

        array_size_t new_pos = add_vectors(&pos,&POSITIONS[i]);

        if(array[(new_pos.rows * size.columns) + new_pos.columns] == '@') total++;
    }

    return total < 4;
}


/**
 * \brief main entry point
 */
int main(int argc, char* argv[]){

    // make sure enough params are given 
    if(argc < 2){
        printf("Error: No file given!\n");
        exit(EXIT_FAILURE);
    }

    // get the filename
    char* filename = argv[1];

    array_size_t array_size = get_array_size_from_file(filename);
    
    // +2 to create a border around the whole array 
    array_size.rows += 2;
    array_size.columns += 2;

    // create the array
    char array[array_size.rows * array_size.columns];

    // empty out the array
    for(int i = 0; i < array_size.rows; i++){
        for(int ii = 0; ii < array_size.columns; ii++){
            array[(i * array_size.columns) + ii] = '.';
        }
    }

    // fill the array
    fill_array_from_file(array, array_size, filename);

    uint32_t total = 0;
    uint8_t roll_removed = 1;

    // while a roll has always been removed
    while(roll_removed){

        roll_removed = 0;

        // go through the array and find places with less than 4 '@' around them
        // start at 1 and go to 1 less than the size in order to ignore the border
        for(int rows = 1; rows < array_size.rows-1; rows++){
            for(int columns = 1; columns < array_size.columns-1; columns++){

                // if the field is a '@' 
                if(array[(rows * array_size.columns) + columns] == '@'){

                    if(check_surrounding_fields(array, array_size, rows, columns)){
                        total++;
                        
                        // set the current field to be removed
                        array[(rows * array_size.columns) + columns] = 'x';

                        roll_removed = 1;
                    }
                }
            }
        }
    }


    //  for(int i = 0; i < array_size.rows; i++){
    //     for(int ii = 0; ii < array_size.columns; ii++){
    //         printf("%c",array[(i * array_size.columns) + ii]);
    //     }
    //     printf("\n");
    // }

    printf("%d\n", total);

    return 0;
}
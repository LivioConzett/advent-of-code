
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_file.h"


/**
 * \brief fill the 2d array with 0
 * \param array pointer to 2d array
 * \param height height of array
 * \param width width of array
 */
void clear_array(char* array, int height, int width){
    
    for(int i = 0; i < height; i++){
        for(int ii = 0; ii < width; ii++){
            array[(i * height) + ii] = 'a';
        }
    }
}

/**
 * \brief print the 2d array 
 * \param array pointer to 2d array
 * \param height height of array
 * \param width width of array
 */
void print_array(char* array, int height, int width){

    for(int i = 0; i < height; i++){
        for(int ii = 0; ii < width; ii++){
            printf("%c",array[(i * height) + ii]);
        }
        printf("\n");
    }
}

/**
 * \brief check around the fields if xmas is given
 * \param array array to use
 * \param width width of the array
 * \param height height of the array
 * \param x x pos of the field to start at
 * \param y y pos of the field to start at
 * \return 0 if no xmas was found, 1 if xmas was found
 */
int check_around_field(char* array, int width, int height, int x, int y){

    int found = 0;
    
    // check for out of bounds
    if(x - 1 < 0 || x + 1 >= width || y - 1 < 0 || y + 1 >= height) return 0;

    // NW - SE
    if(array[((y - 1) * width) + (x - 1)] == 'M' && array[((y + 1) * width) + (x + 1)] == 'S') found++;
    // SE - NW
    if(array[((y + 1) * width) + (x + 1)] == 'M' && array[((y - 1) * width) + (x - 1)] == 'S') found++;

    // NE - SW
    if(array[((y - 1) * width) + (x + 1)] == 'M' && array[((y + 1) * width) + (x - 1)] == 'S') found++;
    // SW - NE
    if(array[((y + 1) * width) + (x - 1)] == 'M' && array[((y - 1) * width) + (x + 1)] == 'S') found++;


    if(found >= 2) return 1;

    return 0;
}


/**
 * \brief Main entry point
 */
int main(int argc, char* argv[]){

    char* filename = argv[1];

    int xmas_counter = 0;

    int height = amount_of_lines(filename);
    int width = amount_of_columns(filename);
    
    printf("%d:%d\n", height, width);

    char main_array[height][width];

    clear_array(main_array, height, width);

    read_file_to_array(main_array, width, height, filename);

    print_array(main_array, height, width);

    for(int i = 0; i < height; i++){
        for(int ii = 0; ii < width; ii++){
            
            if(main_array[i][ii] == 'A'){
                xmas_counter += check_around_field(main_array, width, height, ii, i);
            }
        }
    }


    printf("amount: %d\n",xmas_counter);
    return 0;

}



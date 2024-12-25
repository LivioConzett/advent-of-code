
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

    int found_count = 0;
    int found = 1;
    char* find = "XMAS";
    int find_length = strlen(find);
                    // N  NE  E  SE S  SW  W   NW
    int x_offset[] = { 0,  1, 1, 1, 0, -1, -1, -1}; 
    int y_offset[] = {-1, -1, 0, 1, 1,  1,  0, -1}; 

    for(int pos = 0; pos < 8; pos++){
        for(int i = 0; i < find_length; i++){
            // don't go out of bound
            if((x + x_offset[pos]*i < 0) || (x + x_offset[pos]*i > width)){
                found = 0;
                break;
            }
            if((y + y_offset[pos]*i < 0) || (y + y_offset[pos]*i > height)){
                found = 0;
                break;
            }

            // check the field in the direction that the pos index gives
            if(array[ ((y + (y_offset[pos]*i)) * width) + (x + (x_offset[pos]*i)) ] != find[i]){
                found = 0;
                break;
            }
        }

        if(found) found_count++;
        found = 1;
    }

    return found_count;
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
            
            if(main_array[i][ii] == 'X'){
                xmas_counter += check_around_field(main_array, width, height, ii, i);
            }
        }
    }


    printf("amount: %d\n",xmas_counter);
    return 0;

}



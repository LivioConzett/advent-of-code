
#include <stdio.h>
#include <stdlib.h>

#include "my_file.h"


/**
 * \brief fill the 2d array with 0
 * \param array pointer to 2d array
 * \param height height of array
 * \param width width of array
 */
void clear_array(int* array, int height, int width){

    for(int i = 0; i < height; i++){
        for(int ii = 0; ii < width; ii++){
            array[(i * height) + ii] = ii;
        }
    }
}

/**
 * \brief print the 2d array 
 * \param array pointer to 2d array
 * \param height height of array
 * \param width width of array
 */
void print_array(int* array, int height, int width){

    for(int i = 0; i < height; i++){
        for(int ii = 0; ii < width; ii++){
            printf("%d ",array[(i * height) + ii]);
        }
        printf("\n");
    }
}



/**
 * \brief Main entry point
 */
int main(int argc, char* argv[]){

    char* filename = argv[1];

    int height = amount_of_lines(filename);
    int width = amount_of_columns(filename);
    
    printf("%d:%d\n", height, width);

    int main_array[height][width];

    clear_array(main_array, height, width);

    print_array(main_array, height, width);

    return 0;

}



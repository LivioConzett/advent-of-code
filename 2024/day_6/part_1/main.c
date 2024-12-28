
#include <stdio.h>
#include <stdlib.h>

#include "file.h"

/**
 * Main entry point
 */
int main(int argc, char* argv[]){

    char* filename = argv[1];

    int field_width = f_get_width_of_field(filename);
    int field_height = f_get_height_of_filed(filename);

    // create the 2d array for the field
    int field[field_width][field_height];

    
}
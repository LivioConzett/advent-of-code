
#include <stdio.h>

#include "file.h"



/**
 * \brief print the field
 * \param field field to print
 * \param size size of the field
 */
void print_field(char* field, vector_t size){

    for(int y = 0; y < size.y; y++){
        for(int x = 0; x < size.x; x++){
            printf("%c ",field[(y * size.x) + x]);
        }
        printf("\n");
    }
}


/**
 * Main entry point
 */
int main(int argc, char* argv[]){

    char* filename = argv[1];

    // get the size of the field
    vector_t field_size = f_get_field_size(filename);

    // create the two field arrays
    char field[field_size.y * field_size.x];
    char antinodes[field_size.y * field_size.x];

    f_fill_field(filename, field, field_size);
    f_empty_field(antinodes, field_size);

    

    return 0;
}
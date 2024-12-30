
#include <stdio.h>

#include "file.h"
#include "vector.h"


/**
 * \brief print the field
 * \param field field to print
 * \param size size of the field
 */
void print_field(char* field, vector_t size){

    for(int y = 0; y < size.y; y++){
        for(int x = 0; x < size.x; x++){
            printf("%c",field[(y * size.x) + x]);
        }
        printf("\n");
    }
}

/**
 * \brief check the direction
 */
void check_direction(char* field, char* antinodes, vector_t field_size, vector_t pos, vector_t direction, int radius, char c){

    vector_t check_direction = direction;
    v_multiply(&check_direction, radius);

    vector_t check_pos = pos;

    v_add(&check_pos, &check_direction);
    
    
    // if the check pos is still within the bounds
    if(v_in_bound(&check_pos, &field_size)){
        // check if the same char is at that pos
        if(c == field[(check_pos.y * field_size.x) + check_pos.x]){
            // flip the check direction
            v_flip(&check_direction);

            vector_t new_pos = pos;
            v_add(&new_pos, &check_direction);

            // make sure the new pos is also in bounds
            if(v_in_bound(&new_pos, &field_size)){
                antinodes[(new_pos.y * field_size.x) + new_pos.x] = NODE;
            }
        }
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

    // position of the current character
    vector_t pos = {0,0};

    // go through the field
    for(pos.y = 0; pos.y < field_size.y; pos.y++){
        for(pos.x = 0; pos.x < field_size.x; pos.x++){

            char c = field[(pos.y * field_size.x) + pos.x];

            // don0t do the empty fields
            if(c == EMPTY) continue;

            // get the higher of the two numbers
            int higher = v_get_higher(&field_size);

            // start looking around the field in ever
            // growing circles.
            // Start at 1 because we don't want to check the field
            // we are already on.
            for(int radius = 1; radius < higher; radius++){
                
                // north
                check_direction(field, antinodes, field_size, pos,  N_V, radius, c);

                // north east
                check_direction(field, antinodes, field_size, pos, NE_V, radius, c);

                // east
                check_direction(field, antinodes, field_size, pos,  E_V, radius, c);
                
                // south east
                check_direction(field, antinodes, field_size, pos, SE_V, radius, c);

                // south
                check_direction(field, antinodes, field_size, pos,  S_V, radius, c);

                // south west
                check_direction(field, antinodes, field_size, pos, SW_V, radius, c);

                // west
                check_direction(field, antinodes, field_size, pos,  W_V, radius, c);

                // north west
                check_direction(field, antinodes, field_size, pos, NW_V, radius, c);
                
            }
        }
    }

    print_field(field, field_size);
    printf("-------\n");
    print_field(antinodes, field_size);
            


    return 0;
}

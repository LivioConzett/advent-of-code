
#include <stdio.h>
#include <stdlib.h>

#include "guard.h"


/**
 * Main entry point
 */
int main(int argc, char* argv[]){

    char* filename = argv[1];

    // int field_width = f_get_width_of_field(filename);
    // int field_height = f_get_height_of_filed(filename);

    vector_t field_size = g_get_size_of_field(filename);

    // printf("%d : %d\n", size.x, size.y);

    // create the 2d array for the field
    char field[field_size.y * field_size.x];

    // fill the array
    g_fill_field(filename, field, field_size);

    // g_print_field(field, field_size);

    // get the position of the guard
    vector_t position = get_position_of_guard(field, field_size);
    
    // needed to reset the pos of the guard
    vector_t original_pos;
    original_pos.x = position.x;
    original_pos.y = position.y;

    char original_guard = field[(original_pos.y * field_size.x) + original_pos.x];


    int left_field = 0;

    while(!left_field){
        left_field = g_move(field, field_size, &position, 1);
    }

    // get the amount of touched fields
    int amount_of_touched = g_count_touched_fields(field, field_size);

    g_set_guard(field, field_size, original_pos, original_guard);

    g_print_field(field, field_size);

    for(int i = 0; i < 10; i++){
        g_set_obstacle(field, field_size);

        g_print_field(field, field_size);
    }

}
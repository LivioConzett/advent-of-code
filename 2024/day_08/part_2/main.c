
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
 * \brief count the number of nodes in a field
 * \param field field to count through
 * \param size size of the field
 * \return number of nodes in the field
 */
int count_nodes(char* field, vector_t size){
    
    int counter = 0;
    
    for(int y = 0; y < size.y; y++){
        for(int x = 0; x < size.x; x++){
            if(field[(y * size.x) + x] == NODE) counter ++;
        }
    }

    return counter;
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
    vector_t check_pos = {0,0};

    // the maximum radius for the for loop 
    // that draws the line.
    int max_radius = v_get_higher(&field_size);

    // go through the field
    for(pos.y = 0; pos.y < field_size.y; pos.y++){
        for(pos.x = 0; pos.x < field_size.x; pos.x++){

            char c = field[(pos.y * field_size.x) + pos.x];

            // don't do the empty fields
            if(c == EMPTY) continue;

            for(check_pos.y = 0; check_pos.y < field_size.y; check_pos.y++){
                for(check_pos.x = 0; check_pos.x < field_size.x; check_pos.x++){

                    char check_c = field[(check_pos.y * field_size.x) + check_pos.x];

                    // don't check the same place
                    if(v_equal(&check_pos, &pos)) continue;
                    // only do it if you find the same character
                    if(c != check_c) continue;
                    
                    // get the distance between the two
                    vector_t distance = pos;
                    v_subtract(&distance, &check_pos);

                    // get the direction of the distance
                    vector_t direction = v_get_direction(&distance);

                    for(int radius = 0; radius < max_radius; radius++){
                        
                        vector_t delta = distance;

                        v_multiply(&delta, radius);

                        vector_t new_pos = pos;
                        
                        v_add(&new_pos, &delta);
                        
                        if(v_in_bound(&new_pos, &field_size)){
                            antinodes[(new_pos.y * field_size.x) + new_pos.x] = NODE;
                        }

                        new_pos = pos;

                        v_subtract(&new_pos, &delta);

                        if(v_in_bound(&new_pos, &field_size)){
                            antinodes[(new_pos.y * field_size.x) + new_pos.x] = NODE;
                        }
                    }   
                }
            }
        }
    }

    print_field(field, field_size);
    printf("-------\n");
    print_field(antinodes, field_size);
    
    int nodes = count_nodes(antinodes, field_size);

    printf("nodes: %d\n", nodes);
    return 0;
}



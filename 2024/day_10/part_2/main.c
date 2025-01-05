
#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "vector.h"
#include "linked.h"


/**
 * \brief print the field
 * \param field field to print
 * \param size size of field
 */
void print_field(int field[], vector_t size){

    for(int y = 0; y < size.y; y++){
        for(int x = 0; x < size.x; x++){
            printf("%d",field[(y * size.x) + x]);
        }
        printf("\n");
    }
}

/**
 * \brief get the number at the pos in the field
 * \param field field to get num from
 * \param pos pos of the number to get
 * \return number at the pos in the field
 */
int get_num_at_pos(int field[], vector_t size, vector_t pos){
    return field[(pos.y * size.x) + pos.x];
}


int vector_equal(void* one, void* two){
    return v_equal((vector_t*)one,(vector_t*)two);
}

void print_vectors(void* data, void* ignore){
    v_print((vector_t*)data, 1);
}


/**
 * \brief search the trail while counting up the number of nines one can reach
 * \param field the field to search through
 * \param size size of the field
 * \param pos the position to search
 * \param current_trail the current trail we are on
 * \param nine_counter the counter for the nines
 */
void search_trail(int field[], vector_t size, vector_t pos, int current_trail, lnk_node_t* nine_counter[]){

    // if a nine was reached, increment the counter
    // and then return, since we can't go further anymore
    if(get_num_at_pos(field, size, pos) == 9){
        
        vector_t* data = (vector_t*) malloc(sizeof(vector_t));
        if(data == NULL){
            printf("couldn't malloc data!\n");
            exit(EXIT_FAILURE);
        }
        
        data->x = pos.x;
        data->y = pos.y;

        if(lnk_find_index_of_data(nine_counter[current_trail],vector_equal, data) < 0){
            lnk_append_data(nine_counter[current_trail], data);
            // printf("nine: %d: ",current_trail);
            // v_print(&pos, 1);
        }
        
        return;
    }

    // go through the array of the four Himmelsrichtungen
    for(int i = 0; i < 4; i++){

        vector_t direction = NESW[i];

        vector_t check = v_add_n(&pos, &direction);

        // check it is still within the bounds
        if(v_in_bound(&check, &size)){
            // if the field is one greater then the one we started from
            if(get_num_at_pos(field, size, check) == get_num_at_pos(field, size, pos) + 1){
                // go to the next place and try it again
                // v_print(&check,1);
                search_trail(field, size, check, current_trail, nine_counter);
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
    vector_t field_size = f_get_sie_of_field(filename);

    // create the field
    int field[field_size.x * field_size.y];

    // fill the field
    f_fill_field(filename, field, field_size);

    // get the amount of trail heads
    int trail_head_amount = f_count_numbers(field, field_size, 0);

    // create the array for the 9s a trail can reach
    lnk_node_t* nine_counter[trail_head_amount];
    // empty the array
    for(int i = 0; i < trail_head_amount; i++){
        nine_counter[i] = lnk_create_list();
    }


    int current_trail = 0;

    vector_t pos = {0,0};

    // go through the field and look for train heads
    for(pos.y = 0; pos.y < field_size.y; pos.y++){
        for(pos.x = 0; pos.x < field_size.x; pos.x++){

            if(get_num_at_pos(field, field_size, pos) == 0){
                
                // printf("%d new start: %d:%d\n", current_trail, pos.x, pos.y);

                search_trail(field, field_size, pos, current_trail, nine_counter);

                current_trail++;
            }
        }
    }

    int sum = 0;

    for(int i = 0; i < trail_head_amount; i++){

        // lnk_do_on_each_node(nine_counter[i], print_vectors, 0);

        // printf("%d\n", lnk_list_length(nine_counter[i]));
        sum += lnk_list_length(nine_counter[i]);
    }

    printf("sum: %d\n", sum);

    return 0;
}


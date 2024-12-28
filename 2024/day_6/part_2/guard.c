
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "guard.h"

// bad global variable.
// too lazy to fix for a simple Advent of Code.
static char previous_field = TOUCHED;

/**
 * See header
 */
void g_print_vector(vector_t vector){
    printf("%d : %d", vector.x, vector.y);
}


/**
 * See header
 */
vector_t g_get_size_of_field(char* filename){

    FILE* file_ptr;
    file_ptr = fopen(filename,"r");

    // make sure the file could be opend
    if (file_ptr == NULL){
        printf("Cannot open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    size_t read = 0;
    char* line = NULL;
    size_t len = 0;

    vector_t size;
    size.x = 0;
    size.y = 0;

    while(read != -1){
        
        read = getline(&line, &len, file_ptr);
        if(read == -1) break;

        size.y ++;
        
        if(strlen(line) - 1 > size.x) size.x = strlen(line) - 1;

    }

    return size;
}


/**
 * See header
 */
void g_fill_field(char* filename, char* field, vector_t size){

    FILE* file_ptr;
    file_ptr = fopen(filename,"r");

    // make sure the file could be opend
    if (file_ptr == NULL){
        printf("Cannot open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    size_t read = 0;
    char* line = NULL;
    size_t len = 0;

    int y = 0;

    while(read != -1){
        
        read = getline(&line, &len, file_ptr);

        if(read == -1) break;

        for(int x = 0; x < size.x; x++){
            field[(y * size.x) + x] = line[x];
        }

        y++;

        if(y > size.y) break;
    }
}


/**
 * See header
 */
void g_print_field(char* field, vector_t size){

    printf("\n");

    for(int y = 0; y < size.y; y++){
        for(int x = 0; x < size.x; x++){
            printf("%c",field[(y * size.x) + x]);
        }
        printf("\n");
    }
}


/**
 * See header
 */
vector_t get_position_of_guard(char* field, vector_t size){

    vector_t position = {-1,-1};

    for(int y = 0; y < size.y; y++){
        for(int x = 0; x < size.x; x++){
            char c = field[(y * size.x) + x];
            if(c == UP || c == DOWN || c == LEFT || c == RIGHT){
                position.x = x;
                position.y = y;
                break;
            }
        }
    }

    return position;
}

/**
 * \brief turn the guard by 90 deg CW
 * \param guard the guard
 * \return the guard turned by 90 deg CW
 */
static enum Characters g_turn_90_deg_cw(enum Characters guard){

    switch(guard){
        case UP:
            return RIGHT;
        case DOWN:
            return LEFT;
        case LEFT:
            return UP;
        case RIGHT:
            return DOWN;
        default:
    }

    return guard;
}



/**
 * See header
 */
int g_move(char* field, vector_t size, vector_t* position, int mark_touched){

    char guard = field[(position->y * size.x) + position->x];
    vector_t pos = *position;

    // check the position
    switch(guard){
        case UP:
            pos.y--;
            break;
        case DOWN:
            pos.y++;
            break;
        case LEFT:
            pos.x--;
            break;
        case RIGHT:
            pos.x++;
            break;
        default:
    }

    // if the next step would cause them to leave the field
    if(pos.y < 0 || pos.y >= size.y || pos.x < 0 || pos.x >= size.x) return 1;

    // turn the guard if the next field is not empty
    char next = field[(pos.y * size.x) + pos.x];
    previous_field = next;
    if(next == BLOCK){
        guard = g_turn_90_deg_cw(guard);
        // update the position of the guard in the field
        field[(position->y * size.x) + position->x] = guard;
        return 0;
    }

    // update the pos of the guard in the field.
    // clear the position of the guard
    if(mark_touched) field[(position->y * size.x) + position->x] = TOUCHED;
    else field[(position->y * size.x) + position->x] = previous_field;
    // place the guard in the new position
    field[(pos.y * size.x) + pos.x] = guard;

    // set the position of the guard to the new position
    position->x = pos.x;
    position->y = pos.y;

    return 0;
}


/**
 * See header
 */
int g_count_touched_fields(char* field, vector_t size){

    int counter = 0;

    for(int y = 0; y < size.y; y++){
        for(int x = 0; x < size.x; x++){
            char character = field[(y * size.x) + x];

            // count the guard and the touched fields
            if(character != EMPTY && character != BLOCK) counter ++;
        }
    }

    return counter;
}

/**
 * See header
 */
void g_set_guard(char* field, vector_t size, vector_t position, char guard){

    vector_t old_pos = get_position_of_guard(field, size);

    field[(old_pos.y * size.x) + old_pos.x] = TOUCHED;
    field[(position.y * size.x) + position.x] = guard;

}

/**
 * See header
 */
int g_set_obstacle(char* field, vector_t size){

    //go through the field
    for(int y = 0; y < size.y; y++){
        for(int x = 0; x < size.x; x++){
            char character = field[(y * size.x) + x];
            if(character == OBSTACLE){
                field[(y * size.x) + x] = TRIED;
            }
            
            if(character == TOUCHED){
                field[(y * size.x) + x] = OBSTACLE;
                return 1;
            }
        }
    }
    return 0;
}


/**
 * gcc -std=c99 -Wall -Werror
 */

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef struct {
    uint16_t x;
    uint16_t y;
} vector_t;


/**
 * \brief get the array lengths for the ranges and the ids
 * \param filename name of the file
 * \return length the array needs to be
 */
vector_t get_array_lengths(const char* filename){

    FILE* file_ptr;
    file_ptr = fopen(filename, "r");

    if(file_ptr == NULL){
        printf("Error: File %s does not exist\n", filename);
        exit(EXIT_FAILURE);
    }


    size_t read = 0;
    char* line = NULL;
    size_t len = 0;

    vector_t lengths;

    int line_number = 0;

    while(read != -1){
        read = getline(&line, &len, file_ptr);
        if(read == -1) break;

        if(line[0] == '\n'){

            lengths.x = line_number;
            line_number = 0;
            continue;

        }

        line_number++;
    }

    lengths.y = line_number;

    free(line);

    return lengths;
}

/**
 * \brief fill the arrays with the data
 * \param ranges array for the ranges
 * \param ids array for the ids
 * \param filename name of the file
 */
void fill_arrays(uint64_t ranges[][2], uint64_t ids[], const char* filename){

    FILE* file_ptr;
    file_ptr = fopen(filename, "r");

    if(file_ptr == NULL){
        printf("Error: File %s does not exist\n", filename);
        exit(EXIT_FAILURE);
    }


    size_t read = 0;
    char* line = NULL;
    size_t len = 0;

    int line_number = 0;

    // modes 0 for ranges 1 for ids
    uint8_t mode = 0;

    while(read != -1){
        read = getline(&line, &len, file_ptr);
        if(read == -1) break;

        if(line[0] == '\n'){

            line_number = 0;
            mode = 1;
            continue;

        }

        // ids
        if(mode){

            ids[line_number] = atoll(line);

        }
        // ranges
        else{

            char number[200];
            uint8_t number_index = 0;
            char character = ' ';
            int index = 0;

            while(character != '\n'){
                character = line[index];
                
                // printf("%c", character);

                if(character == '\n') break;

                if(character == '-'){
                    // cap off the string
                    number[number_index] = 0;
                    
                    // printf("\n%s - ", number);

                    ranges[line_number][0] = atoll(number);
                    number_index = 0;
                    // skip the '-'
                    index++;
                }

                number[number_index] = line[index];

                number_index++;
                index++;
            }
            // cap off the string
            number[number_index + 1] = 0;

            // printf("\n%s\n", number);

            ranges[line_number][1] = atoll(number);

        }

        line_number++;
    }


    free(line);
}


/**
 * \brief main entry point
 */
int main(int argc, char* argv[]){

    // check the amount of parameters
    if(argc < 2){
        printf("Error: No file given!\n");
        exit(EXIT_FAILURE);
    }

    char* filename = argv[1];

    vector_t array_lengths = get_array_lengths(filename);

    uint64_t ranges[array_lengths.x][2];
    uint64_t ids[array_lengths.y];

    fill_arrays(ranges, ids, filename);

    uint16_t total = 0;

    // go through the id's and check if they are in any range
    for(int id = 0; id < array_lengths.y; id++){
        
        for(int range = 0; range < array_lengths.x; range++){

            if(ids[id] >= ranges[range][0] && ids[id] <= ranges[range][1]){

                total++;
                // printf("%ld . %ld - %ld\n", ids[id], ranges[range][0], ranges[range][1]);
                break;
            }
            // printf("\n");
        }
    }

    // for(int i = 0; i < array_lengths.x; i++){
    //     printf("%ld-%ld\n",ranges[i][0], ranges[i][1]);
    // }
    // printf("\n");
    // for(int i = 0; i < array_lengths.y; i++){
    //     printf("%ld\n", ids[i]);
    // }


    printf("%d\n", total);

    return 0;
}
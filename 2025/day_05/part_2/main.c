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
uint16_t get_array_lengths(const char* filename){

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

    while(read != -1){
        read = getline(&line, &len, file_ptr);
        if(read == -1) break;

        if(line[0] == '\n') break;

        line_number++;
    }

    free(line);

    return line_number;
}

/**
 * \brief fill the arrays with the data
 * \param ranges array for the ranges
 * \param filename name of the file
 */
void fill_arrays(uint64_t ranges[][2], const char* filename){

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

    while(read != -1){
        read = getline(&line, &len, file_ptr);
        if(read == -1) break;

        if(line[0] == '\n') break;

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

    uint16_t array_length = get_array_lengths(filename);

    uint64_t ranges[array_length][2];
    // uint64_t new_ranges[array_length][2];
    uint16_t new_ranges_index = 0;

    fill_arrays(ranges, filename);

    uint64_t total = 0;

    uint8_t overlap = 1;

    while(overlap){
        overlap = 0;
        new_ranges_index = 0;

        // go through the ranges and check for overlapping ones
        for(int i = 0; i < array_length; i++){

            uint64_t start_range = ranges[i][0];
            uint64_t end_range = ranges[i][1];

            for(int ii = 0; ii < array_length; ii++){

                // skip your own range
                if(ii == i) continue;

                if(ranges[i][0] >= ranges[ii][0] && ranges[i][0] <= ranges[ii][1]){
                    if(ranges[ii][0] < start_range){
                        start_range = ranges[ii][0];
                        overlap = 1;
                    }
                }

                if(ranges[i][1] >= ranges[ii][0] && ranges[i][1] <= ranges[ii][1]){
                    if(ranges[ii][1] > end_range){
                        end_range = ranges[ii][1];
                        overlap = 1;
                    }
                }
            }

            ranges[new_ranges_index][0] = start_range;
            ranges[new_ranges_index][1] = end_range;
            new_ranges_index++;
        }
    }


    // go through the array to see if there are any ranges that are the same
     for(int i = 0; i < array_length; i++){

            for(int ii = 0; ii < array_length; ii++){
                
                // skip your own one
                if(i == ii) continue;

                if(ranges[i][0] == ranges[ii][0] && ranges[i][1] == ranges[ii][1]){
                    ranges[ii][0] = 0;
                    ranges[ii][1] = 0;
                }
            }
     }


    // go through the ranges and calculate the difference
    for(int i = 0; i < array_length; i++){

        if(ranges[i][0] == 0 && ranges[i][1] == 0) continue;

        // the plus one is because the ranges are inclusive
        total += ranges[i][1] - ranges[i][0] + 1;
    
    }

    for(int i = 0; i < array_length; i++){
        printf("%ld - %ld\n", ranges[i][0], ranges[i][1]);
    }

    printf("-------\n");

    // for(int i = 0; i < array_length; i++){
    //     printf("%ld - %ld\n", new_ranges[i][0], new_ranges[i][1]);
    // }
    


    printf("%ld\n", total);

    return 0;
}
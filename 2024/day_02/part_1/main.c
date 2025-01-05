
#include <stdio.h>
#include <stdlib.h>

#include "my_file.h"





/**
 * main function
 */
int main(int argc, char *argv[]){

    // get the filename from the comand line
    char* filename = argv[1];

    // opent the file
    FILE* file_ptr;
    file_ptr = fopen(filename,"r");

    // make sure the file could be opend
    if (file_ptr == NULL){
        printf("Cannot open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    int safe_counter = 0;
    int safe = 1;

    size_t read = 0;
    char* line = NULL;
    size_t len = 0;

    while(read != -1){
        
        safe = 1;

        read = getline(&line, &len, file_ptr);
        if(read == -1) break;

        // get the length of the array
        int array_amount = get_length_of_array(line);

        int line_array[array_amount];

        // create the array
        create_array(line_array, line);

        int negative = 0;

        int diff = line_array[0] - line_array[1];

        if(diff == 0) safe = 0;

        if(diff < 0) negative = 1;

        if(abs(diff) > 3) safe = 0;

        // go through the rest of the array
        for(int i = 1; i < array_amount - 1; i++){

            diff = line_array[i] - line_array[i+1];

            if(diff == 0){
                safe = 0;
                break;
            }

            if(negative && diff >= 0){
                safe = 0;
                break;
            }

            if(!negative && diff < 0){
                safe = 0;
                break;
            }

            if(abs(diff) > 3){
                safe = 0;
                break;
            }

        }

        if(safe){
            printf("  safe: %s", line);
            safe_counter ++;
        }
        else{
            printf("unsafe: %s", line);
        }

    }


    fclose(file_ptr);

    printf("safe: %d\n", safe_counter);

    return 0;
}
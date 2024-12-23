
#include <stdio.h>
#include <stdlib.h>

#include "my_file.h"



/**
 * \brief check if the two numbers are ok
 * \param negative is it supposed to go down or up
 * \param one the first number to compare
 * \param two the second number to compare
 */
int check(int negative, int one, int two){
    
    int diff = one - two;

    if(diff == 0) return 0;

    if(negative && diff >= 0) return 0;

    if(!negative && diff < 0) return 0;

    if(abs(diff) > 3) return 0;

    return 1;
}


void print_array(int array[], int length){

    for(int i = 0; i < length; i++){
        printf("%d ", array[i]);
    }

    printf("\n");

}


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
    int safe_1 = 1;
    int safe_2 = 1;
    int safe_level_count = 0;

    size_t read = 0;
    char* line = NULL;
    size_t len = 0;

    while(read != -1){
        safe_1 = 1;
        safe_2 = 1;
        safe_level_count = 0;


        read = getline(&line, &len, file_ptr);
        if(read == -1) break;

        // printf("\n---------------------\n");

        // get the length of the array
        int array_amount = get_length_of_array(line);

        int line_array[array_amount];

        // create the array
        create_array(line_array, line);

        int negative = 0;

        for(int i = 0; i < array_amount -1; i++){

            safe_1 = check(0, line_array[i], line_array[i+1]);
            
            if(!safe_1) break;

        }

        for(int i = 0; i < array_amount -1; i++){

            safe_2 = check(0, line_array[i], line_array[i+1]);
            
            if(!safe_2) break;

        }

        // if(!safe_1) printf("not safe up\n");
        // if(!safe_2) printf("not safe down\n");

        if(!(safe_1 || safe_2)){

            // go through the rest of the array
            for(int i = 0; i < array_amount; i++){

                int short_array[array_amount-1];
                int short_array_counter = 0;

                for(int ii = 0; ii < array_amount; ii ++){
                    if(ii == i) continue;

                    short_array[short_array_counter] = line_array[ii];
                    short_array_counter ++;

                }

                // print_array(short_array, array_amount - 1);

                for(int ii = 0; ii < array_amount -2; ii++){

                    safe_1 = check(0, short_array[ii], short_array[ii+1]);
                    
                    if(!safe_1) break;

                }

                for(int ii = 0; ii < array_amount -2; ii++){

                    safe_2 = check(1, short_array[ii], short_array[ii+1]);
                    
                    if(!safe_2) break;

                }
            
            // printf("%d\n", safe_1 || safe_2);
            if(safe_1 || safe_2) break;

            }
        }


        if(safe_1 || safe_2){
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
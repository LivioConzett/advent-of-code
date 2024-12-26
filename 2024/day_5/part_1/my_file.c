
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "my_file.h"
#include "linked.h"


/**
 * See header file
 */
node_t* create_sort_list(char* filename){

    // opent the file
    FILE* file_ptr;
    file_ptr = fopen(filename,"r");

    // make sure the file could be opend
    if (file_ptr == NULL){
        printf("Cannot open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    // create the list
    node_t* list = create_list();

    size_t read = 0;
    char* line = NULL;
    size_t len = 0;

    while(read != -1){
        read = getline(&line, &len, file_ptr);
        if(read == -1) break;
        // only read up to the empty line
        if(strlen(line) <= 1) break;

        char first_num[100];
        char second_num[100];
        int delimiter_found = 0;
        int counter = 0;

        // parse the line
        for(int i = 0; i < strlen(line);i++){
            
            // handel the delimiter
            if(line[i] == '|'){
                // close the string
                first_num[counter] = 0;
                delimiter_found = 1;
                counter = 0;
                continue;
            }

            // handel the newline
            if(line[i] == '\n'){
                // close the string
                second_num[counter] = 0;
                break;
            }

            if(!delimiter_found){
                first_num[counter] = line[i];
            }
            else{
                second_num[counter] = line[i];
            }

            counter++;
        }

        printf("%s : %s\n", first_num, second_num);

    }

    return list;
}





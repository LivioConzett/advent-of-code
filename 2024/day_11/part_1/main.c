
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked.h"


/**
 * \brief function for the list printing
 */
void print_number(void* number, void* ignore){
    printf("%d\n",*(int*)number);
}

/**
 * \brief print the list
 * \param list list to print
 */
void print_list(lnk_node_t* list){
    lnk_do_on_each_node(list, print_number, 0);
}

/**
 * Main entry point
 */
int main(int argc, char* argv[]){

    char* filename = argv[1];

    lnk_node_t* list = lnk_create_list();

    FILE* file = fopen(filename, "r");
    if(file == NULL){
        printf("Cannot open the file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    size_t len = 0;
    char* line = NULL;

    while(getline(&line, &len, file) != -1){

        char num[100];
        int num_index = 0;

        int len = strlen(line);
        
        for(int i = 0; i < len; i++){
            char c = line[i];

            if(c == ' ' || c == '\n'){
                // cap the stirng
                num[num_index] = 0;

                int* number = (int*) malloc(sizeof(int));
                if(number == NULL){
                    printf("could not malloc number\n");
                    exit(EXIT_FAILURE);
                }

                *number = atoi(num);

                lnk_append_data(list, number);

                num_index = 0;
                num[0] = 0;
            }

            num[num_index] = c;
            num_index++;
        }
    }

    print_list(list);


    return 0;
}
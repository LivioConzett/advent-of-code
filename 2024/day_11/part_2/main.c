
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
 * \brief append the number to the list
 * \param list list to append to
 * \param number number to append
 */
void append_number(lnk_node_t* list, long number){

    long* num = (long*) malloc(sizeof(long));
    if(num == NULL){
        printf("could not malloc number\n");
        exit(EXIT_FAILURE);
    }

    *num = number;

    lnk_append_data(list, num);

}

/**
 * \brief insert the number before the node
 * \param node node to insert number before
 * \param number number to insert
 */
void insert_number_before(lnk_node_t* node, long number){
    long* num = (long*) malloc(sizeof(long));
    if(num == NULL){
        printf("could not mallo number\n");
        exit(EXIT_FAILURE);
    }

    *num = number;

    lnk_insert_data_before(node, num);
}

/**
 * \brief fre the memory for the delete list
 */
void free_number(void* number, void* ignore){
    free(number);
}

/**
 * \brief delete a list and its data
 * \param list list to delete
 */
void delete_list(lnk_node_t* list){

    lnk_do_on_each_node(list, free_number, 0);

    lnk_delete_list(list);

}

/**
 * \brief check if the number has an even length
 * \param list list to append if the length is even
 * \param number number to check
 * \return 1 if the numbers length was even, else 0
 */
int check_even_length(lnk_node_t* node, long number){

    char num[100];
    sprintf(num, "%ld", number);
    int len = strlen(num);

    if(len % 2 == 0){
        
        int half = len / 2;
        char n[half+1];

        for(int ii = 0; ii < half; ii++){
            
            n[ii] = num[ii];

        }
        n[half] = 0;

        insert_number_before(node, strtol(n, NULL, 10));
        
        for(int ii = 0; ii < half; ii++){
            
            n[ii] = num[half+ii];

        }
        n[half] = 0;

        *(long*)(node->data) = strtol(n, NULL, 10);

        return 1;
    }

    return 0;
}

/**
 * Main entry point
 */
int main(int argc, char* argv[]){

    char* filename = argv[1];
    int amount = atoi(argv[2]);

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

                append_number(list, strtol(num, NULL, 10));

                num_index = 0;
                num[0] = 0;
            }

            num[num_index] = c;
            num_index++;
        }
    }

    fclose(file);

    print_list(list);

    printf("--------\n");

    long sum = 0;

    int counter = 0;

    int list_length = lnk_list_length(list);

    lnk_node_t* current = list;

    while(current->next != list){
            
        current = current->next;

        lnk_node_t* new = lnk_create_list();
        append_number(new,*(long*)current->data);


        for(int i = 0; i < amount; i++){
            
            printf("%d/%d: %d/%d\n", counter, list_length-1, i, amount-1);

            lnk_node_t* new_current = new;

            while(new_current->next != new){
                
                new_current = new_current->next;

                long* number = new_current->data;

                if(*number == 0l){
                    *number = 1l;
                    continue;
                }
                
                if(check_even_length(new_current, *number)) continue;
                
                *number *= 2024l;
            }
            
        }

        sum += lnk_list_length(new);

        delete_list(new);

        counter ++;

    }

    printf("len: %ld\n", sum);

    return 0;
}
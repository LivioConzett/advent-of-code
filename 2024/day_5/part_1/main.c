
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linked.h"
#include "my_file.h"
#include "topo.h"


void print_numbers(void* data, void* ignore){
    printf("%d\n", *(int*)data);
}

/**
 * \brief find the middle number
 * \param array array to find number in
 * \param length length of the array
 * \return middle number
 */
int find_middle_number(int* array, int length){

    int middle = length / 2;
    // printf("middle: %d, %d\n", middle, array[middle]);

    return array[middle];
}


int main(int argc, char* argv[]){

    char* filename = argv[1];

    // get the length of the sort array
    int sort_length = f_length_of_sort(filename);

    // create the arrays to hold the data
    int first_numbers[sort_length];
    int second_numbers[sort_length];

    // fill the sorting arrays with the data
    f_fill_sort_arrays(filename, first_numbers, second_numbers, sort_length);

    // for(int i = 0; i < sort_length; i++){
    //     printf("%d : %d\n", first_numbers[i], second_numbers[i]);
    // }


    // opent the file
    FILE* file_ptr;
    file_ptr = fopen(filename,"r");

    // make sure the file could be opend
    if (file_ptr == NULL){
        printf("Cannot open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    // create the list
    lnk_node_t* list = lnk_create_list();

    size_t read = 0;
    char* line = NULL;
    size_t len = 0;

    int found_empty_line = 0;

    int sum_of_middle = 0;

    while(read != -1){

        read = getline(&line, &len, file_ptr);
        if(read == -1) break;
        // only read up to the empty line
        if(strlen(line) <= 1){
            found_empty_line = 1;
            continue;
        };

        if(found_empty_line){
            
            int length = f_find_length_of_csl(line);

            // create the array for the line
            int line_array[length];
            
            f_fill_line_array(line, line_array, length);

            lnk_node_t* tree = tp_create_tree(line_array, length, first_numbers, second_numbers, sort_length);

            // tp_print_list(tree);

            // the array of the sorted list
            int sorted_list[length];
            int sorted_list_counter = length - 1;

            // sort the tree by pruning the leafs until there is nothing left
            while(1){
                tp_node_t* leaf = tp_find_leaf(tree);

                if(leaf == 0) break;
                
                sorted_list[sorted_list_counter] = leaf->number;
            
                lnk_delete_node_at(tree, lnk_find_index_of_data_pointer(tree, leaf));
                tp_delete_node(leaf);

                sorted_list_counter--;
                if(sorted_list_counter < 0) break;
            }

            // delete the tree
            lnk_do_on_each_node(tree, tp_delete_node_void, 0);
            lnk_delete_list(tree);

            // for(int i = 0; i < length; i++){
            //     printf("%d, ", sorted_list[i]);
            // }
            // printf("\n");

            // check if the array is in the correct way
            int correct = 1;
        
            for(int i = 0; i < length; i++){
                if(sorted_list[i] != line_array[i]) correct = 0;
            }

            if(correct){
                sum_of_middle += find_middle_number(line_array, length);
            }

        }
    }

    printf("sum of middle: %d\n", sum_of_middle);
    return 0;
}

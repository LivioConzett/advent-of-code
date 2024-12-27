
#include <stdio.h>
#include <stdlib.h>

#include "linked.h"
#include "my_file.h"
#include "topo.h"


void print_numbers(void* data, void* ignore){
    printf("%d\n", *(int*)data);
}

int main(int argc, char* argv[]){

    char* filename = argv[1];

    lnk_node_t* tree = f_create_dependency_tree(filename);
    
    lnk_node_t* sort_list = lnk_create_list();

    tp_print_list(tree);


    while(1){
        tp_node_t* leaf = tp_find_leaf(tree);

        if(leaf == 0) break;
        
        printf("leaf: %d\n", leaf->number);

        int* number = (int*)malloc(sizeof(int));
        if (number == NULL) {
            printf("malloc failed\n");
            exit(-1);
        }

        *number = leaf->number;

        lnk_append_data(sort_list, number);

        lnk_delete_node_at(tree, lnk_find_index_of_data_pointer(tree, leaf));
        tp_delete_node(leaf);

        // tp_print_list(tree);
        // printf("\n-----------------\n");
    }

    lnk_do_on_each_node(sort_list, print_numbers, 0);

    printf("\n");
    return 0;
}

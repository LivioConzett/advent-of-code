
#include <stdio.h>
#include <stdlib.h>

#include "linked.h"
#include "my_file.h"
#include "topo.h"



int main(int argc, char* argv[]){

    char* filename = argv[1];

    lnk_node_t* tree = f_create_dependency_tree(filename);
    
    tp_print_list(tree);


    tp_node_t* leaf = tp_find_leaf(tree);

    if(leaf != 0){
        printf("leaf: %d\n", leaf->number);
    }

    printf("\n");
    return 0;
}

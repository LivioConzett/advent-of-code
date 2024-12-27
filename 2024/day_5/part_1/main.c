
#include <stdio.h>
#include <stdlib.h>

#include "linked.h"
#include "my_file.h"
#include "topo.h"



void print_node(void* data){
    printf("%d\n", *(int*)data);
}


int find(void* data, void* number){
    return *(int*)data == *(int*)number;
}


int main(int argc, char* argv[]){

    char* filename = argv[1];

    lnk_node_t* list = lnk_create_list();

    tp_node_t* topo_1 = tp_create_node(1);

    tp_add_dependency(topo_1, 1);
    tp_add_dependency(topo_1, 2);
    tp_add_dependency(topo_1, 3);
    tp_add_dependency(topo_1, 4);
    tp_add_dependency(topo_1, 5);

    lnk_append_data(list, topo_1);

    tp_remove_dependency_from_node(topo_1, 3);

    tp_node_t* topo_2 = tp_create_node(2);

    tp_add_dependency(topo_2, 69);
    tp_add_dependency(topo_2, 420);
    tp_add_dependency(topo_2, 2);

    lnk_append_data(list, topo_2);

    tp_print_list(list);

    printf("---\n");

    tp_remove_dependency_from_list(list, 2);

    tp_print_list(list);
    
    printf("\n");
    return 0;
}

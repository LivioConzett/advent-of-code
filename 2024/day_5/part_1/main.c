
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

    tp_node_t* topo = tp_create_node(1);

    tp_add_dependency(topo, 1);
    tp_add_dependency(topo, 2);
    tp_add_dependency(topo, 3);
    tp_add_dependency(topo, 4);
    tp_add_dependency(topo, 5);

    tp_print_dependencies(topo);
    printf("\nlength: %d\n", lnk_list_length(topo->depends_on));

    tp_remove_dependency(topo, 3);
    tp_print_dependencies(topo);



    printf("\n");
    return 0;
}

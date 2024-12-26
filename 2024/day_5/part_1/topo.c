

#include "topo.h"


/**
 * See header file
 */
topo_node_t* create_topo_node(){

    topo_node_t* node = (topo_node_t*) malloc(sizeof(topo_node_t));
    if (node == NULL) {
        printf("malloc failed\n");
        exit(-1);
    }

    node->depends_on = create_list();

    return node;

}


/**
 * See header file
 */
void print_dependencies(topo_node_t* anchor){

    node_t* head = anchor->depends_on;

    // printf("1: %p\n", anchor->depends_on);
    
    // Go through the list.
    while(head->next != anchor->depends_on){
        head = head->next;

        // printf("1: %p\n", head->next);
        printf("%d, ", *(int*)head->data);

    }
}

/**
 * See header
 */
void add_dependency(topo_node_t* anchor, int dependant_on){

    int* number = (int*) malloc(sizeof(int));
    if (number == NULL) {
        printf("malloc failed\n");
        exit(-1);
    }

    *number = dependant_on;

    node_t* number_node = create_node(number);

    append_node(anchor->depends_on, number_node);

}




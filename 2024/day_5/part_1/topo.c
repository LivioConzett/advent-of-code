

#include "topo.h"


/**
 * See header file
 */
tp_node_t* tp_create_node(){

    tp_node_t* node = (tp_node_t*) malloc(sizeof(tp_node_t));
    if (node == NULL) {
        printf("malloc failed\n");
        exit(-1);
    }

    node->depends_on = lnk_create_list();

    return node;

}

/**
 * \brief print function to use to print the dependency list
 * \param data pointer to the data from the linked list
 */
static void tp_print_dependency_node(void* data){
    printf("%d, ", *(int*)data);
}

/**
 * See header file
 */
void tp_print_dependencies(tp_node_t* anchor){


    lnk_do_on_each_node(anchor->depends_on, tp_print_dependency_node);


    // lnk_node_t* head = anchor->depends_on;

    // // printf("1: %p\n", anchor->depends_on);
    
    // // Go through the list.
    // while(head->next != anchor->depends_on){
    //     head = head->next;

    //     // printf("1: %p\n", head->next);
    //     printf("%d, ", *(int*)head->data);

    // }
}

/**
 * See header
 */
void tp_add_dependency(tp_node_t* anchor, int dependant_on){

    int* number = (int*) malloc(sizeof(int));
    if (number == NULL) {
        printf("malloc failed\n");
        exit(-1);
    }

    *number = dependant_on;

    lnk_node_t* number_node = lnk_create_node(number);

    lnk_append_node(anchor->depends_on, number_node);

}




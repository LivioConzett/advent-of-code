

#include "topo.h"


/**
 * See header file
 */
tp_node_t* tp_create_node(int number){

    tp_node_t* node = (tp_node_t*) malloc(sizeof(tp_node_t));
    if (node == NULL) {
        printf("malloc failed\n");
        exit(-1);
    }

    node->number = number;
    node->depends_on = lnk_create_list();

    return node;

}

/**
 * \brief print function to use to print the dependency list
 * \param data pointer to the data from the linked list
 */
static void tp_print_dependency_node(void* data, void* ignore){
    printf("%d, ", *(int*)data);
}

/**
 * \brief check if the data is the number
 * \param data the data to check
 * \param number the number to check against the data
 * \return 1 if the data is the number, else 0
 */
static int tp_check_dependency(void* data, void* number){
    return *(int*)data == *(int*)number;
}

/**
 * See header file
 */
void tp_print_dependencies(tp_node_t* anchor){
    lnk_do_on_each_node(anchor->depends_on, tp_print_dependency_node, 0);
}

/**
 * \brief print the topo node
 * \param node the node to print
 */
static void tp_print_node(void* data, void* ignore){

    tp_node_t* node = (tp_node_t*)data;

    printf("node: %d\n", node->number);
    tp_print_dependencies(data);

    printf("\n=====\n");
}

/**
 * See header
 */
void tp_add_dependency(tp_node_t* anchor, int dependant_on){

    // check if the dependency already exists
    int index = lnk_find_index_of_data(anchor->depends_on, tp_check_dependency, &dependant_on);
    if(index > 0) return;


    int* number = (int*) malloc(sizeof(int));
    if (number == NULL) {
        printf("malloc failed\n");
        exit(-1);
    }

    *number = dependant_on;

    lnk_node_t* number_node = lnk_create_node(number);

    lnk_append_node(anchor->depends_on, number_node);

}

/**
 * See header
 */
void tp_remove_dependency_from_node(tp_node_t* anchor, int dependent_remove){

    int index = lnk_find_index_of_data(anchor->depends_on, tp_check_dependency, &dependent_remove);

    if(index < 0) return;

    tp_node_t* data = lnk_get_data_at_index(anchor->depends_on, index);

    // delete the node
    lnk_delete_node_at(anchor->depends_on, index);

    // free the data
    free(&(data->number));
}


/**
 * \brief remove a dependency from a node, but with void pointers
 */
static void tp_remove_dependency_from_list_void(void* anchor, void* dependent_remove){
    tp_remove_dependency_from_node((tp_node_t*)anchor, *(int*)dependent_remove);
}


/**
 * See header
 */
void tp_remove_dependency_from_list(lnk_node_t* anchor, int dependent_remove){
    lnk_do_on_each_node(anchor, tp_remove_dependency_from_list_void, &dependent_remove);
}


/**
 * See header
 */
int tp_amount_of_dependencies(tp_node_t* anchor){
    return lnk_list_length(anchor->depends_on);
}

/**
 * See header
 */
void tp_print_list(lnk_node_t* anchor){
    lnk_do_on_each_node(anchor, tp_print_node, 0);
}



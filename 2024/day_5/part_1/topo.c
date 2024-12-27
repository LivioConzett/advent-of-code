

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
static void tp_print_dependency_node(void* data){
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
    lnk_do_on_each_node(anchor->depends_on, tp_print_dependency_node);
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
void tp_remove_dependency(tp_node_t* anchor, int dependent_remove){

    int index = lnk_find_index_of_data(anchor->depends_on, tp_check_dependency, &dependent_remove);

    if(index < 0) return;

    lnk_delete_node_at(anchor->depends_on, index);

}

/**
 * See header
 */
int tp_amount_of_dependencies(tp_node_t* anchor){
    return lnk_list_length(anchor->depends_on);
}



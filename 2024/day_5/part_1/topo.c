

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
 * \brief check if the node is the same as the number
 * \param node the node
 * \param number the number
 * \return 1 if the same, else 0
 */
static int tp_check_nodes(void * node, void* number){
    return ((tp_node_t*)node)->number == *(int*)number;
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

/**
 * See header
 */
int tp_find_index_of_data(lnk_node_t* anchor, int number){
    return lnk_find_index_of_data(anchor, tp_check_nodes, &number);
}

/**
 * See header
 */
tp_node_t* tp_find_leaf(lnk_node_t* list){

    // go through the nodes

    lnk_node_t* head_1 = list;

    int found = 0;

    // go through the nodes first
    while(head_1->next != list){
        head_1 = head_1->next;

        int number =  ((tp_node_t*) head_1->data)->number;

        found = 0;

        lnk_node_t* head_2 = list;

        // go through the nodes a second time
        while(head_2->next != list){
            head_2 = head_2->next;

            // check if the number we are looking for is in the dependency list
            int index = lnk_find_index_of_data(((tp_node_t*)head_2->data)->depends_on, tp_check_dependency, &number);

            if(index > -1) found = 1;

        }

        if(!found) return head_1->data;
    }

    return 0;
}


/**
 * \brief Free the memory of the data in the node
 * \param data the node to clear the data from
 */
static void tp_free_dependency(void* data, void* ignore){
    free(data);
}

/**
 * See header
 */
void tp_delete_node_void(void* node, void* ignore){

    tp_delete_node(node);

}

/**
 * See header
 */
void tp_delete_node(tp_node_t* node){

    // free the dependencies
    lnk_do_on_each_node(node->depends_on, tp_free_dependency, 0);

    // delete the list itself
    lnk_delete_list(node->depends_on);

    // free the node
    free(node);
}

/**
 * \brief check if a number is in an array
 * \param number number to search for
 * \param array the array to look through
 * \param array_length length of the array
 * \return 0 if not found, 1 if found
 */
int tp_is_number_in_array(int number, int* array, int array_length){

    for(int i = 0; i < array_length; i ++){
        if(array[i] == number) return 1;
    }

    return 0;
}


/**
 * See header
 */
lnk_node_t* tp_create_tree(int* array, int array_length, int* first_numbers, int* second_numbers, int numbers_length){

    lnk_node_t* tree = lnk_create_list();

    for(int i = 0; i < numbers_length; i++){
    
        if(tp_is_number_in_array(first_numbers[i], array, array_length) && 
           tp_is_number_in_array(second_numbers[i], array, array_length)
           ){
                
                int index = tp_find_index_of_data(tree, second_numbers[i]);

                if(index < 0){
                    tp_node_t* node = tp_create_node(second_numbers[i]);
                    tp_add_dependency(node, first_numbers[i]);
                    lnk_append_data(tree, node);
                }
                else{
                    tp_node_t* node = (tp_node_t*)lnk_get_data_at_index(tree, index);
                    tp_add_dependency(node, first_numbers[i]);
                }

                // add the other number also as a node
                index = tp_find_index_of_data(tree, first_numbers[i]);
                
                if(index < 0){
                    tp_node_t* node = tp_create_node(first_numbers[i]);
                    lnk_append_data(tree, node);
                }

           }
    }


    return tree;
}


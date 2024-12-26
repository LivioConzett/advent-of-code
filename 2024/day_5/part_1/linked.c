
#include "linked.h"


/**
 * See header file
 */
void init_list(node_t* start){

    start->next = start;
    start->previous = start;

}

/**
 * See header
 */
node_t* create_node(int number){

    node_t* node = (node_t*) malloc(sizeof(node_t));
    if (node == NULL) {
        printf("malloc failed\n");
        exit(-1);
    }
    node->number = number;

    return node;
}


/**
 * See header file
 */
void append_node(node_t* start, node_t* to_append){

    node_t* head = start->next;

    // find the end
    while(head->next != start){
        head = head->next;
    }


    to_append->next = head->next;
    to_append->previous = head;

    // Set the previous link of the next element
    // to point to the element we are appending.
    head->next->previous = to_append;

    // Set the next element to be the element to append.
    head->next = to_append;

}


/**
 * See header file
 */
void print_list(node_t* start){

    node_t* head = start->next;

    printf("%d\n", start->number);

    // Go through the list.
    while(head->next != start){

        printf("%d\n", head->number);
        head = head->next;
    }

    printf("%d\n", head->number);
}



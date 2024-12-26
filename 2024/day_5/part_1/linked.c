
#include "linked.h"


/**
 * See header file
 */
node_t* create_list(){

    node_t* start = create_node(0);

    start->next = start;
    start->previous = start;

    return start;
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
void insert_node(node_t* start, node_t* to_insert, int index){

    // if the index is too great, just append the node
    if(index > list_length(start)){
        append_node(start, to_insert);
        return;
    }

    node_t* head = start->next;
    int node_counter = 0;

    // find the end
    while(head->next != start && node_counter < index){
        head = head->next;
        node_counter++;
    }

    to_insert->next = head;
    to_insert->previous = head->previous;

    head->previous->next = to_insert;
    head->previous = to_insert;


}

/**
 * See header file
 */
int list_length(node_t* start){

    node_t* head = start->next;

    int counter = 0;

    while(head->next != start){
        head = head->next;
        counter++;
    }

    return counter;
}

/**
 * See header file
 */
int get_index_of(node_t* start, int number){
    
    node_t* head = start->next;

    int counter = 0;
    int index = -1;

    // Go through the list.
    while(head->next != start){
        
        if(head->number == number){
            index = counter;
            break;
        }
        
        head = head->next;
        counter++;
    }

    // incase it's the last one in the list
    if(head->number == number) index = counter;

    return index;
}


/**
 * See header file
 */
void print_list(node_t* start){

    node_t* head = start->next;

    // Go through the list.
    while(head->next != start){

        printf("%d\n", head->number);
        head = head->next;
    }

    printf("%d\n", head->number);
}




#include "linked.h"


/**
 * See header file
 */
node_t* create_list(){

    char* data = (char*) malloc(sizeof(char));
    if (data == NULL) {
        printf("malloc failed\n");
        exit(-1);
    }

    node_t* anchor = create_node(data);

    anchor->next = anchor;
    anchor->previous = anchor;

    return anchor;
}

/**
 * See header
 */
node_t* create_node(void* data){

    node_t* node = (node_t*) malloc(sizeof(node_t));
    if (node == NULL) {
        printf("malloc failed\n");
        exit(-1);
    }
    node->data = data;

    return node;
}


/**
 * See header file
 */
void append_node(node_t* anchor, node_t* to_append){

    node_t* head = anchor;

    // find the end
    while(head->next != anchor){
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
void insert_node(node_t* anchor, node_t* to_insert, int index){

    // if the index is too great, just append the node
    if(index > list_length(anchor)){
        append_node(anchor, to_insert);
        return;
    }

    node_t* head = anchor->next;
    int node_counter = 0;

    // find the end
    while(head->next != anchor && node_counter < index){
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
int list_length(node_t* anchor){

    node_t* head = anchor;

    int counter = 0;

    while(head->next != anchor){
        head = head->next;
        counter++;
    }

    return counter;
}

/**
 * See header file
 */
int get_index_of(node_t* anchor, void* data){
    
    node_t* head = anchor->next;

    int counter = 0;
    int index = -1;

    // Go through the list.
    while(head->next != anchor){
        
        if(head->data == data){
            index = counter;
            break;
        }
        
        head = head->next;
        counter++;
    }

    // incase it's the last one in the list
    if(head->data == data) index = counter;

    return index;
}





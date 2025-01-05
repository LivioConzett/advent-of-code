
#include "linked.h"


/**
 * See header file
 */
lnk_node_t* lnk_create_list(){

    // char* data = (char*) malloc(sizeof(char));
    // if (data == NULL) {
    //     printf("malloc failed\n");
    //     exit(-1);
    // }

    lnk_node_t* anchor = lnk_create_node(NULL);

    anchor->next = anchor;
    anchor->previous = anchor;

    return anchor;
}

/**
 * See header
 */
lnk_node_t* lnk_create_node(void* data){

    lnk_node_t* node = (lnk_node_t*) malloc(sizeof(lnk_node_t));
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
void lnk_append_node(lnk_node_t* anchor, lnk_node_t* to_append){

    lnk_node_t* head = anchor;

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
 * See header
 */
void lnk_append_data(lnk_node_t* anchor, void* data){

    lnk_node_t* node = lnk_create_node(data);

    lnk_append_node(anchor, node);
}


/**
 * See header file
 */
void lnk_insert_node(lnk_node_t* anchor, lnk_node_t* to_insert, int index){

    // if the index is too great, just append the node
    if(index > lnk_list_length(anchor)){
        lnk_append_node(anchor, to_insert);
        return;
    }

    lnk_node_t* head = anchor->next;
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
 * See header
 */
void lnk_insert_data(lnk_node_t* anchor, void* data, int index){

    lnk_node_t* node = lnk_create_node(data);

    lnk_insert_node(anchor, node, index);
}


/**
 * See header
 */
void lnk_insert_before(lnk_node_t* anchor, lnk_node_t* insert){
    insert->previous = anchor->previous;
    insert->next = anchor;
    anchor->previous->next = insert;
    anchor->previous = insert;
}


/**
 * See header
 */
void lnk_insert_after(lnk_node_t* anchor, lnk_node_t* insert){
    insert->previous = anchor;
    insert->next = anchor->next;
    anchor->next->previous = insert;
    anchor->next = insert;
}


/**
 * See header
 */
void lnk_insert_data_before(lnk_node_t* anchor, void* data){

    lnk_node_t* node = lnk_create_node(data);

    lnk_insert_before(anchor, node);
}


/**
 * See header
 */
void lnk_insert_data_after(lnk_node_t* anchor, void* data){

    lnk_node_t* node = lnk_create_node(data);

    lnk_insert_after(anchor, node);

}


/**
 * See header file
 */
int lnk_list_length(lnk_node_t* anchor){

    lnk_node_t* head = anchor;

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
int lnk_find_index_of_data_pointer(lnk_node_t* anchor, void* data){
    
    lnk_node_t* head = anchor;

    int counter = 0;
    int index = -1;

    // Go through the list.
    while(head->next != anchor){
        
        head = head->next;
        if(head->data == data){
            index = counter;
            break;
        }
        
        counter++;
    }

    return index;
}

/**
 * See header
 */
void* lnk_get_data_at_index(lnk_node_t* anchor, int index){

    lnk_node_t* head = anchor;

    int counter = 0;

    // Go through the list.
    while(head->next != anchor){
        head = head->next;
        
        if(counter == index){
            return head->data;
        }
        
        counter++;
    }

    return 0;
}



/**
 * See header
 */
void lnk_do_on_each_node(lnk_node_t* anchor, void(*function)(void*, void*), void* additional){

    lnk_node_t* head = anchor;

    while(head->next != anchor){
        head = head->next;
        function(head->data, additional);
    }
}

/**
 * See header
 */
int lnk_find_index_of_data(lnk_node_t* anchor, int(*function)(void*, void*), void* additional){

    lnk_node_t* head = anchor;

    int counter = 0;

    while(head->next != anchor){
        head = head->next;
        if(function(head->data, additional)) return counter;
        counter ++;
    }

    return -1;
}

/**
 * See header
 */
void lnk_delete_node_at(lnk_node_t* anchor, int index){

    lnk_node_t* head = anchor;

    int counter = 0;

    while(head->next != anchor){
        head = head->next;
        if(counter == index){
            
            // unhook the head from the list
            head->previous->next = head->next;
            head->next->previous = head->previous;

            // free the memory of the node
            free(head);
            return;
        }
        counter ++;
    }
}


/**
 * See header
 */
void lnk_delete_list(lnk_node_t* anchor){


    lnk_node_t* current = anchor;
    lnk_node_t* next;


    while(current->next != anchor){

        next = current->next;
        free(current);
        current = next;

    }

    free(current);
}


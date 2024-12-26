
#include <stdio.h>
#include <stdlib.h>

#ifndef LINKED_H
#define LINKED_H

typedef struct node_t node_t;

// structure of one node
struct node_t{
    void* data;
    node_t* next;
    node_t* previous;
};

/**
 * \brief Initialize a list
 */
node_t* create_list();

/**
 * \brief create a node
 * \param data data the node holds
 * \return node_t pointer to the created node
 */
node_t* create_node(void* data);

/**
 * \brief Append a node at the end of the linked list
 * \param anchor anchor node of the list
 * \param to_append node to append
 */
void append_node(node_t* anchor, node_t* to_append);

/**
 * \brief insert a node at the indexed position.
 *        If the index is too great, it just appends the node.
 * \param anchor anchor node of the list
 * \param to_insert node to insert
 * \param index index to place the node into
 */
void insert_node(node_t* anchor, node_t* to_insert, int index);

/**
 * \brief Gets the length of a list
 * \param anchor anchor node of the list
 */
int list_length(node_t* anchor);

/**
 * \brief Gets the index of the node with a given number in it
 * \param anchor anchor node of the list
 * \param number number we are looking for
 * \return the index of the node, or -1 if not found
 */
int get_index_of(node_t* anchor, void* data);



#endif
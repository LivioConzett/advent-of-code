
#include <stdio.h>
#include <stdlib.h>

#ifndef LINKED_H
#define LINKED_H

typedef struct node_t node_t;

// structure of one node
struct node_t{
    int number;
    node_t* next;
    node_t* previous;
};

/**
 * \brief Initialize a list
 * \param start starting node
 */
void init_list(node_t* start);

/**
 * \brief create a node
 * \param number number the node holds
 * \return node_t pointer to the created node
 */
node_t* create_node(int number);

/**
 * \brief Append a node at the end of the linked list
 * \param start starting node
 * \param to_append node to append
 */
void append_node(node_t* start, node_t* to_append);

/**
 * \brief print the whole linked list
 * \param start the starting node of the list
 */
void print_list(node_t* start);

#endif
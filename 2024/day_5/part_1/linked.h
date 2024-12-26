
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
 */
node_t* create_list();

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
 * \brief insert a node at the indexed position.
 *        If the index is too great, it just appends the node.
 * \param start start of the list
 * \param to_insert node to insert
 * \param index index to place the node into
 */
void insert_node(node_t* start, node_t* to_insert, int index);

/**
 * \brief Gets the length of a list
 * \param start the start node of the list
 */
int list_length(node_t* start);

/**
 * \brief Gets the index of the node with a given number in it
 * \param start start node of the list
 * \param number number we are looking for
 * \return the index of the node, or -1 if not found
 */
int get_index_of(node_t* start, int number);

/**
 * \brief print the whole linked list
 * \param start the starting node of the list
 */
void print_list(node_t* start);

#endif
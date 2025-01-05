
#include <stdio.h>
#include <stdlib.h>

#ifndef LINKED_H
#define LINKED_H

typedef struct lnk_node_t lnk_node_t;

// structure of one node
struct lnk_node_t{
    void* data;
    lnk_node_t* next;
    lnk_node_t* previous;
};

/**
 * \brief Initialize a list
 */
lnk_node_t* lnk_create_list();

/**
 * \brief create a node
 * \param data data the node holds
 * \return node_t pointer to the created node
 */
lnk_node_t* lnk_create_node(void* data);

/**
 * \brief Append a node at the end of the linked list
 * \param anchor anchor node of the list
 * \param to_append node to append
 */
void lnk_append_node(lnk_node_t* anchor, lnk_node_t* to_append);

/**
 * \brief append data to the list
 * \param anchor list to append to
 * \param data data to append
 */
void lnk_append_data(lnk_node_t* anchor, void* data);

/**
 * \brief insert a node at the indexed position.
 *        If the index is too great, it just appends the node.
 * \param anchor anchor node of the list
 * \param to_insert node to insert
 * \param index index to place the node into
 */
void lnk_insert_node(lnk_node_t* anchor, lnk_node_t* to_insert, int index);

/**
 * \brief insert data at the indexed position. 
 *        If the index is too great, it just appends the data. 
 * \param anchor anchor node to insert 
 * \param data data to insert 
 * \param index index to place the node into
 */
void lnk_insert_data(lnk_node_t* anchor, void* data, int index);

/**
 * \brief insert a node before another node
 * \param anchor node to insert a node before
 * \param insert node to insert before the anchor
 */
void lnk_insert_before(lnk_node_t* anchor, lnk_node_t* insert);

/**
 * \brief insert a node after another node
 * \param anchor node to insert a node after
 * \param insert node to insert after the anchor
 */
void lnk_insert_after(lnk_node_t* anchor, lnk_node_t* insert);

/**
 * \brief insert data before node
 * \param anchor node to insert data before
 * \param data data to insert
 */
void lnk_insert_data_before(lnk_node_t* anchor, void* data);

/**
 * \brief insert data after node
 * \param anchor node to insert data after
 * \param data data to insert
 */
void lnk_insert_data_after(lnk_node_t* anchor, void* data);

/**
 * \brief Gets the length of a list
 * \param anchor anchor node of the list
 */
int lnk_list_length(lnk_node_t* anchor);

/**
 * \brief Gets the index of the node with a given number in it
 * \param anchor anchor node of the list
 * \param number number we are looking for
 * \return the index of the node, or -1 if not found
 */
int lnk_find_index_of_data_pointer(lnk_node_t* anchor, void* data);

/**
 * \brief Get the data at a certain index
 * \param anchor list to get the data from
 * \param index index in the list to get
 * \return pointer to the data at the index, 0 if nothing was found
 */
void* lnk_get_data_at_index(lnk_node_t* anchor, int index);

/**
 * \brief Takes a function and does this on every node in the list
 * \param anchor list to use
 * \param function the function to do on each node
 * \param additional additional value to give the function
 */
void lnk_do_on_each_node(lnk_node_t* anchor, void(*function)(void*, void*), void* additional);

/**
 * \brief find a node according to a function
 * \param anchor list to look through
 * \param function function to use. Has to return 1 or 0, for found or not found
 * \param additional additional value to give the function
 * \return index of the node, -1 if nothing was found
 */
int lnk_find_index_of_data(lnk_node_t* anchor, int(*function)(void*, void*), void* additional);

/**
 * \brief Delete the node at index. Will not delete the data the node is pointing too.
 * \param anchor list to delete node in
 * \param index node at index to delete
 */
void lnk_delete_node_at(lnk_node_t* anchor, int index);

/**
 * \brief delete the list.
 *        Goes through the list and frees every node. 
 *        Will not delete the data the nodes are pointing too. 
 * \param anchor list to delete
 */
void lnk_delete_list(lnk_node_t* anchor);

#endif
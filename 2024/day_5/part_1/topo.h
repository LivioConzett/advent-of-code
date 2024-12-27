
#ifndef TOPO_H
#define TOPO_H

#include "linked.h"

typedef struct tp_node_t tp_node_t;

struct tp_node_t{
    int number;
    lnk_node_t* depends_on;
};

/**
 * \brief create a topo node
 * \param number number of the node
 * \return pointer to the topo node
 */
tp_node_t* tp_create_node(int number);


/**
 * \brief print the dependancies of a topo node
 * \param anchor the node to print the dependancies from
 */
void tp_print_dependencies(tp_node_t* anchor);

/**
 * \brief add a dependency to the topo node. 
 *        If the dependency already exists, nothing will happen.
 * \param anchor topo node to add the dependency to
 * \param dependent_on number to add
 */
void tp_add_dependency(tp_node_t* anchor, int dependent_on);

/**
 * \brief remove a dependency from the node
 * \param anchor node to remove the dependency from
 */
void tp_remove_dependency(tp_node_t* anchor, int dependent_remove);

/**
 * \brief get the amount of dependencies of a node
 * \return amount of dependencies
 */
int tp_amount_of_dependencies(tp_node_t* anchor);

#endif
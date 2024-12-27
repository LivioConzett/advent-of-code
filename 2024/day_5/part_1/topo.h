
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
 * \return pointer to the topo node
 */
tp_node_t* tp_create_node();


/**
 * \brief print the dependancies of a topo node
 * \param anchor the node to print the dependancies from
 */
void tp_print_dependencies(tp_node_t* anchor);

/**
 * \brief add a dependency to the topo node
 * \param anchor topo node to add the dependency to
 * \param dependent_on number to add
 */
void tp_add_dependency(tp_node_t* anchor, int dependent_on);


#endif

#ifndef TOPO_H
#define TOPO_H

#include "linked.h"

typedef struct topo_node_t topo_node_t;

struct topo_node_t{
    int number;
    node_t* depends_on;
};

/**
 * \brief create a topo node
 * \return pointer to the topo node
 */
topo_node_t* create_topo_node();


/**
 * \brief print the dependancies of a topo node
 * \param anchor the node to print the dependancies from
 */
void print_dependencies(topo_node_t* anchor);

/**
 * \brief add a dependency to the topo node
 * \param anchor topo node to add the dependency to
 * \param dependent_on number to add
 */
void add_dependency(topo_node_t* anchor, int dependent_on);


#endif
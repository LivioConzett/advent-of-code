
#include <stdio.h>
#include <stdlib.h>

#include "linked.h"


int main(int argc, char* argv[]){

    char* filename = argv[1];

    node_t* start = create_node(0);

    init_list(start);

    node_t* one = create_node(1);

    append_node(start, one);

    node_t* two = create_node(2);

    append_node(start, two);

    print_list(start);

    return 0;
}
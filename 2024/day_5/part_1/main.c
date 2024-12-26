
#include <stdio.h>
#include <stdlib.h>

#include "linked.h"
#include "my_file.h"


int main(int argc, char* argv[]){

    char* filename = argv[1];

    node_t* start = create_list();

    node_t* zero = create_node(0);

    append_node(start, zero);

    node_t* one = create_node(1);

    append_node(start, one);

    node_t* two = create_node(2);

    append_node(start, two);

    node_t* three = create_node(3);

    insert_node(start, three, 4);

    print_list(start);

    return 0;
}
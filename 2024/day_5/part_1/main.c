
#include <stdio.h>
#include <stdlib.h>

#include "linked.h"
#include "my_file.h"
#include "topo.h"



int main(int argc, char* argv[]){

    char* filename = argv[1];

    topo_node_t* topo = create_topo_node();

    add_dependency(topo, 1);
    add_dependency(topo, 2);
    add_dependency(topo, 3);
    add_dependency(topo, 4);

    print_dependencies(topo);
    printf("length: %d\n", list_length(topo->depends_on));



    return 0;
}

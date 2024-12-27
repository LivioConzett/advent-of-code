
#include <stdio.h>
#include <stdlib.h>

#include "linked.h"
#include "my_file.h"
#include "topo.h"



void print_node(void* data){
    printf("%d\n", *(int*)data);
}


int find(void* data, void* number){
    return *(int*)data == *(int*)number;
}


int main(int argc, char* argv[]){

    char* filename = argv[1];

    // topo_node_t* topo = create_topo_node();

    // add_dependency(topo, 1);
    // add_dependency(topo, 2);
    // add_dependency(topo, 3);
    // add_dependency(topo, 4);

    // print_dependencies(topo);
    // printf("length: %d\n", list_length(topo->depends_on));

    int one = 1;
    int two = 2;
    int three = 3;
    int four = 4;
    int five = 5;
    int six = 6;
    int seven = 7;
    int eight = 8;
    int nine = 9;
    int ten = 10;
    int eleven = 11;

    lnk_node_t* list = lnk_create_list();


    lnk_append_data(list, &one);
    lnk_append_data(list, &two);
    lnk_append_data(list, &three);
    lnk_append_data(list, &four);
    lnk_append_data(list, &five);
    lnk_append_data(list, &six);
    lnk_append_data(list, &seven);
    lnk_append_data(list, &eight);
    lnk_append_data(list, &nine);
    lnk_append_data(list, &ten);


    lnk_do_on_each_node(list, print_node);

    int index = lnk_find_node(list, find, &six);

    printf("index: %d\n", index);

    lnk_delete_node_at(list, index);

    lnk_do_on_each_node(list, print_node);

    printf("======\n");

    lnk_insert_data(list, &eleven, 6);

    lnk_do_on_each_node(list, print_node);

    lnk_delete_list(list);

    return 0;
}

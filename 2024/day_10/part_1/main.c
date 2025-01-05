
#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "vector.h"


/**
 * Main entry point
 */
int main(int argc, char* argv[]){

    char* filename = argv[1];

    vector_t field_size = f_get_sie_of_field(filename);

    v_print(&field_size, 1);

    return 0;
}


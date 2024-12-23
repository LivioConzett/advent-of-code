
#include <stdio.h>
#include <stdlib.h>

#include "my_file.h"


/**
 * Main function
 */
int main(int argc, char *argv[]){

    // get the filename from the comand line
    char* filename = argv[1];

    // get the amount of lines in the file
    int lines = amount_of_lines(filename);

    // creat the arrays
    int array_1[lines];
    int array_2[lines];

    // read the file into the arrays
    // read_file_to_array(array_1, lines, 0, filename);
    read_file_to_array(array_2, lines, 1, filename);

    return 0;
}



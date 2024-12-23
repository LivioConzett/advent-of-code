
#include <stdio.h>
#include <stdlib.h>


/**
 * \brief Get the amount of lines in a file
 * \param filename string of the filename to open
 * \return amount of lines in the file
 */
int amount_of_lines(char* filename){
    
    // opent the file
    FILE* file_ptr;
    file_ptr = fopen(filename,"r");

    int line_counter = 0;

    // make sure the file could be opend
    if (file_ptr == NULL){
        printf("Cannot open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    size_t read = 0;
    char* line = NULL;
    size_t len = 0;

    while(read != -1){
        read = getline(&line, &len, file_ptr);
        line_counter++;
    }


    // close the file
    fclose(file_ptr);

    return line_counter;
}


/**
 * \brief read a certain column of a file into the given array
 * \param array array to writ the values into
 * \param length length of the array
 * \param column which column to read into the array. starts at 0
 * \param filename string of the file name
 */
void read_file_to_array(int array[], int length, int column, char* filename){
    
    // opent the file
    FILE* file_ptr;
    file_ptr = fopen(filename,"r");

    int line_counter = 0;

    // make sure the file could be opend
    if (file_ptr == NULL){
        printf("Cannot open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    

}


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
    read_file_to_array(array_1, lines, 0, filename);
    read_file_to_array(array_2, lines, 1, filename);


    printf("%d\n", lines);

    return 0;
}




#include <stdio.h>
#include <stdlib.h>

#include "my_file.h"


/**
 * \brief the compare function for the sorting
 * \param a first element to compare
 * \param b second element to compare
 * \return if a is greater than b or not
 */
int compare(const void* a, const void* b){

    // cast the pointers to a int
    int int_a = * ( (int*) a );
    int int_b = * ( (int*) b );
     
    if ( int_a == int_b ) return 0;
    else if ( int_a < int_b ) return -1;
    else return 1;
}


/**
 * \brief returns the amount of times the number occurs in the array
 * \param number number to look for
 * \param array array to look for the number in
 * \param length length of the array
 * \return amount of times the number was found in the array
 */
int count_occurrences(int number, int array[], int length){
    int count = 0;

    for(int i = 0; i < length; i++){
        if(number == array[i]){
            count ++;
        }
    }

    return count;
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

    // sort the arrays
    qsort(array_1, lines, sizeof(int), compare);
    qsort(array_2, lines, sizeof(int), compare);

    int sum = 0;

    // go through the arrays and compare the numbers
    for(int i = 0; i < lines; i++){
        sum += abs(array_1[i] * count_occurrences(array_1[i], array_2, lines));
    }

    printf("%d\n", sum);

    return 0;
}



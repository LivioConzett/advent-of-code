
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "mathe.h"


/**
 * \brief get the length of array needed to parse the line into
 * \param line string to parse
 * \return length of array needed
 */
static int m_get_array_length_from_line(char* line){

    // start at 1, because there is one more number than space
    int len = 1;

    for(int i = 0; i < strlen(line); i++){
        if(line[i] == ' ') len++;
    }

    return len;
}

/**
 * \brief fill the array by parsing the line
 * \param line string to parse
 * \param array array to parse the numbers into
 */
static void m_fill_array(char* line, int* array){

    char number[100];
    int num_counter = 0;
    int array_counter = 0;

    for(int i = 0; i < strlen(line); i++){
        char c = line[i];

        if(c == ':') continue;

        if(c == ' ' || c == '\n'){
            // cap the string
            number[num_counter] = 0;
            
            array[array_counter] = atoi(number);
            
            num_counter = 0;
            array_counter++;
            continue;
        }

        number[num_counter] = c;
        num_counter ++;
    }

}


/**
 * See header
 */
int m_evaluate_line(char* line){

    int array_length = m_get_array_length_from_line(line);

    int num_array[array_length];

    m_fill_array(line, num_array);

    for(int i = 0; i < array_length; i++){
        printf("%d, ", num_array[i]);
    }
    printf("\n");



    return 0;
}



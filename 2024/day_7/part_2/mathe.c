
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>


#include "mathe.h"


/**
 * \brief get the length of array needed to parse the line into
 * \param line string to parse
 * \return length of array needed
 */
int m_get_array_length_from_line(char* line){

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
void m_fill_array(char* line, unsigned long long* array){

    char number[100];
    char* endpointer;
    int num_counter = 0;
    int array_counter = 0;

    for(int i = 0; i < strlen(line); i++){
        char c = line[i];

        if(c == ':') continue;

        if(c == ' ' || c == '\n'){
            // cap the string
            number[num_counter] = 0;
            
            // can't use atoi since the numbers to read in are too large for an int.
            array[array_counter] = strtoll(number,&endpointer,10);
            
            num_counter = 0;
            array_counter++;
            continue;
        }

        number[num_counter] = c;
        num_counter ++;
    }
}

/**
 * \brief Reverse a string
 * \param string string to reverse
 */
void m_reverse_string(char* string){

    int length = strlen(string);

    char new[length+1];

    for(int i = 0; i < length; i++){
        new[i] = string[length -1 - i];
    }
    new[length] = 0;

    strcpy(string, new);

}

/**
 * \brief Create the operand line for the number
 * \param line line to place the operands in
 * \param number number to count up to
 * \param width the width of the array to fill
 */
void m_create_operand_line(char* line, int number, int width){

    static char CHARS[] = {"+*|"};
    static int base = 3;

    int line_counter = 0;

    do{
        line[line_counter] = CHARS[number % base];
        number = number / base;
        line_counter ++;
    }while(number > 0);

    // cap the string
    line[line_counter] = 0;

    int length = strlen(line);
    int buffer = width - length;

    for(int i = 0; i < buffer; i++){
        line[line_counter] = CHARS[0];
        line_counter++;
    }

    // cap the string again
    line[line_counter] = 0;

    m_reverse_string(line);
}

/**
 * \brief create the array of operands
 * \param array 2d array to place the operands in
 * \param height height of the 2d array
 * \param width width of the 2d array
 */
void m_create_operand_array(char* array, int height, int width){
    
    char line[100];

    for(int y = 0; y < height; y++){
        
        m_create_operand_line(line, y, width);

        for(int x = 0; x < width; x++){
            array[(y * width) + x] = line[x];
        }
    }
}

/**
 * \brief concat two numbers
 * \param first first number
 * \param second second number to append to the first
 * \return both numbers concatenated
 */
unsigned long long m_concat_numbers(unsigned long long first, unsigned long long second){
    unsigned long long pow = 10;

    while(second >= pow) pow *= 10;

    return (first * pow) + second;
}


/**
 * See header
 */
unsigned long long m_evaluate_line(char* line){

    int array_length = m_get_array_length_from_line(line);

    unsigned long long num_array[array_length];

    m_fill_array(line, num_array);

    // don't count the result (first number)
    // and there is one less space then numbers
    int width = array_length - 2;
    int height = (int) pow(3.0, (double) width);

    char op_array[height * width];

    m_create_operand_array(op_array, height, width);

    unsigned long long result;

    for(int y = 0; y < height; y++){
        
        result = num_array[1];
        // printf("%lld = %lld ", num_array[0], num_array[1]);

        for(int x = 0; x < width; x++){
            
            char op = op_array[(y * width) + x];

            // printf("%c %lld ", op, num_array[x+2]);

            if(op == '+'){
                result += num_array[x+2];
            }
            else if(op == '*'){
                result *= num_array[x+2];
            }
            else{
                result = m_concat_numbers(result, num_array[x+2]);
            }
        }
        
        // printf("\n");

        if(num_array[0] == result){
            // printf("------\n");
            return result;

        }

    }

    return 0;
}



/*

max unsigned long long:
18446744073709551615

*/
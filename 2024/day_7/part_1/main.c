
#include <stdio.h>
#include <stdlib.h>

#include "mathe.h"

int main(int argc, char* argv[]){

    char* filename = argv[1];

    FILE* file = fopen(filename, "r");

    if(file == NULL){
        printf("Cannot open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char* line = NULL;
    size_t len = 0;

    int sum = 0;

    int counter = 0;

    while(getline(&line, &len, file) != -1 && counter < 1){

        sum += m_evaluate_line(line);

        counter ++;
    }


    printf("sum %d\n", sum);
    return 0;
}
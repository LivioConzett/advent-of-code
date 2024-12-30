
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

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

    unsigned long long sum = 0;

    while(getline(&line, &len, file) != -1){

        unsigned long long num = m_evaluate_line(line);
        if(num > 0){
            printf("%s", line);
            sum += num;
        }

    }

    printf("sum %lld\n", sum);
    return 0;
}
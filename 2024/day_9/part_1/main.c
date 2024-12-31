
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * \brief get the size of the memory that will be needed
 * \param filename name of the file to get input from
 * \return the size of the memory needed
 */
int get_mem_size(char* filename){

    FILE* file;

    file = fopen(filename, "r");

    if(file == NULL){
        printf("cannot open file!\n");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    size_t len = 0;
    char* line = NULL;

    while((getline(&line, &len, file)) != -1){

        for(int i = 0; i < strlen(line); i++){
            char num[2];
            num[0] = line[i];
            num[1] = 0;
            count += atoi(num);
        }
    }


    fclose(file);

    return count;
}

/**
 * \brief print the memory
 * \param mem memory to print 
 * \param size size of the memory
 */
void print_mem(int* mem, int size){

    for(int i = 0; i < size; i++){
        if(mem[i] == -1) printf(". ");
        else printf("%d ", mem[i]);
    }
    printf("\n");
}


/**
 * \brief fill the memory according to the file
 * \param filename name of the file
 * \param mem memory to write to
 * \param size size of the memory
 */
void fill_memory(char* filename, int* mem, int size){
    
    
    FILE* file;

    file = fopen(filename, "r");

    if(file == NULL){
        printf("cannot open file!\n");
        exit(EXIT_FAILURE);
    }

    size_t len = 0;
    char* line = NULL;

    int block_index = 0;
    int mem_index = 0;

    while((getline(&line, &len, file)) != -1){

        int length = strlen(line);

        for(int i = 0; i < length; i++){
            char num[2];
            num[0] = line[i];
            num[1] = 0;
            int number = atoi(num);

            for(int ii = 0; ii < number; ii++){
                
                if(i % 2 == 0) mem[mem_index] = block_index;
                else mem[mem_index] = -1;


                mem_index ++;
                if(mem_index > size){
                    fclose(file);
                    return;
                };
            }

            if(i % 2 == 0) block_index++;

        }
    }

    fclose(file);
}


/**
 * \brief defrag the memory
 * \param mem memory to defrag
 * \param size size of the memory
 */
void defrag(int* mem, int size){

    // set up the left and right indexes
    int l = 0;
    int r = size - 1;

    while(l != r){

        while(mem[l] != -1){
            l++;
            if(l == r) return;
        }

        while(mem[r] == -1){
            r--;
            if(l == r) return;
        }

        mem[l] = mem[r];
        mem[r] = -1;

    }
}

/**
 * \brief calculate the checksum of the memory
 * \param mem memory
 * \param size size of the memory
 */
unsigned long long calculate_checksum(int* mem, int size){

    unsigned long long sum = 0;

    for(int i = 0; i < size; i++){
        
        if(mem[i] == -1) break;

        sum += mem[i] * i;
        
    }

    return sum;
}


/**
 * Main entry point
 */
int main(int argc, char* argv[]){

    char* filename = argv[1];

    // get the length of the memory needed
    int mem_length = get_mem_size(filename);

    printf("%d\n", mem_length);
    
    // create the memory
    int mem[mem_length];

    // fill the memory
    fill_memory(filename, mem, mem_length);

    print_mem(mem, mem_length);

    defrag(mem, mem_length);

    print_mem(mem, mem_length);

    unsigned long long checksum = calculate_checksum(mem, mem_length);

    printf("sum %llu\n", checksum);

    return 0;
}
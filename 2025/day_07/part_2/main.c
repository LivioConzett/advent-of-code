/**
 * gcc -std=c99 -Wall -Werror main.c -lm
 */

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef struct {
    int16_t x;
    int16_t y;
} vector_t;

typedef struct {
    int32_t from;
    int32_t to;
} edge_t;

typedef struct {
    int32_t array[2];
    uint8_t length;
} node_t;



/**
 * \brief get the size of the array that needs to be allocated
 * \param filename nae of the file
 * \return a vector with the width and hight
 */
vector_t get_array_size(const char* filename){

    FILE* file_ptr;
    file_ptr = fopen(filename, "r");

    if(file_ptr == NULL){
        printf("Error: File %s does not exist\n", filename);
        exit(EXIT_FAILURE);
    }


    size_t read = 0;
    char* line = NULL;
    size_t len = 0;

    int line_number = 0;
    int columns = 0;

    while(read != -1){
        read = getline(&line, &len, file_ptr);
        if(read == -1) break;

        columns = 0;

        while(line[columns] != '\n'){

            columns++;
        }

        line_number++;
    }

    free(line);

    return (vector_t){line_number, columns};
}


/**
 * \brief fill the array with the characters
 * \param array array to put characters into
 * \param size size of the array
 * \param filename name of the file
 */
void fill_array(char array[], vector_t size, char* filename){


    FILE* file_ptr;
    file_ptr = fopen(filename, "r");

    if(file_ptr == NULL){
        printf("Error: File %s does not exist\n", filename);
        exit(EXIT_FAILURE);
    }


    size_t read = 0;
    char* line = NULL;
    size_t len = 0;

    int char_index = 0;

    for(int i = 0; i < size.x; i++){
        read = getline(&line, &len, file_ptr);
        if(read == -1) break;

        char_index = 0;

        while(line[char_index] != '\n'){
            
            array[(i * size.y) + char_index] = line[char_index];

            char_index++;
        }
    }

    free(line);
}


/**
 * \brief prints out the array
 * \param array array to print
 * \param size size of the array
 */
void print_array(char array[], vector_t size){

    for(int row = 0; row < size.x; row++){
        for(int col = 0; col < size.y; col++){
            printf("%c", array[(row * size.y) + col]);
        }
        printf("\n");
    }
}


/**
 * \brief go through a row in the array
 * \param array array of the characters
 * \param size size of the array
 * \param row we are on
 * \return the number of '^' with a '|' above them in that row
 */
uint16_t go_through_row(char array[], vector_t size, uint16_t row){

    uint16_t count = 0;

    if(row == 0) return 0;

    for(int i = 0; i < size.y; i++){
        // if the character 1 row above is a '|'
        if(array[((row - 1) * size.y) + i] == '|'){

            // if the current character is a '^'
            if(array[(row * size.y) + i] == '^'){
                count++;

                if(i > 0) array[(row * size.y) + i - 1] = '|';
                if(i < size.y - 1) array[(row * size.y) + i + 1] = '|';
            }
            else{
                array[(row * size.y) + i] = '|';
            }
        }
    }

    return count;
}


/**
 * \brief find the next node in the column
 * \param array array with the characters
 * \param size size of the array
 * \param start from where to start looking for
 * \return the coordinates of a found node {-1,-1} if nothing found
 */
vector_t find_next_node_in_col(char array[], vector_t size, vector_t start){

    // check size is within the parameters
    if(start.x < 0 || start.x > size.x || start.y < 0 || start.y > size.y){
        return (vector_t) {-1,-1};
    }

    // find the next node in the column
    for(int row = start.x + 1; row < size.x; row++){
        if(array[(row * size.y) + start.y] == '^'){
            return (vector_t) {row, start.y};
        }
    }

    return (vector_t) {-1,-1};
}


/**
 * \brief number the nodes sequentially
 * \param old_array the old array with the names of the edges
 * \param size size of the array
 * \param new_array new_array to place the new numbers into
 * \param dest_nodes destination nodes array
 */
void clean_edge_array(edge_t old_array[], uint32_t size, edge_t new_array[], int32_t dest_nodes[]){

    uint16_t counter = 0;

    for(int i = 0; i < size; i++){

        // number to search for
        uint32_t search = old_array[i].from;

        if(search > 0){

            for(int ii = 0; ii < size; ii++){

                if(old_array[ii].from == search) {
                    new_array[ii].from = counter;
                    old_array[ii].from = 0;
                }
                if(old_array[ii].to == search){
                    new_array[ii].to = counter;
                    old_array[ii].to = 0;
                } 
            }

            counter++;
        }

        search = old_array[i].to;
        
        if(search > 0){

            for(int ii = 0; ii < size; ii++){

                if(old_array[ii].from == search) {
                    new_array[ii].from = counter;
                    old_array[ii].from = 0;
                }
                if(old_array[ii].to == search){
                    new_array[ii].to = counter;
                    old_array[ii].to = 0;
                } 
            }

            for(int ii = 0; ii < size; ii++){
                
                if(dest_nodes[ii] < 0) break;

                if(dest_nodes[ii] == search){
                    dest_nodes[ii] = counter;
                }
            }

            counter++;
        }
    }
}



/**
 * \brief find the number of paths to a certain destination
 * \param size size of the edge array
 * \param edges array of the edges
 * \param source source node
 * \param destination destination node
 * \param paths the array to place the paths into
 * \return the amount of paths from source to destination
 */
uint16_t find_paths(uint16_t edge_array_size, edge_t edges[], uint16_t source, uint16_t destination, int16_t paths[]){

    uint16_t amount_of_paths = 0;
    uint16_t paths_index = 0;

    // create the graph
    node_t graph[edge_array_size];

    // init the graph
    for(int i = 0; i < edge_array_size; i++){
        graph[i].length = 0;
    }

    // fill the graph
    for(int i = 0; i < edge_array_size; i++){
        graph[edges[i].from].array[graph[edges[i].from].length] = edges[i].to;
        graph[edges[i].from].length++;
    }


    printf("here\n");
    
    int16_t queue[edge_array_size][150];
    int16_t queue_lengths[edge_array_size];
    uint16_t queue_length = 0;


    // zero out everything
    for(int i = 0; i < edge_array_size; i++){
        queue_lengths[i] = 0;
    }

    // add the first path
    queue[0][0] = source;
    queue_lengths[0]++;
    queue_length++;


    while(queue_length > 0){

        // preform a shift() on the queue
        int16_t path[edge_array_size];
        int16_t path_length = queue_lengths[queue_length - 1];

        for(int i = 0; i < path_length; i++){
            path[i] = queue[queue_length - 1][i];
        }

        queue_lengths[queue_length - 1] = 0;
        queue_length--;


        // get the last node in the path array
        int32_t current = path[path_length - 1];

        // we reached our destination
        if(current == destination){
            amount_of_paths++;

            for(int i = 0; i < path_length; i++){
                paths[(paths_index * edge_array_size) + i] = path[i];
            }

            paths_index++;
        }


        for(int i = 0; i < graph[current].length; i++){
            
            // add the path to the queue
            for(int ii = 0; ii < path_length; ii++){
                queue[queue_length][ii] = path[ii];
                queue_lengths[queue_length]++;
            }

            // add the nodes in the graph to the queue
            queue[queue_length][queue_lengths[queue_length]] = graph[current].array[i];
            queue_lengths[queue_length]++;
            queue_length++;
        }

        // printf("%d\n", queue_length);
    }

    return amount_of_paths;
}






/**
 * \brief main entry point
 */
int main(int argc, char* argv[]){

    // make sure there are enough parameters
    if(argc < 2){
        printf("Error: No file given!\n");
        exit(EXIT_FAILURE);
    }

    char* filename = argv[1];

    vector_t array_size = get_array_size(filename);
    
    // array for the characters
    char array[array_size.x * array_size.y];

    fill_array(array, array_size, filename);

    // create the array for the edges
    // way too big, but better than too small
    edge_t edges[array_size.x * array_size.y];

    // create the array for the last nodes
    int32_t dest_nodes[array_size.y];
    uint32_t start_node = 0;


    // find the S in the first line
    for(int i = 0; i < array_size.y; i++){
        if(array[i] == 'S'){
            array[i] = '|';
            break;
        }
    }

    // fill the paths
    for(int i = 0; i < array_size.x; i++){
        (void) go_through_row(array, array_size, i);
    }


    uint16_t dest_nodes_index = 0;

    // fill in the last line with the nodes, so that the node finder will work
    for(int i = 0; i < array_size.y; i++){
        if(array[((array_size.x - 1) * array_size.y) + i] == '|'){
            array[((array_size.x - 1) * array_size.y) + i] = '^';

            dest_nodes[dest_nodes_index] = ((array_size.x - 1) * 1000) + i;

            dest_nodes_index++;
        }
    }

    //print_array(array, array_size);
    
    // cap off the dest_nodes array
    dest_nodes[dest_nodes_index] = -1;


    uint32_t total = 0;

    uint32_t edges_index = 0;

    for(int row = 0; row < array_size.x; row++){
        for(int col = 0; col < array_size.y; col++){

            // look for the '^' character
            if(array[(row * array_size.y) + col] == '^'){

                vector_t right_side = find_next_node_in_col(array, array_size, (vector_t){row,col-1});
                vector_t left_side = find_next_node_in_col(array, array_size, (vector_t){row,col+1});

                if(right_side.x > -1){
                    edges[edges_index] = (edge_t){(row*1000) + col,(right_side.x * 1000) + right_side.y};
                    edges_index++;
                }
                
                if(left_side.x > -1){
                    edges[edges_index] = (edge_t){(row*1000) + col,(left_side.x * 1000) + left_side.y};
                    edges_index++;
                }

            }
        }
    }

    // cap off the edges array
    edges[edges_index] = (edge_t){-1,-1};


    

    uint32_t edge_array_length = 0;

    // get the length of the edges array
    for(int i = 0; i < array_size.x * array_size.y; i++){
        if(edges[i].from == -1){
            edge_array_length = i;
            break;
        }
    }

    // create the new edges array
    edge_t new_edges[edge_array_length];

    

    // clean the edges array
    // turn the node names from the big numbers to smaller numbers
    clean_edge_array(edges, edge_array_length, new_edges, dest_nodes);
    

    // for(int i = 0; i < array_size.x * array_size.y; i++){
    //     if(new_edges[i].from < 0) break;
    //     printf("%d : %d\n", new_edges[i].from, new_edges[i].to);
    // }

    
    int16_t paths[edge_array_length * array_size.y];


    // empty the paths array
    for(int i = 0; i < edge_array_length * array_size.y; i++){
        paths[i] = -1;
    }

    printf("len: %d\n", edge_array_length);


    for(int i = 0; i < array_size.y; i++){
        if(dest_nodes[i] == -1) break;
    
        // find the number of paths from the source to the destination
        total += find_paths(edge_array_length, new_edges, start_node, dest_nodes[i], paths);
    
        // print the paths array
        for(int row = 0; row < edge_array_length; row++){
            
            if(paths[(row * edge_array_length)] == -1) break;

            for(int col = 0; col < edge_array_length; col++){
                if(paths[(row * edge_array_length) + col] == -1) break;
                printf("%d ", paths[(row * edge_array_length) + col]);
            }
            printf("\n\n");
        }
    }



    // for(int i = 0; i < edge_array_length; i++){
    //     printf("%d : %d\n", new_edges[i].from, new_edges[i].to);
    // }

    // for(int i = 0; i < array_size.y; i++){
    //     if(dest_nodes[i] < 0) break;
    //     printf("%d ", dest_nodes[i]);
    // }
    // printf("\n");


    printf("total: %d\n", total);

    return 0;
}


// https://www.geeksforgeeks.org/dsa/find-paths-given-source-destination/



// create a graph of the nodes



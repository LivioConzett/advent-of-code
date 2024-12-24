
#include <stdio.h>
#include <stdlib.h>

// enum with the states of the state machine
enum State{
    START,
    M_STATE,
    U_STATE,
    L_STATE,
    LB_STATE,
    FIRST_MINUS_STATE,
    FIRST_NUM_STATE,
    COMMA_STATE,
    SECOND_MINUS_STATE,
    SECOND_NUM_STATE,
    RB_STATE
};

// current state
enum State current_state = START;



/**
 * \brief Handel the start state
 * \param c the character that was read
 */
void start_function(char c){
    if(c == 'm') current_state = M_STATE;
}

/**
 * \brief Handel the m state
 * \param c character that was read
 */
void m_function(char c){
    if(c == 'u') current_state = U_STATE;
    else current_state = START;
}




/**
 * Main Entry Point
 */
int main(int argc, char* argv[]){

    char* filename = argv[1];


    // opent the file
    FILE* file_ptr;
    file_ptr = fopen(filename,"r");

    int line_counter = 0;

    // make sure the file could be opend
    if (file_ptr == NULL){
        printf("Cannot open file %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char c;
    
    // go through the file char by char
    while((c = fgetc(file_ptr)) != EOF){

        // create the two strings to save the number to
        char first_num[100];
        int first_num_counter = 0;

        char second_num[100];
        int second_num_counter = 0;


        switch(current_state){

            case START:
                start_function(c);
                break;
            case M_STATE:
                m_function(c);
                break;
            case U_STATE:
                break;
            case L_STATE:
                break;
            case LB_STATE:
                break;
            case FIRST_MINUS_STATE:
                break;
            case FIRST_NUM_STATE:
                break;
            case COMMA_STATE:
                break;
            case SECOND_MINUS_STATE:
                break;
            case SECOND_NUM_STATE:
                break;
            case RB_STATE:
                break;
            default:

        }

    }


    fclose(file_ptr);

    return 0;
}

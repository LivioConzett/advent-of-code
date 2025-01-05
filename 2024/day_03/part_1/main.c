
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

// create the two strings to save the number to
char first_num[100];
int first_num_counter = 0;

char second_num[100];
int second_num_counter = 0;

int total_sum = 0;

/**
 * \brief check if a character is a number from 0 - 9
 * \param c character to check
 * \return 0 if character is not a number, 1 if it is
 */
int is_a_number(char c){

    int num = (int) c;

    if(num >= 48 && num <= 57) return 1;

    return 0;
}

/**
 * \brief add a character to the end of the first number string
 * \param c character to append
 */
void append_to_first_number(char c){
    
    first_num[first_num_counter] = c;
    first_num_counter++;
}

/**
 * \brief reset the first and second number
 */
void reset_numbers(){
    // reset the first and second number
    first_num[0] = 0;
    first_num_counter = 0;
    second_num[0] = 0;
    second_num_counter = 0;
}

/**
 * \brief add a character to the end of the second number string
 * \param c character to append
 */
void append_to_second_number(char c){
    
    second_num[second_num_counter] = c;
    second_num_counter++;
}


/**
 * \brief Handel the start state
 * \param c the character that was read
 */
void start_function(char c){

    reset_numbers();

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
 * \brief Handel the u state
 * \param c character that was read
 */
void u_function(char c){
    if(c == 'l') current_state = L_STATE;
    else current_state = START;
}

/**
 * \brief Handel the l state
 * \param c character that was read
 */
void l_function(char c){
    if(c == '(') current_state = LB_STATE;
    else current_state = START;
}

/**
 * \brief Handel the ( state
 * \param c character that was read
 */
void lb_function(char c){

    if(c == '-'){
        current_state = FIRST_MINUS_STATE;
        append_to_first_number(c);
        return;
    }

    if(is_a_number(c)){
        current_state = FIRST_NUM_STATE;
        append_to_first_number(c);
        return;
    }

    current_state = START;

}

/**
 * \brief Handel the first minus state
 * \param c charater that was read
 */
void first_minus_function(char c){
    if(is_a_number(c)){
        current_state = FIRST_NUM_STATE;
        append_to_first_number(c);
        return;
    }

    current_state = START;
}

/**
 * \brief Handel the first number state
 * \param c character that was read
 */
void first_number_function(char c){
    
    if(c == ','){
        current_state = COMMA_STATE;
        return;
    }
    
    if(is_a_number(c)){
        append_to_first_number(c);
        return;
    }

    current_state = START;
}

/**
 * \brief Handel the comma state
 * \param c charater that was read
 */
void comma_function(char c){

    if(c == '-'){
        current_state = SECOND_MINUS_STATE;
        append_to_second_number(c);
        return;
    }

    if(is_a_number(c)){
        current_state = SECOND_NUM_STATE;
        append_to_second_number(c);
        return;
    }

    current_state = START;
}

/**
 * \brief Handel the second minus state
 * \param c character that was read
 */
void second_minus_function(char c){
    
    if(is_a_number(c)){
        current_state = SECOND_NUM_STATE;
        append_to_second_number(c);
        return;
    }

    current_state = START;
}

/**
 * \brief Handel the second number state
 * \param c character that was read
 */
void second_number_function(char c){
    
    if(c == ')'){
        current_state = RB_STATE;
        return;
    }
    

    if(is_a_number(c)){
        append_to_second_number(c);
        return;
    }

    current_state = START;
}

/**
 * \brief handel the ) state
 * \param c character that was read
 */
void rb_function(char c){

    // terminate the string
    first_num[first_num_counter] = 0;
    second_num[second_num_counter] = 0;

    int first = atoi(first_num);
    int second = atoi(second_num);

    total_sum += first * second;

    reset_numbers();

    if(c == 'm') current_state = M_STATE;
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

        switch(current_state){

            case START:
                // printf("- start -\n");
                start_function(c);
                break;
            case M_STATE:
                // printf("- M -\n");
                m_function(c);
                break;
            case U_STATE:
                // printf("- U -\n");
                u_function(c);
                break;
            case L_STATE:
                // printf("- L -\n");
                l_function(c);
                break;
            case LB_STATE:
                // printf("- ( -\n");
                lb_function(c);
                break;
            case FIRST_MINUS_STATE:
                // printf("- 1- -\n");
                first_minus_function(c);
                break;
            case FIRST_NUM_STATE:
                // printf("- 1 num -\n");
                first_number_function(c);
                break;
            case COMMA_STATE:
                // printf("- , -\n");
                comma_function(c);
                break;
            case SECOND_MINUS_STATE:
                // printf("- 2- -\n");
                second_minus_function(c);
                break;
            case SECOND_NUM_STATE:
                // printf("- 2 num -\n");
                second_number_function(c);
                break;
            case RB_STATE:
                // printf("- ) -\n");
                rb_function(c);
                break;
            default:

        }

    }


    fclose(file_ptr);

    printf("total: %d\n", total_sum);

    return 0;
}

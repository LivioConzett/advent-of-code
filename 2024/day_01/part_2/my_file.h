
#ifndef MY_FILE
#define MY_FILE


/**
 * \brief Get the amount of lines in a file
 * \param filename string of the filename to open
 * \return amount of lines in the file
 */
int amount_of_lines(char* filename);


/**
 * \brief get the number from the line
 * \param line the string to get the number from
 * \param column which number to get
 * \return the number at the column in the line
 */
int get_number_from_line(char* line, int column);


/**
 * \brief read a certain column of a file into the given array
 * \param array array to writ the values into
 * \param length length of the array
 * \param column which column to read into the array. starts at 0
 * \param filename string of the file name
 */
void read_file_to_array(int array[], int length, int column, char* filename);



#endif
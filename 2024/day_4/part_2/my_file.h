
#ifndef MY_FILE
#define MY_FILE



/**
 * \brief Get the amount of lines in a file
 * \param filename string of the filename to open
 * \return amount of lines in the file
 */
int amount_of_lines(char* filename);

/**
 * \brief get the length of the max line
 * \param filename string of the filname to open
 * \return max amount of columns
 */
int amount_of_columns(char* filename);

/**
 * \brief read a certain column of a file into the given array
 * \param array array to writ the values into
 * \param width width of the array
 * \param height height of the array
 * \param filename string of the file name
 */
void read_file_to_array(char* array, int width, int height, char* filename);



#endif
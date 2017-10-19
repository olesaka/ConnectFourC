#ifndef	IO_FILE	
#define	IO_FILE

/*	
	Interface file that contains functions that
	the program must implement
*/

// reads a given file into an array created using buffer
int read_file(char* filename, char **buffer );

// writes the contents of the array buffer to the given file
int write_file(char* filename, char *buffer, int size);

#endif
#include "file_io.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>


/*  Function takes a filename and an array of chars and reads each character 
 	of the file into the array
 	The code for opening the file was provided by instructor Ira Woodring
 	@param filename a pointer to the name of a file
 	@param buffer a pointer to a pointer used to create an array
  	@return the size of the file
*/
int read_file(char* filename, char** buffer ){

	// finds the size of the file and allocates
	// an appropiate amount of memory.
	struct stat st;
  	stat(filename, &st);
  	int size = st.st_size;
  	*buffer = malloc(size * sizeof(char));

// check to see if malloc was executed correctly
  	if(*buffer==NULL){
  		fprintf(stderr, "Memory was not allocated correctly.");
  	}
  	
 // opens the file to read from and checks for errors
	FILE *file;
	file = fopen(filename, "r");
	if(file==NULL){
		fprintf( stderr, "Did not read file or it doesn't exist." );
		return 0;
	}

// reads the file and assigns each character 
// as an array element
	int num = fread(*buffer, size, 1, file);
	fclose(file);


	return size;
}



/*
	Function writes to a given file the contents of the 
	array contained in buffer.
	@param filename a pointer to the name of a file
	@param buffer a pointer to the first element in an arary
	@param size the size of the array buffer
	@return the size of the file written to
*/
int write_file(char* filename, char *buffer, int size){

// opens the file to write to and checks for errors
	FILE *file;
	file = fopen(filename, "w");
	if(file==NULL){
		fprintf( stderr, "Did not read file correctly" );
	}

// write  the contents of the array into the file
	int num = fwrite(buffer, size, 1, file);

	fclose(file);

	// gets the size of the write file and checks
	// to make sure that it's the right length
	struct stat st;
  	stat(filename, &st);
  	int s = st.st_size;

	return s;
}
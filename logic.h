#ifndef LOGIC
#define LOGIC
#include "arguments.h"

/*
	Interface file contains all of the necessary functions 
	that logic.c must implements
*/

//Function takes the two dimensional array representing the 
//board, a height, and a width of the game board
//and prints it out using a nested for loop
void print_board(char**board, int height, int width);


//Function takes the two dimensional array of the game board, 
//an integer representing the column in which to place
//a chip, a width, a height, and a character representing a piece.
//Error handling will be implemented to account for
//an already full row or invalid row
int add_chip(char**board, int height, int width, int column, char piece);

//Fucntion takes a two dimensional array of chars, a height, and a width and 
// creates a blank game board for a new game
void new_board(char**board, int height, int width);

//Function checks the board to see if there is a winner
int check_for_winner(char**board, int height, int width, int connect, char piece);

// creates a formatted char array that will be used to save the game state
void format_save(char*buffer, char**board, int* board_dim, int height, int width, int connect, int player);

// sets all of the game parameters and the board from a given file array
int format_load(char*buffer, int* height, int*width, int* connect, int*player);

// creates the dimensions of the board depending on the input
// from the user
void setup_board(struct arguments arg, int *height, int *width, int *connect);

// allocate memory for the dimensions of the board
void malloc_board(char *** board, int height, int width);

// allocate memory for the buffer which will write to a file
int malloc_buffer(char** buffer, int* board_dim, int height, int width);

// prints the current player to the screen
void print_player(int player);

// switches the player value
void switch_player(int *player);

// creates an array of integers that describe how long the game attributes
// are for mallocing the saving buffer size
void board_dim_array(int board_dim[], int height, int width, int connect);

// returns the number of digits in a given number
int find_size(int number);

// returns this size of the string
int string_size(char* str);

// set every element of the given char array to null
void set_null(char* str, int size);

// mallocs a desired amount of memory for a string of chars
void malloc_string(char** str, int size);

// places the conents of one string into another of correct length
void string_to_string(char* str1, char* str2, int size);

// function places the pieces in buffer in the game board
void buffer_to_board(char*buffer, char**board, int height, int width, int buf_index);

// prints the commands for the game to the screen for the user to see
void print_commands(); 

#endif
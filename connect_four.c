#include <stdio.h>
#include "file_io.h"
#include "logic.h"
#include "test.h"
#include "arguments.h"
#include <stdlib.h>


/*
	Main function allows users to play a game of connect four to their dimensions
	Game functions allow saving, loading, new game
	@author Andrew Olesak
	@version February 25, 2017
	The use of this code is open source and designed for the public domain
	Any issues with this code please contact olesaka@mail.gvsu.edu
*/
int main(int argc, char** argv){
	/*
		test all test cases in the test file
		it takes rouphly ten seconds for all cases to run successfully
		if all are successfull, it will display that all tests passed
		uncomment the line below to run the test cases
	 */
	// test_all();

	// create instance variables for the game parameters

	// to dimensional array for the board
	char** board;
	// board height, width, and number of connections for a win defaults
	int height = 7;
	int width = 7;
	int connect = 4;
	// current player, used as an index
	int player = 0;
	// create a buffer pointer incase the users decide to load or save
	char* buffer;
	// buffer index to keep track of load/save data
	int buf_index = 0;
	// pieces for each player, indexed by current player
	char piece[2] = {'X', 'O'};

	// call the parser and create an arguments struct to hold the data
	struct arguments args = setup(argc, argv);

	// check if the user entered a load file
	if(args.load_file==NULL){
		// gets the data from the struct and places it accordingly
		setup_board(args, &height, &width, &connect);
		// mallocs the appropriate size for the board
		malloc_board(&board, height, width);
		// resets the board to an empty board
		new_board(board, height, width);

	}else{
		// reads the data from the file and places it in a buffer
		read_file(args.load_file, &buffer);
		// sets the parameters of the game board from the first part of the buffer
		buf_index = format_load(buffer, &height, &width, &connect, &player);
		// mallocs the appropriate size for the board from the load file dimesions
		malloc_board(&board, height, width);
		// places the game pieces into the newly created board
		buffer_to_board(buffer, board, height, width, buf_index);
	}



	// introduction
	printf("\n\n   Welcome to Connect Four!\n\n");

	// print the commands for the game to the screen
	print_commands();

	// display the board to the screen to start
	print_board(board, height, width);
	// create an input char array for user input
	char input[10];
	// set char array to null to avoid corrupt previous data
	set_null(input, 10);
	// print the current player's turn
	print_player(player);
	// asks for and accepts a column or game command
	printf("Please enter a valid column:\n");
	fgets(input, sizeof(input), stdin);

	// loop continues to allow the users to play the game unless
	// they enter 'q' to quit, then it exits and the game returns
	while(input[0]!='q'){

		// prints the commands to the screen again if the user types 'c'
		if(input[0]=='c'){
			// print commands and then the board, followed by the player
			print_commands();
			print_board(board, height, width);
			print_player(player);
			// asks for input for new move
			set_null(input, 10);
			printf("Please enter a valid column:\n");
			fgets(input, sizeof(input), stdin);
			continue;

		// allows the users to save the current game to a file if type 's'
		}else if(input[0]=='s'){
			// asks for a filename
			char name[200] = "";
			printf("Please enter the name of the file you would like to save to:\n");
			fgets(name, sizeof(name), stdin);
			// finds the length of the filename char array
			int size = string_size(name);
			// create a char array
			char *filename;
			// dynamically allocate the correct amount of memory for filename
			malloc_string(&filename, size+1);
			// copy contents to filename
			string_to_string(filename, name, size);
			// end with a null terminator
			filename[size] = '\0';
			int num[3];
			// get game parameters sizes
			board_dim_array(num, height, width, connect);
			// malloc the buffer
			int buf_size = malloc_buffer(&buffer, num, height, width);
			// places everything in the buffer in an organized fashion
			format_save(buffer, board, num, height, width, connect, player);
			// writes the data from the buffer the correct file
			write_file(filename, buffer, buf_size);
			// free dynamic memory
			free(filename);
			free(buffer);
			// prints the board and asks for next turn input
			set_null(input, 10);
			print_board(board, height, width);
			print_player(player);
			printf("Please enter a valid column:\n");
			fgets(input, sizeof(input), stdin);
			continue;
		
		// allows users to load a previously saved game from a file if type 'l'
		}else if(input[0]=='l'){
			// asks for the name of the file to load from
			char name[200] = "";
			printf("Please enter the name of the file you would like to load from:\n");
			fgets(name, sizeof(name), stdin);
			// finds length of string of chars given
			int size = string_size(name);
			// create filename char array
			char *filename;
			// dynamically allocate the array to the correct size
			malloc_string(&filename, size+1);
			// place the contents into filename
			string_to_string(filename, name, size);
			// end with a null terminator
			filename[size] = '\0';
			// reads the data from the given file and places it in a buffer
			read_file(filename, &buffer);
			// free dynamic memory
			free(filename);
			// set the game parameters and get the index of the first game
			// chip in the buffer
			buf_index = format_load(buffer, &height, &width, &connect, &player);
			// malloc the new board
			malloc_board(&board, height, width);
			// get the game pieces from buffer and place in the board
			buffer_to_board(buffer, board, height, width, buf_index);
			// free buffer
			free(buffer);

			// print board for next turn
			print_board(board, height, width);
			print_player(player);
			set_null(input, 10);
			printf("Please enter a valid column:\n");
			fgets(input, sizeof(input), stdin);
			continue;
		
		// resets the board and creates a new game with the same dimensions
		// if users type 'n'
		}else if(input[0]=='n'){
			printf("\n***New Game***\n");
			// resets the board to empty
			new_board(board, height, width);
			// set to first player
			player = 0;
			// print board and ask for first move
			print_board(board, height, width);
			print_player(player);
			printf("Please enter a valid column:\n");
			set_null(input, 10);
			fgets(input, sizeof(input), stdin);
			continue;
		
		// if none of the above are selected, execute a normal turn 
		// and look for a column as input
		}else{
			// convert input to integer and subtract one so it is indexable
			int column = atoi(input)-1;
			// check whether a chip can be added there
			// if so, add it
			// iif not, continue to loop conditional to check for other commands
			if(add_chip(board, height, width, column, piece[player])==0){
				printf("Please enter a valid column:\n");
				set_null(input, 10);
				fgets(input, sizeof(input), stdin);
				continue;

			}

			// check for a win after every chip is placed in the game board
			// print the appropriate message depending on who won
			if(check_for_winner(board, height, width, connect, piece[player])==1){
				print_board(board, height, width);
				if(player==0){
					printf("***Player one has won the game!***\n");
				}else{
					printf("***Player two has won the game!***\n");
				}

				// after win, allow for new game, quit, or load previous game
				printf("Please type 'n' for a new game, 'q' to quit, or 'l' to load a game\n");
				set_null(input, 10);
				fgets(input, sizeof(input), stdin);
				// Continue to ask for input until one of the three commands are entered
				while(input[0]!='q' && input[0]!='n' && input[0]!='l'){
					printf("Sorry, please type 'n' for a new game, 'q' to quit, or 'l' to load a game\n");
					set_null(input, 10);
					fgets(input, sizeof(input), stdin);
				}
				continue;
			}

		}

		// after move is complete, switch the player, display the board
		// and ask for the next column as input
		switch_player(&player);
		print_board(board, height, width);
		print_player(player);
		set_null(input, 10);
		printf("Please enter a valid column:\n");
		fgets(input, sizeof(input), stdin);
	}



	// free all malloced memory and return to exit game
	free(board);
	return 0;
}
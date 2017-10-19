#include "logic.h"
#include <stdlib.h>
#include <stdio.h>

/*
	Function prints the board in an organized and readable fashion
	@param board, the two dimensional array of the game board
	@param height the height of the game board
	@param width, the width of the game board
	@return void
*/
void print_board(char**board, int height, int width){

	// print for every increment by 10 the correct number above the 
	// column so the user knows the base of the number
	// for a large board
	printf("\n ");
	int tens = 1;
	for(int i=0; i<width; ++i){
		if((i+1)%10==0){
			printf(" %d", tens);
			++tens;
		}else{
			printf("  ");
		}
	}
	printf("\n ");
	// print a line of column numbers to make selections easier
	for(int i=0; i<width; ++i){
		printf(" %d", (i+1)%10);
	}

	// print out each character in the array and a new line when
	// the end of a row is reached
	printf("\n");
	for(int i=0; i<height; ++i){
		printf(" ");
		for(int j=0; j<width; ++j){
			printf(" %c", board[i][j]);
		}
		printf("\n");
	}
	return;
}

/*
	Function places a piece in the board if it is a valid move
	@param board, the two dimensional array of the game board
	@param height the height of the game board
	@param width, the width of the game board
	@param column, the column in which the piece will be placed
	@param piece, the piece that will be placed in the board
	@return 1 for true meaning that the chip was placed successfully and 0
	for false meaning the chip was not allowed to be placed there
*/
int add_chip(char**board, int height, int width, int column, char piece){

	// check to make sure that the given column is within the 
	// dimensions of the board, if so return false
	if(column<0 || column>=width){
		printf("Sorry, please enter a number in the correct range\n");
		return 0;
	}

	// check the board from the bottom up and place the chip
	// when an open spot appears, then return true
	for(int i=height-1; i>=0; --i){
		if(board[i][column]=='*'){
			board[i][column]=piece;
			return 1;
		}
	}

	// there were no empty spots in the board, so let the player know, return false
	printf("Sorry, that column is already full\n");
	return 0;

}

/*
	Function creates a new empty game board
	@param board, the two dimensional array of the game board
	@param height the height of the game board
	@param width, the width of the game board
	@return void
*/
void new_board(char**board, int height, int width){

	// loop through every spot on the board and set 
	// them to the same blank character
	for(int i=0; i<height; ++i){
		for(int j=0; j<width; ++j){
			board[i][j] = '*';
		}
	}
	return;
}

/*
	Function checks the board to see if there is a winner
	@param board, the two dimensional array of the game board
	@param height the height of the game board
	@param width, the width of the game board
	@param connect, the number of required connections for a win
	@param piece, the piece of the player who is being checked for a win
	@return true for a win, otherwise false
*/
int check_for_winner(char**board, int height, int width, int connect, char piece){

	// loop through every spot on the board to check for the desired piece
	for(int i=0; i<height; ++i){
		for(int j=0; j<width; ++j){

			// check to see if the spot contains the given piece
			if(board[i][j]==piece){
				
				// variable keeps track of the number of pieces found in a row
				int win_count = 1;
				// check for vertical win and increment win_count every
				// time a new piece of the same kind is found
				// if no win, reset win_count
				if(i+connect<=height){
					for(int row=i+1; row<i+connect; ++row){
						if(board[row][j]==piece){
							++win_count;
						}else{
							win_count = 1;
							break;
						}
					}
				}

				// check for winner for vertical win, if so return true
				if(win_count==connect){
					return 1;
				}

				// check for horizontal win and increment win_count accordingly
				// if no win, reset win_count
				if(j+connect<=width){
					for(int col=j+1; col<j+connect; ++col){
						if(board[i][col]==piece){
							++win_count;
						}else{
							win_count = 1;
							break;
						}
					}
				}

				// check for winner for horizontal win, if so return true
				if(win_count==connect){
					return 1;
				}

				// check for right diagonal and increment win_count accordingly
				// if no win, reset win_count
				if(i+connect<=height && j+connect<=width){
					for(int k=1; k<connect; ++k){
						if(board[i+k][j+k]==piece){
							++win_count;
						}else{
							win_count = 1;
							break;
						}
					}
				}

				// check for winner for right diagonal win, if so return true
				if(win_count==connect){
					return 1;
				}

				// check for left diagonal and increment win_count accordingly
				// if no win, reset win_count
				if(i+connect<=height && j-connect>=-1){
					for(int k=1; k<connect; ++k){
						if(board[i+k][j-k]==piece){
							++win_count;
						}else{
							win_count = 1;
							break;
						}
					}
				}

				// check for winner for left diagonal win, if so return true
				if(win_count==connect){
					return 1;
				}

			}
		}
	}
	// no win was found, so return false
	return 0;
}

/*
	Function creates a formatted char array that will be used to save the game state
	@param buffer a pointer to a pointer that will be assigned the game data
	@param board, the two dimensional array of the game board
	@param height, the height of the game board
	@param width, the width of the game board
	@param connect, the number of pieces required to connect to win
	@param player an integer represented the current player
	@return the size of the buffer array
*/
void format_save(char*buffer, char**board, int* board_dim, int height, int width, int connect, int player){

	// assign the basic values at the beginning of the array
	// create some holder variables
	// add each dimension with the number of digits in the dimension
	// followed by the number itself with each char as each digit.
	// this is followe by a new line character
	// repeat this for all four dimensions
	int h = height;
	int w = width;
	int buf_index = board_dim[0];
	// add the height number
	for(int i=0; i<board_dim[0]; ++i){
		buffer[buf_index] = (h%10) + '0';
		h/=(int)10;
		--buf_index;
	}
	buffer[buf_index] = board_dim[0]+'0';
	buffer[board_dim[0]+1] = *"\n";
	buf_index = board_dim[0]+board_dim[1]+2;

	// assign the width of the board to the buffer
	for(int i=0; i<board_dim[1]; ++i){
		buffer[buf_index] = (w%10) + '0';
		w/=(int)10;
		--buf_index;
	}
	buffer[buf_index] = board_dim[1]+'0';
	buffer[board_dim[0]+board_dim[1]+3] = *"\n";
	buf_index = board_dim[0]+board_dim[1]+board_dim[2]+4;
	
	// assign the number of connections to the buffer
	for(int i=0; i<board_dim[2]; ++i){
		buffer[buf_index] = (connect%10) + '0';
		connect/=(int)10;
		--buf_index;
	}

	// assign the current player and increment the 
	// buf_index accordingly
	buffer[buf_index] = board_dim[2]+'0';
	buf_index = board_dim[0]+board_dim[1]+board_dim[2]+5;
	buffer[buf_index] = *"\n";
	++buf_index;
	buffer[buf_index] = player+ '0';
	++buf_index;
	buffer[buf_index] = '\n';
	++buf_index;

	// assign the pieces of the game to the buffer
	for(int i=0; i<height; ++i){
		for(int j=0; j<width; ++j){
			buffer[buf_index] = board[i][j];
			++buf_index;
		}
		buffer[buf_index] = '\n';
		++buf_index;
	}
	return;
}

/*
	Function puts the number of digits of each number into a given array
	@param bord_dim an array of size 3 that will hold the number of digits of each given number
	@param height the height of the game board
	@param width the width of the game board
	@param connect the number of connection required for a win
	@return void
*/
void board_dim_array(int board_dim[], int height, int width, int connect){

	// call a helper function that calculates the number of digits in each number
	board_dim[0] = find_size(height);
	board_dim[1] = find_size(width);
	board_dim[2] = find_size(connect);
	return;
}

/*
	Fuction calculates how many digits are contained in the given number
	@param number, an integer number
	@return the number of digits in the given number
*/
int find_size(int number){
	int size = 1;
	// moves the decimal to the left one digit
	number/=(int)10;
	// continues to loop until no more digits are left
	while(number>0){
		number/=(int)10;
		++size;
	}
	return size;
}
/*
	Function sets all of the game parameters from the buffer
	@param buffer the buffer containing the game parameters from a saved file
	@param height a pointer to the height of the game board
	@param width a pointer to the width of the game board
	@param connect a pointer to the number of connections reuquired for a win
	@param a pointer to the current player
	@return the buffer index that points to the first the pieces that will 
		be placed in the two dimensional array of the game board

*/
int format_load(char*buffer, int* height, int*width, int* connect, int*player){

	// extract the the number of digits of the height parameter
	// put each character in a string of chars
	// increment the buf_index accordingly throughout the function
	char str1[buffer[0]];
	int buf_index = 1;
	for(int i=0; i<buffer[0]-'0'; ++i){
		str1[i] = buffer[buf_index];
		++buf_index;
	}
	// convert the string of chars to a number and assign as the height
	*height = atoi(str1);
	++buf_index;
	// create a variable to hold the size of the next parameter
	int size = buffer[buf_index] - '0';
	// create another string of chars for the width
	char str2[size];
	++buf_index;
	for(int i=0; i<size; ++i){
		str2[i] = buffer[buf_index];
		++buf_index;
	}
	// convert the string of chars to a number and assign as the width
	*width = atoi(str2);
	++buf_index;
	// reassign the size variable to the size of the connections parameter
	size = (int)buffer[buf_index] - '0';
	// create a string of chars to hold each digit of the number of connections as chars
	char str3[size];
	++buf_index;
	for(int i=0; i<size; ++i){
		str3[i] = buffer[buf_index];
		++buf_index;
	}
	// conver the string of cahrs to a number and assign as the connections parameter
	*connect = atoi(str3);
	++buf_index;
	*player = buffer[buf_index] -'0';
	buf_index+=2;

	// the final buffer incrementation is the index that will return the 
	// first piece of the game board
	// it will be used in the next function call in main so it is returned
	return buf_index;
}


/*
	Function takes the arguments from the struct and places them in the 
	given pointers if they are supposed to be
	@param arg a struct containing the arguments
	@param height a pointer to the height of the board
	@param width a pointer to the width of the board
	@param connect the number of connections required for a win
	@return void
*/
void setup_board(struct arguments arg, int *height, int *width, int *connect){

	// if the height was given and is valid, assign it as the height
	// if not height was given, arg.height will equal 0
	if(arg.height<4 && arg.height!=0){
		printf("The height must be at least 4.  A default was used.\n");
	}else if(arg.height!=0){
		*height = arg.height;
	}

	// if the width was given and is valid, assign it as the width
	// if no width was given, width will equal 0
	if(arg.width<4 && arg.width!=0){
		printf("The width must be at least 4.  A default was used.\n");
	}else if(arg.width!=0){
		*width = arg.width;
	}

	// if the number of connections was given and is valic, assign it as connect
	// if no connect was given, connect will equal 0
	if(arg.connect<3 && arg.connect!=0){
		printf("The number of connections must be at least 3.  Default of 4 was used.\n");
	}else if(arg.connect!=0){
		*connect = arg.connect;
	}
	return;
}

/*
	Function allocates memory for the game board
	@param board, the two dimensional array of the game board
	@param height the height of the game board
	@param width, the width of the game board
	@return void
*/
void malloc_board(char *** board, int height, int width){

	// allocate the appropriate amount of memory for the 
	// height and width of the board
	*board = malloc(height * sizeof(char*));
	for(int i=0; i<height; ++i){
		*(*board+i) = malloc(width * sizeof(char));
	}
	return;
}

/*
 	Function allocates memory for the buffer which will write to a file
 	@param buffer a double pointer that will be malloced to a specifiec size
 	@param board_dim an array containing the number of digits for each board dimension
 	@param height, the height of the game board
 	@param width, the width of the game board
 	@param the size of the buffer
 */
int malloc_buffer(char** buffer, int* board_dim, int height, int width){

	// calculate the size of the buffer
	int total = board_dim[0]+board_dim[1]+board_dim[2]+8+height+(height*width);
	// malloc the appropriate amount of memory
	*buffer = malloc(total*sizeof(char));
	// return the size of the array
	return total;
}

/*
	Function prints which player's turn it currently is
	@param player, an integer representing the current player
	@return void
*/
void print_player(int player){

	// print a message according to who the current player is
	if(player==0){
		printf("It is player one's turn\n");
	}else{
		printf("It is player two's turn\n");
	}
	return;
}


/*
	Function switches the player to the next player
	@param player, a pointer to an integer representing the current player
	@return void
*/
void switch_player(int *player){

	// check what the player is and switch accordingly
	if(*player==0){
		*player=1;
	}else{
		*player=0;
	}
	return;
}

/*
	Function calculates the size of a string
	@param str an array of chars representing a string of an 
	arbitrary length
	@return the size of the string
*/
int string_size(char* str){
	int count = 0;
	while(str[count]!='\n'){
		++count;
	}
	return count;
}

/*
	Function sets every value of the char array to null character
	@param str a char array representing a string
	@param size the size of the char array
	@return void
*/
void set_null(char* str, int size){

	for(int i=0; i<size; ++i){
		str[i] = '\0';
	}
	return;
}

/*
	Function mallocs the appropriate amount of memory for a string of chars
	@param str a double pointer of what will become a char array
	@param size the desired size of the array
	@param void
*/
void malloc_string(char** str, int size){

	*str = malloc(size*sizeof(char));
	return;
}


/*
	Function assigns the values in one string and assigns them in another
	@param str1 an array of chars that will be manipulated
	@param str2 an array of chars that will be copied to str1
	@param size the size of str1 because this string will be concise
	@return void
*/
void string_to_string(char* str1, char* str2, int size){

	for(int i=0; i<size; ++i){
		str1[i] = str2[i];
	}
	return;
}

/*
	Function assigns the pieces to the board from the buffer
	@param buffer a pointer to a buffer array containing the pieces of the board
	@param board a two dimensional array of chars that will hold the board
	@param height the height of the game board
	@param width the width of the game board
	@param buf_index the current index of the buffer that is the first piece of the game
	@return void
*/
void buffer_to_board(char*buffer, char**board, int height, int width, int buf_index){

	// loop through and assign the pieces to their appropriate place in the board
	for(int i=0; i<height; ++i){
		for(int j=0; j<width; ++j){
				board[i][j] = buffer[buf_index];
				++buf_index;
		}
		++buf_index;
	}
	return;
}

// prints the commands for the game to the screen for the users to see
void print_commands(){
	printf("******Game Commands******\n\n");
	printf("Type 's' to save the game and follow the prompts\n");
	printf("Type 'n' for a new game\n");
	printf("Type 'l' to load a game and follow the prompts\n");
	printf("Type 'c' to see the commands list again\n");
	printf("Otherwise type a valid number in range to place a chip\n");
}
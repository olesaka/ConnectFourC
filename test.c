#include <stdio.h>
#include <stdlib.h>
#include "logic.h"
#include "test.h"
#include "assert.h"
#include "file_io.h"

/*
	This is a test file for the logic file that contains all of
	the functions used by the main method for connect four
	@author Andrew Olesak
	@version March 2, 2017
	**********THIS TEST FILE WILL TAKE ROUGHLY 10 SECONDS TO FULLY EXECUTE***********
*/

// create instance variables that will be used for testing
char** board1;
char** board2;
char** board3;
char* buffer1;
int height1 = 250;
int width1 = 400;
int connect1 = 100;
char* buffer2;
int height2 = 12000;
int width2 = 50000;
int connect2 = 1500;
char** board4;
char** board5;
int num1[3];
int num2[3];
int buf_size1;
int buf_size2;
char* buffer3;
char* buffer4;
int buf_index1;
int buf_index2;
char** board6;
char** board7;


// runs all of the tests in a certain order to reuse instance variables
// also frees up malloced memory
void test_all(){
	test_string_size();
	test_malloc_board();
	test_new_board();
	test_add_chip();
	test_check_for_winner();
	test_find_size();
	test_board_dim_array();
	test_switch_player();
	test_set_null();
	test_string_to_string();
	test_malloc_buffer();
	test_format_save();
	test_format_load();
	test_buffer_to_board();

	// if one of the above tests fails, then this
	// print statement will never be reached
	// the program will abort instead
	printf("***All Tests Passed***\n");
	free(board1);
	free(board2);
	free(board3);
	free(buffer1);
	free(buffer2);
	free(board4);
	free(board5);
	free(buffer3);
	free(buffer4);
	free(board6);
	free(board7);
	return;
}

// tests the output of the length of a string of chars
void test_string_size(){
	char* str1 = "hello\n";
	char* str2 = "this should be 17\n";
	char* str3 = "\n";
	assert(string_size(str1)==5);
	assert(string_size(str2)==17);
	assert(string_size(str3)==0);
	return;
}

// tests whether a new board was created successfully
void test_new_board(){
	new_board(board1, 7, 7);
	new_board(board2, 50, 25);
	new_board(board3, 145, 75);
	assert(board1[0][0]=='*');
	assert(board1[6][6]=='*');
	assert(board2[2][14]=='*');
	assert(board2[0][1]=='*');
	assert(board3[56][34]=='*');
	assert(board3[144][74]=='*');
	return;
}

// tests whether the board was malloced correctly
void test_malloc_board(){
	malloc_board(&board1, 7, 7);
	malloc_board(&board2, 50, 25);
	malloc_board(&board3, 145, 75);
	assert(board1[0][0]=='\0');
	assert(board1[6][6]=='\0');
	assert(board2[2][14]=='\0');
	assert(board2[0][1]=='\0');
	assert(board3[56][34]=='\0');
	assert(board3[144][74]=='\0');
	return;
}

// tests whether a chip can be added or the column is full
void test_add_chip(){

	for(int i=0; i<7; ++i){
		assert(add_chip(board1, 7, 7, 3, 'X')==1);
	}
	assert(add_chip(board1, 7, 7, 3, 'X')==0);
	assert(add_chip(board1, 7, 7, 7, 'O')==0);

	for(int i=0; i<50; ++i){
		assert(add_chip(board2, 50, 25, 24, 'O')==1);
	}
	assert(add_chip(board2, 50, 25, 24, 'X')==0);
	return;
}

/*
	In depth test case for checking whether there is a winner or not.  
	This includes multiple edge
*/
void test_check_for_winner(){
	// create two boards to test
	new_board(board1, 7, 7);
	new_board(board2, 50, 25);

	assert(check_for_winner(board2, 50, 25, 3, 'X')==0);

	// test for vertical on far left side of board
	for(int i=0; i<14; ++i){
		board2[0][i] = 'X';
		if(i!=13){
			assert(check_for_winner(board2, 50, 25, 14, 'X')==0);
		}
	}
	assert(check_for_winner(board2, 50, 25, 14, 'X')==1);
	new_board(board2, 50, 25);

	// test for horizontal on far left side on top
	for(int i=0; i<14; ++i){
		board2[i][0] = 'X';
		if(i!=13){
			assert(check_for_winner(board2, 50, 25, 14, 'X')==0);
		}
	}
	assert(check_for_winner(board2, 50, 25, 14, 'X')==1);
	new_board(board2, 50, 25);

	// tests for left diagonal starting at top left
	for(int i=0; i<14; ++i){
		board2[i][i] = 'X';
		if(i!=13){
			assert(check_for_winner(board2, 50, 25, 14, 'X')==0);
		}
	}
	assert(check_for_winner(board2, 50, 25, 14, 'X')==1);
	new_board(board2, 50, 25);

	// test for vertical on far right bottom
	for(int i=36; i<50; ++i){
		board2[i][24] = 'X';
		if(i!=49){
			assert(check_for_winner(board2, 50, 25, 14, 'X')==0);
		}
	}
	assert(check_for_winner(board2, 50, 25, 14, 'X')==1);
	new_board(board2, 50, 25);

	// test for horizontal on far right bottom
	for(int i=11; i<25; ++i){
		board2[49][i] = 'X';
		if(i!=24){
			assert(check_for_winner(board2, 50, 25, 14, 'X')==0);
		}
	}
	assert(check_for_winner(board2, 50, 25, 14, 'X')==1);
	new_board(board2, 50, 25);

	// test for down right diagonal to far right bottom corner
	int j=11;
	for(int i=36; i<50; ++i){
		board2[i][j] = 'X';
		if(i!=49){
			assert(check_for_winner(board2, 50, 25, 14, 'X')==0);
		}
		++j;
	}
	assert(check_for_winner(board2, 50, 25, 14, 'X')==1);
	new_board(board2, 50, 25);

	// test for vertical on far left bottom
	for(int i=0; i<4; ++i){
		board2[49-i][0]='X';
	}
	assert(check_for_winner(board2, 50, 25, 5, 'X')==0);
	board2[45][0] = 'X';
	assert(check_for_winner(board2, 50, 25, 5, 'X')==1);
	new_board(board2, 50, 25);
	return;
}

// tests for whether or not the correct number of digits is return for size of an int
void test_find_size(){
	assert(find_size(14542)==5);
	assert(find_size(7)==1);
	assert(find_size(285)==3);
	assert(find_size(48151623)==8);
	return;
}

// test whether the board dimension array is assigned correctly
void test_board_dim_array(){

	int nums[3];
	board_dim_array(nums, 34293, 1121, 23123953);
	assert(nums[0]==5);
	assert(nums[1]==4);
	assert(nums[2]==8);
	board_dim_array(nums, 2, 1231000003, 22222222);
	assert(nums[0]==1);
	assert(nums[1]==10);
	assert(nums[2]==8);
	return;
}

// tests if the current player gets switched correctly
void test_switch_player(){
	int p = 0;
	switch_player(&p);
	assert(p==1);
	switch_player(&p);
	assert(p==0);
	return;
}

// tests to see if a string is completely set to null
void test_set_null(){
	char* str1 = malloc(10*sizeof(char));
	char* str2 = malloc(15*sizeof(char));
	set_null(str1, 10);
	set_null(str2, 15);
	assert(str1[0]=='\0');
	assert(str1[5]=='\0');
	assert(str1[9]=='\0');
	assert(str2[0]=='\0');
	assert(str2[14]=='\0');
	free(str1);
	free(str2);
	return;
}

// tests whether a string gets correctly assigned to another string
void test_string_to_string(){
	char* str1 = malloc(13*sizeof(char));
	char* str2 = malloc(5*sizeof(char));
	char* str3 = "hello";
	char* str4 = "yes of course";
	string_to_string(str1, str4, 13);
	string_to_string(str2, str3, 5);
	assert(str1[0]=='y');
	assert(str1[12]=='e');
	assert(str1[6]==' ');
	assert(str2[0]=='h');
	assert(str2[4]=='o');
	assert(str2[1]=='e');
	free(str1);
	free(str2);
	return;
}

// tests to see if the buffer gets malloced correctly
void test_malloc_buffer(){
	board_dim_array(num1, height1, width1, connect1);
	buf_size1 = malloc_buffer(&buffer1, num1, height1, width1);
	board_dim_array(num2, height2, width2, connect2);
	buf_size2 = malloc_buffer(&buffer2, num2, height2, width2);
	assert(buf_size1==100267);
	assert(buf_size2==600012022);
	return;
}

// tests to see if the buffer is formatted correctly to be saved
void test_format_save(){
	malloc_board(&board4, height1, width1);
	malloc_board(&board5, height2, width2);
	new_board(board4, height1, width1);
	new_board(board5, height2, width2);
	format_save(buffer1, board4, num1, height1, width1, connect1, 0);
	format_save(buffer2, board5, num2, height2, width2, connect2, 1);
	assert(buffer1[0]=='3');
	assert(buffer1[2]=='5');
	assert(buffer1[4]=='\n');
	assert(buffer1[10]=='3');
	assert(buffer1[13]=='0');
	assert(buffer1[14]=='\n');
	assert(buffer1[15]=='0');
	assert(buffer1[116]=='*');
	assert(buffer1[100266]=='\n');

	assert(buffer2[0]=='5');
	assert(buffer2[3]=='0');
	assert(buffer2[4]=='0');
	assert(buffer2[6]=='\n');
	assert(buffer2[8]=='5');
	assert(buffer2[9]=='0');
	assert(buffer2[14]=='4');
	assert(buffer2[18]=='0');
	assert(buffer2[20]=='1');
	assert(buffer2[22]=='*');
	assert(buffer2[600012021]=='\n');
	write_file("test_file1", buffer1, buf_size1);
	write_file("test_file2", buffer2, buf_size2);
	return;
}

// tests whether the game parameters were assigned correctly 
void test_format_load(){

	read_file("test_file1", &buffer3);
	read_file("test_file2", &buffer4);
	int p1 = 0;
	int p2 = 0;
	buf_index1 = format_load(buffer3, &height1, &width1, &connect1, &p1);
	buf_index2 = format_load(buffer4, &height2, &width2, &connect2, &p2);
	assert(height1==250);
	assert(width1== 400);
	assert(connect1==100);
	assert(height2==12000);
	assert(width2==50000);
	assert(connect2==1500);
	assert(p1==0);
	assert(p2==1);

	return;
}

// tests whether the game pieces are assigned to the board correctly
void test_buffer_to_board(){

	malloc_board(&board6, height1, width1);
	malloc_board(&board7, height2, width2);
	buffer_to_board(buffer3, board6, height1, width1, buf_index1);
	buffer_to_board(buffer4, board7, height2, width2, buf_index2);
	assert(board6[height1-1][width1-1]=='*');
	assert(board6[0][0]=='*');
	assert(board6[124][56]=='*');
	assert(board7[height2-1][width2-1]=='*');
	assert(board7[0][0]=='*');
	assert(board7[5430][6560]=='*');
	assert(buffer3[buf_index1-1]=='\n');
	assert(buffer4[buf_index2-1]=='\n');
	return;
}


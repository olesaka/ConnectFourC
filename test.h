#ifndef TEST
#define TEST

/*
	Test functions that cover each function in the logic file and tests
	for completeness and accuracy
*/

// Function calls every test function to run them all at once
void test_all();

// tests the size of a give string function
void test_string_size();

// tests whether a new board is created successfully
void test_new_board();

// tests whether the board is malloced properly
void test_malloc_board();

// tests whether a chip can be added or not
void test_add_chip();

// test whether or not there is a winner in the game
void test_check_for_winner();

// tests whether the correct number of digits is returned
void test_find_size();

// tests whether the correct values are stored in a give array of ints
void test_board_dim_array();

// tests whether the current player is switched properly
void test_switch_player();

// tests whether a give string is set to null
void test_set_null();

// tests wheter a strings is successfully copied to another string
void test_string_to_string();

// tests wheter the buffer is malloced correctly
void test_malloc_buffer();

// tests whether the buffer is formatted correctly to be saved
void test_format_save();

// tests whether the correct parameters are put into the game parameters
void test_format_load();

// tests whether the specific game data is put into the board
void test_buffer_to_board();

#endif
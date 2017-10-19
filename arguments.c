#include <stdlib.h>
#include "arguments.h"

/*
	The following code was created by a framework provided by professor
	Ira Woodring
*/


// Title and version of the program
const char *argp_program_version = "Parse connect four arguments, beta";

// contact the given email address for bugs
const char *argp_program_bug_address = "olesaka@mail.gvsu.edu";

// Describes the process of the program
char doc[] = "Args program to parse given input for a connect four game.";

// Describes the accepted arguments, all are optional
char args_doc[] = "The game parameters accepted are a height, width, \nnumber of connections for a win, and a loaded game from a save file";

// Shows the options in detail for the arguments
struct argp_option options[] = {
	{"height",	'h', 	"HEIGHT",	0,	"Argument for height of board"},
	{"width",	'w',	"WIDTH",	0,	"Argument for width of board"},
	{"squre",	's',	"SQUARE",	0,	"Argument for a square board"},
	{"connect",	'c',	"CONNECT",	0,	"Arument for number of pieces to connect"},
	{"load",	'l',	"LOAD",		0,	"Argument for loading from a file"},
	{0}
};

struct argp argp = {options, parse_opt, args_doc, doc};

// declare an arguments struct called arguments to actually hold data
struct arguments arguments;

// Function assigns values to the struct above according to the given arguments
error_t parse_opt(int key, char* arg, struct argp_state*state){
	struct arguments*arguments = state->input;
	switch(key){
		case 'h':
			arguments->height = atoi(arg);
			break;
		case 'w':
			arguments->width = atoi(arg);
			break;
		case 's':
			arguments->height = atoi(arg);
			arguments->width = atoi(arg);
			break;
		case 'c':
			arguments->connect = atoi(arg);
			break;
		case 'l':
			arguments->load_file = arg;
			break;
		defualt:
			return ARGP_ERR_UNKNOWN;
	}
	return 0;
}

// calls the parser and returns the struct
struct arguments setup(int argc, char** argv){
	// call the parser
	argp_parse(&argp, argc, argv, 0, 0, &arguments);
	// return the given arguments whether they were overidden or not
	return arguments;
}
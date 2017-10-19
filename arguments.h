#ifndef ARGUMENTS
#define ARGUMENTS
#include <argp.h>

// define some values in a struct for the given arguments
struct arguments{
	int height;
	int width;
	int connect;
	char* load_file;
};

// Function processes the arguments and places them in the
// appropriate struct parameters
error_t parse_opt(int key, char* arg, struct argp_state* state);

// Function begins parsing the input data
struct arguments setup(int argc, char**argv);

#endif
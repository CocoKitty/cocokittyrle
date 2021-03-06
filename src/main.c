// Made by CocoKitty on 2020-07-01

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "locale.h"

#define ERROR_STRING_SIZE 50
#define FILE_STRING_SIZE 255

// command line options
typedef struct {

    // whether to print 
    bool verbose;
    bool dont_compress;
    char input_file[FILE_STRING_SIZE];
	char output_file[FILE_STRING_SIZE];
} Options;

// the operation to do
typedef enum {
    OPER_ENCODE,
    OPER_DECODE,
    OPER_VIEW,
} Operation;

// returns 0 if succesfull, 1 if failed,
// -1 if needs help, -2 if needs version 
int parse_args(int argc, char** argv, char* fail_string, Options* options, Operation* oper);

int main(int argc, char** argv) {
    Options cmd_options;
    Operation cmd_operation;

    //FILE* to_parse;

    char fail_string[ERROR_STRING_SIZE] = "unknown error";

    int args_return;

    args_return = parse_args(argc, argv, fail_string, &cmd_options,
		&cmd_operation);

    if ( args_return == 1 ) {
        printf("error: %s. try 'rle -h'\n", fail_string);
    } else if ( args_return == -1 ) {
        printf(HELP_STRING);
    } else if ( args_return == -2 ) {
		printf("rle version " VER_STR);
	}
	
	// start the actual tool
	


}

int parse_args(int argc, char** argv, char* fail_string,
	Options* options, Operation* oper) {

	int curr_arg = 1;

	// needed to avoid segfault with empty args
	
	if (argc <= 1) {
			return -1;
	}
	
    // check for operation

    if ( strcmp(argv[curr_arg], "-e") == 0 ||
			strcmp(argv[curr_arg], "--encode") == 0 ) {
        *oper = OPER_ENCODE;

    } else if ( strcmp(argv[curr_arg], "-d") == 0 ||
			strcmp(argv[curr_arg], "--decode") == 0 ) {

        *oper = OPER_DECODE;
    } else if ( strcmp(argv[curr_arg], "-s") == 0 ||
			strcmp(argv[curr_arg], "--show") == 0 ) {
        *oper = OPER_VIEW;

    } else if ( strcmp(argv[curr_arg], "-h") == 0 ||
			strcmp(argv[curr_arg], "--help") == 0 ) {
        return -1;

	} else if ( strcmp(argv[curr_arg], "-v") == 0 ||
			strcmp(argv[curr_arg], "--version") == 0) {
		return -2;

    } else {
        strncpy(fail_string, "invalid operation", ERROR_STRING_SIZE);
        return 1;
    }

	curr_arg++;

    // check arg number, after operation because rle -h is valid

    if (argc <= 2) {
        strncpy(fail_string, "not enough arguments", ERROR_STRING_SIZE);
        return 1;
    }

    // read in file(s)

    strncpy( options->input_file, argv[curr_arg], FILE_STRING_SIZE );
	// only read output arg if not in show mode
	if (*oper != OPER_VIEW) {
		curr_arg++;
	}
    strncpy( options->output_file, argv[curr_arg], FILE_STRING_SIZE );

	
    // set args to default values
    options->verbose = false;
    options->dont_compress = false;
    // check for args

	if (*oper == OPER_VIEW) {
		curr_arg++;
		if (curr_arg == argc) {
			return 0;
		}
	}

    for (int i = curr_arg; i != argc; ++i) {
        if ( strcmp(argv[i], "-v") == 0 ||
				strcmp(argv[i], "--verbose") == 0 ) {
            options->verbose = true;

        } else if ( strcmp(argv[i], "-dc") == 0 ||
				strcmp(argv[i], "--dont-compress") == 0 ) {
			// detect incorrect mode
			if (*oper != OPER_ENCODE) {
				strncpy(fail_string, "--dont-compress is only for encode",
						FILE_STRING_SIZE );
			}
            options->dont_compress = true;

        } else {
			snprintf(fail_string, FILE_STRING_SIZE, "invalid option: %s",
					argv[i] );
			return 1;
		}
    }

    return 0;

}

#ifndef CMD_ARGS_H
#define CMD_ARGS_H
#include <stdbool.h>
#include <stdlib.h>
#include "types.h"

#define COMMAND_ADD_STR "add"
#define COMMAND_LIST_STR "list"
#define COMMAND_REMOVE_STR "remove"
#define COMMAND_SEARCH_STR "search"

/**
 * input arguments from the command line
 */
struct st_cmd_args
{
    st_student_t student;
    char *            db_file;
    st_command_type_t command;

    int               error;
    char              str_error[100];
    bool              search_and_flag;
    size_t            print_limit;
};

typedef struct st_cmd_args st_cmd_args_t;


/**
 * Parse the command line arguments and returns all
 * the useful values.
 * If something is wrong, the returned structure
 * will have a non-null 'error' attribut and the 'str_error'
 * attribut will contain a description of the error
 */
st_cmd_args_t st_cmd_args_parse(int argc, char ** argv);

/**
 * Convert a command type to a printable string
 */
char *st_command_type_to_string(st_command_type_t type);

#endif
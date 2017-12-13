#ifndef CMD_ARGS_H
#define CMD_ARGS_H
#include <stdbool.h>
#include "types.h"


/**
 * input arguments from the command line
 */
struct st_cmd_args
{
    st_student_t student;
    char *       db_file;
    char *       command;

    int          error;
    char         str_error[100];
    bool         search_and_flag;
};

typedef struct st_cmd_args st_cmd_args_t;


st_cmd_args_t st_cmd_args_parse(int argc, char ** argv);


#endif
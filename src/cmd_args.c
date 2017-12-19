#include "cmd_args.h"
#include <unistd.h>
#include <getopt.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


char *st_command_type_to_string(st_command_type_t type)
{
    switch(type)
    {
        case COMMAND_ADD:
            return COMMAND_ADD_STR;
        case COMMAND_LIST:
            return COMMAND_LIST_STR;
        case COMMAND_REMOVE:
            return COMMAND_REMOVE_STR;
        case COMMAND_SEARCH:
            return COMMAND_SEARCH_STR;
        default:
            return "Unknown command";
    }
}

st_command_type_t st_parse_command_arg(char * command_str)
{
    int n = strlen(command_str);
    for(int i = 0; i < n; i++)
    {
        command_str[i] = tolower(command_str[i]);
    }

    if(!strcmp(command_str, COMMAND_ADD_STR))
    {
        return COMMAND_ADD;
    }
    if(!strcmp(command_str, COMMAND_LIST_STR))
    {
        return COMMAND_LIST;
    }
    if(!strcmp(command_str, COMMAND_REMOVE_STR))
    {
        return COMMAND_REMOVE;
    }
    if(!strcmp(command_str, COMMAND_SEARCH_STR))
    {
        return COMMAND_SEARCH;
    }
    return COMMAND_UNKNOWN;
}

st_cmd_args_t st_cmd_args_parse(int argc, char ** argv)
{
    st_cmd_args_t args = {.error = 0};

    if(argc < 2)
    {
        args.error = 2;
        strcpy(args.str_error, "Not enough arguments");
        return args;
    }

    args.command = st_parse_command_arg(argv[1]);
    args.db_file = "students.txt";
    args.print_limit = SIZE_MAX;

    char c;
    while ((c = getopt (argc, argv, "ad:f:l:i:b:n:")) != -1)
    {
        switch (c)
        {
            case 'a':
                args.search_and_flag = 1;
                break;
            case 'd':
                args.db_file = optarg;
                break;
            case 'f':
                strncpy(
                    args.student.first_name,
                    optarg,
                    MAX_STUDENT_STRLEN);
                break;
            case 'l':
                strncpy(
                    args.student.last_name,
                    optarg,
                    MAX_STUDENT_STRLEN);
                break;
            case 'i':
                args.student.id = atoi(optarg);
                break;
            case 'b':
                args.student.birth_year = atoi(optarg);
                break;
            case 'n':
                args.print_limit = atoll(optarg);
                break;
            case '?':
                if (isprint (optopt))
                {
                    args.error = 1;
                    sprintf(
                        args.str_error,
                        "Unknown option `-%c' or `-%c' should be"
                        " followed by an argument.",
                        optopt, optopt);
                }
                else
                {
                    args.error = 1;
                    sprintf(
                        args.str_error,
                        "Unknown option character `\\x%x'.",
                        optopt);
                }
        }
    }
    return args;
}
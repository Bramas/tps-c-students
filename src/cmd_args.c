#include "cmd_args.h"
#include <unistd.h>
#include <getopt.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

st_cmd_args_t st_cmd_args_parse(int argc, char ** argv)
{
    st_cmd_args_t args = {.error = 0};

    if(argc < 2)
    {
        args.error = 2;
        strcpy(args.str_error, "Not enough arguments");
        return args;
    }

    args.command = argv[1];
    args.db_file = "students.txt";

    char c;
    while ((c = getopt (argc, argv, "ad:f:l:i:b:")) != -1)
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
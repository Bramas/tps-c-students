#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <ctype.h>
#include <errno.h>
#include "commands.h"
#include "db.h"
#include "types.h"


#define COMMAND_ADD "add"
#define COMMAND_LIST "list"
#define COMMAND_REMOVE "remove"
#define COMMAND_SEARCH "search"

void printUsage(void);

int main(int argc, char ** argv)
{
    if(argc < 2)
    {
        printUsage();
        return 1;
    }

    char * command = argv[1];
    printf("Command %s\n", command);


    char *db_file = "students.txt";
    st_student_t arg_student = {};

    char c;
    while ((c = getopt (argc, argv, "d:f:l:i:b:")) != -1)
        switch (c)
        {
            case 'd':
                db_file = optarg;
                break;
            case 'f':
                strncpy(arg_student.first_name, optarg, MAX_STUDENT_STRLEN);
                break;
            case 'l':
                strncpy(arg_student.last_name, optarg, MAX_STUDENT_STRLEN);
                break;
            case 'i':
                arg_student.id = atoi(optarg);
                break;
            case 'b':
                arg_student.birth_year = atoi(optarg);
                break;
            case '?':
                if (optopt == 'c')
                    fprintf (stderr, "Option -%c requires an argument.\n", optopt);
                else if (isprint (optopt))
                    fprintf (stderr, "Unknown option `-%c'.\n", optopt);
                else
                    fprintf (stderr,
                       "Unknown option character `\\x%x'.\n",
                       optopt);
                return 1;
        }


    st_db_t *db = st_db_init(db_file);
    if(db == NULL)
    {
        printf("Error: %s\n", st_db_get_last_error());
        printf("errno %i: %s\n", errno, strerror(errno));
        return 1;
    }

    if(!strcmp(command, COMMAND_ADD))
    {
        st_command_add(db, arg_student);
    }
    else if(!strcmp(command, COMMAND_LIST))
    {
        st_command_list(db);
    }
    else if(!strcmp(command, COMMAND_REMOVE))
    {
        st_command_remove(db, arg_student.id);
    }
    else
    {
        printf("Unknown command\n");
        printUsage();
        return 1;
    }
    st_db_free(db);

}


void printUsage(void)
{
    printf(
        "Usage: students COMMAND OPTIONS\n"
        "Available commands:\n"
        "  - "COMMAND_ADD": add a student\n"
        "  - "COMMAND_LIST": list all the student\n"
        "  - "COMMAND_REMOVE": remove a student\n"
    );
}
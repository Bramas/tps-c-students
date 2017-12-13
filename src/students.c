#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "commands.h"
#include "db.h"
#include "types.h"
#include "cmd_args.h"


#define COMMAND_ADD "add"
#define COMMAND_LIST "list"
#define COMMAND_REMOVE "remove"
#define COMMAND_SEARCH "search"

void printUsage(void);

int main(int argc, char ** argv)
{
    st_cmd_args_t arguments = st_cmd_args_parse(argc,argv);
    if(arguments.error)
    {
        fprintf(stderr, "%s\n", arguments.str_error);
        printUsage();
        return 1;
    }

    printf("Command %s\n", arguments.command);


    st_db_t *db = st_db_init(arguments.db_file);
    if(db == NULL)
    {
        printf("Error: %s\n", st_db_get_last_error());
        printf("errno %i: %s\n", errno, strerror(errno));
        return 1;
    }

    if(!strcmp(arguments.command, COMMAND_ADD))
    {
        st_command_add(db, arguments.student);
    }
    else if(!strcmp(arguments.command, COMMAND_LIST))
    {
        st_command_list(db);
    }
    else if(!strcmp(arguments.command, COMMAND_REMOVE))
    {
        st_command_remove(db, arguments.student.id);
    }

    else if(!strcmp(arguments.command, COMMAND_SEARCH))
    {
        st_command_search(
            db,
            arguments.student,
            arguments.search_and_flag
            );
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
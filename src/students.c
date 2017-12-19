#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "commands.h"
#include "db.h"
#include "types.h"
#include "cmd_args.h"



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

    printf("Command %s\n",
        st_command_type_to_string(arguments.command));


    st_db_t *db = st_db_init(arguments.db_file);
    if(db == NULL)
    {
        printf("Error: %s\n", st_db_get_last_error());
        printf("errno %i: %s\n", errno, strerror(errno));
        return 1;
    }

    //TODO: Utilisation des énum
    switch(arguments.command)
    {
        case COMMAND_ADD:
            st_command_add(db, arguments);
            break;
        case COMMAND_LIST:
            st_command_list(db, arguments);
            break;
        case COMMAND_REMOVE:
            st_command_remove(db, arguments);
            break;
        case COMMAND_SEARCH:
            st_command_search(db, arguments);
                break;
        default:
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
        "  - "COMMAND_ADD_STR": add a student\n"
        "  - "COMMAND_LIST_STR": list all the student\n"
        "  - "COMMAND_REMOVE_STR": remove a student\n"
        "  - "COMMAND_SEARCH_STR": search for a student,"
        " by id, name or birth year\n"
    );
}
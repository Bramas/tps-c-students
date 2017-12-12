#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"

#define COMMAND_ADD "add"
#define COMMAND_LIST "list"

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

    if(!strcmp(command, COMMAND_ADD))
    {
        printf("Not implemented\n");
    }
    else if(!strcmp(command, COMMAND_LIST))
    {
        st_command_list();
    }
    else
    {
        printf("Unknown command\n");
        printUsage();
        return 1;
    }
}


void printUsage(void)
{
    printf(
        "Usage: students COMMAND OPTIONS\n"
        "Available commands:\n"
        "  - "COMMAND_ADD": add a student\n"
        "  - "COMMAND_LIST": list all the student\n"
    );
}
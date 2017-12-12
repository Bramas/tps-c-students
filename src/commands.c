#include "commands.h"
#include "db.h"

#include <stdio.h>
#include <errno.h>
#include <string.h>

void st_command_list(void)
{
    st_db_t *db = st_db_init("students.txt");
    if(db == NULL)
    {
        printf("Error: %s\n", st_db_get_last_error());
        printf("errno %i: %s\n", errno, strerror(errno));
        return;
    }

    if(!st_db_load(db))
    {
        printf("Error: %s\n", st_db_get_last_error());
        printf("errno %i: %s\n", errno, strerror(errno));
        return;
    }

    printf("OK\n");
}
#include "commands.h"
#include "db.h"

#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>

void st_command_list(st_db_t *db, st_cmd_args_t args)
{
    if(!st_db_load(db))
    {
        printf("Error: %s\n", st_db_get_last_error());
        printf("errno %i: %s\n", errno, strerror(errno));
        return;
    }

    for(size_t i = 0;
        i < st_db_size(db) && i < args.print_limit;
        i++) {
        st_student_t student = st_db_get(db,i);
        st_student_print(student);
    }
}

void st_command_add(st_db_t *db, st_cmd_args_t args)
{
    if(!st_db_load(db))
    {
        printf("Error: %s\n", st_db_get_last_error());
        printf("errno %i: %s\n", errno, strerror(errno));
        return;
    }
    if(!st_db_add(db, args.student))
    {
        printf("Error: %s\n", st_db_get_last_error());
        printf("errno %i: %s\n", errno, strerror(errno));
        return;
    }

    if(!st_db_save(db))
    {
        printf("Error: %s\n", st_db_get_last_error());
        printf("errno %i: %s\n", errno, strerror(errno));
        return;
    }
    printf("Success\n");

}

void st_command_remove(st_db_t *db, st_cmd_args_t args)
{
    if(!st_db_load(db))
    {
        printf("Error: %s\n", st_db_get_last_error());
        printf("errno %i: %s\n", errno, strerror(errno));
        return;
    }
    if(!st_db_remove_by_id(db, args.student.id))
    {
        printf("Error: %s\n", st_db_get_last_error());
        printf("errno %i: %s\n", errno, strerror(errno));
        return;
    }
    if(!st_db_save(db))
    {
        printf("Error: %s\n", st_db_get_last_error());
        printf("errno %i: %s\n", errno, strerror(errno));
        return;
    }
    printf("Success\n");

}


bool st_student_match(
    st_student_t arg_student,
    st_student_t student,
    bool and_flag)
{
    if(and_flag)
    {
        return
         (arg_student.id == 0
            || arg_student.id == student.id)
      && (strlen(arg_student.last_name) == 0
        || !strcmp(arg_student.first_name, student.first_name))
      && (strlen(arg_student.last_name) == 0
        || !strcmp(arg_student.last_name, student.last_name))
      && (arg_student.birth_year == 0
        || arg_student.birth_year == student.birth_year);
    }
    return
          arg_student.id == student.id
      || !strcmp(arg_student.first_name, student.first_name)
      || !strcmp(arg_student.last_name, student.last_name)
      || arg_student.birth_year == student.birth_year;
}

void st_command_search(
    st_db_t *db,
    st_cmd_args_t args
    )
{
    if(!st_db_load(db))
    {
        printf("Error: %s\n", st_db_get_last_error());
        printf("errno %i: %s\n", errno, strerror(errno));
        return;
    }
    size_t found = 0;
    for(size_t i = 0;
        i < st_db_size(db) && found < args.print_limit;
        i++) {
        st_student_t student = st_db_get(db,i);
        if(st_student_match(
                args.student,
                student,
                args.search_and_flag
            ))
        {
            st_student_print(student);
            found++;
        }
    }
    if(found == 0 && args.print_limit != 0)
    {
        printf("No student found\n");
    }
}

void st_student_print(st_student_t student)
{
    printf(
        "\n"
        "id:         %u\n"
        "first name: %s\n"
        "last name:  %s\n"
        "birth year: %hu\n",
        student.id,
        student.first_name,
        student.last_name,
        student.birth_year);
}
/**
 * Contains all the functions associated
 * with all the commands
 *
 *
 * Auteur: Quentin Bramas <bramas@unistra.fr>
 */


#ifndef COMMANDS_H
#define COMMANDS_H

#include "types.h"
#include "cmd_args.h"
#include <stdbool.h>
#include <stdlib.h>

/**
 * Print the list of all the students
 * in the database
 */
void st_command_list(st_db_t *db, st_cmd_args_t args);

/**
 * Add a single student to the database
 */
void st_command_add(st_db_t *db, st_cmd_args_t args);

/**
 * Remove a single student with the given id from the database
 */
void st_command_remove(st_db_t *db, st_cmd_args_t args);

/**
 * print a student in the terminal
 */
void st_student_print(st_student_t student);

/**
 * Search and prints all the students that have at least one value matching
 * the student parsed from the command line argument
 * If the and_flag 'true' only the students that match all the non-null attributs
 * of the arg_student will be matched.
 */
void st_command_search(
    st_db_t *db,
    st_cmd_args_t arguments);

#endif // COMMANDS_H



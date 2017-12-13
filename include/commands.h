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
#include <stdbool.h>

/**
 * Print the list of all the students
 * in the database
 */
void st_command_list(st_db_t *db);

void st_command_add(st_db_t *db, st_student_t student);

void st_command_remove(st_db_t *db, unsigned int id);


void st_command_search(
    st_db_t *db,
    st_student_t arg_student,
    bool and_flag);

#endif // COMMANDS_H



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

/**
 * Print the list of all the students
 * in the database
 */
void st_command_list(st_db_t *db);

void st_command_add(st_db_t *db, st_student_t student);

void st_command_remove(st_db_t *db, unsigned int id);

#endif // COMMANDS_H



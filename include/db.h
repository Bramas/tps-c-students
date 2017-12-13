
#ifndef DB_H
#define DB_H

#include "types.h"

#include <stdio.h>
#include <stdbool.h>

#define ERROR_MALLOC "Memory allocation error"
#define ERROR_CANNOT_OPEN_DB_FILE           \
    "Cannot open db file with write mode, " \
    "see errno for more information"
#define ERROR_EOF "Unexpected end of file"
#define ERROR_WRITING \
           "Cannot write in the db file " \
           "(see errno for more information)"
#define ERROR_ID_NOT_FOUND "Id not found"


/**
 * returns the last error that might have occured
 * during any db function call
 */
char *st_db_get_last_error(void) ;

/**
 * Initialize the database.
 * Returns a pointer to a structure
 * that represents the database.
 * Returns a null pointer when an error occurs
 */
st_db_t * st_db_init(const char *filepath);

/**
 * Load the database into memory
 */
bool st_db_load(st_db_t *db);

/**
 * return the number of students
 * in the database
 */
size_t st_db_size(st_db_t *db);
/**
 * return i-th student
 */
st_student_t st_db_get(st_db_t *db, int i);


bool st_db_add(st_db_t *db, st_student_t student);


bool st_db_save(st_db_t *db);

bool st_db_remove_by_id(st_db_t *db, unsigned int id);

void st_db_remove(st_db_t *db, int to_be_deleted);

void st_db_free(st_db_t *db);
#endif

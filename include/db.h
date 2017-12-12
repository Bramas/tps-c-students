
#ifndef DB_H
#define DB_H

#include "types.h"

#include <stdbool.h>

#define ERROR_MALLOC "Memory allocation error"
#define ERROR_CANNOT_OPEN_DB_FILE           \
    "Cannot open db file with write mode, " \
    "see errno for more information"



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

#endif

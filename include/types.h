
#ifndef TYPES_H
#define TYPES_H

#define MAX_STUDENT_STRLEN 32

/**
 * Structur holding database informations
 */
struct st_db;
typedef struct st_db st_db_t;


/**
 * Structure storing one student
 */
struct st_student {
    char           first_name[MAX_STUDENT_STRLEN];
    char           last_name[MAX_STUDENT_STRLEN];
    unsigned int   id;
    unsigned short birth_year;
};
typedef struct st_student st_student_t;


/**
 * Types of acceptable command
 */
enum st_command_type {
    COMMAND_UNKNOWN = 0,
    COMMAND_ADD,
    COMMAND_LIST,
    COMMAND_REMOVE,
    COMMAND_SEARCH
};
typedef enum st_command_type st_command_type_t;



#endif // TYPES_H

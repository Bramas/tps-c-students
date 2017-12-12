#include "db.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct st_db {
    char *filepath;
    size_t size;
    st_student_t *students;
};

static char * st_db_last_error;

char *st_db_get_last_error(void) {
    return st_db_last_error;
}


bool st_db_init_alloc(st_db_t **db);
bool st_db_init_filepath(st_db_t *db, const char *filepath);
bool st_db_init_db_file(st_db_t *db);

bool st_db_alloc_students(st_db_t *db);


st_db_t * st_db_init(const char *filepath)
{
    st_db_t *db;

    if(!st_db_init_alloc(&db))
        return NULL;
    if(!st_db_init_filepath(db, filepath))
        return NULL;
    if(!st_db_init_db_file(db))
        return NULL;

    return db;
}
bool st_db_init_alloc(st_db_t **db)
{
    *db = calloc(1, sizeof(st_db_t));
    if(*db == NULL)
    {
        st_db_last_error = ERROR_MALLOC;
        return false;
    }
    return true;
}
bool st_db_init_filepath(st_db_t *db, const char *filepath)
{
    size_t filepath_length = strlen(filepath);
    db->filepath = malloc(filepath_length+1);
    if(db->filepath == NULL)
    {
        st_db_last_error = ERROR_MALLOC;
        free(db);
        return false;
    }
    strncpy(db->filepath, filepath, filepath_length);
    return true;
}

bool st_db_init_db_file(st_db_t *db)
{
    FILE * db_file = fopen(db->filepath, "r+");
    if(db_file == NULL) {
        st_db_last_error = ERROR_CANNOT_OPEN_DB_FILE;
        free(db);
        return false;
    }
    fclose(db_file);
    return true;
}

void st_str_trim(char * str)
{
    int n = strlen(str);
    n--;
    while(n >= 0 && isspace(str[n]))
    {
        str[n] = '\0';
        n--;
    }
}

bool st_db_read_string_attribute(char * str, FILE *in)
{
    if(NULL == fgets(
            str,
            MAX_STUDENT_STRLEN,
            in
        ))
    {
        st_db_last_error = ERROR_EOF;
        return false;
    }
    st_str_trim(str);
    return true;
}
bool st_db_read_id_attribute(unsigned int * value, FILE *in)
{
    if(0 >= fscanf(in, "%u\n", value))
    {
        st_db_last_error = ERROR_EOF;
        return false;
    }
    return true;
}
bool st_db_read_birth_year_attribute(unsigned short * value, FILE *in)
{
    if(0 >= fscanf(in, "%hu\n", value))
    {
        st_db_last_error = ERROR_EOF;
        return false;
    }
    return true;
}
bool st_db_read_student(st_student_t * student, FILE *in)
{
    return
        st_db_read_string_attribute(student->first_name, in)
     && st_db_read_string_attribute(student->last_name, in)
     && st_db_read_id_attribute(&(student->id), in)
     && st_db_read_birth_year_attribute(&(student->birth_year), in);
}
bool st_db_open_db_file(st_db_t *db, const char * mode, FILE **in)
{
    *in = fopen(db->filepath, mode);
    if(*in == NULL)
    {
        st_db_last_error = ERROR_CANNOT_OPEN_DB_FILE;
        return false;
    }
    return true;
}
bool st_db_read_size(st_db_t *db, FILE *in)
{
    if(0 >= fscanf(in, "%zi\n", &(db->size)))
        return false;
    return true;
}

bool st_db_load(st_db_t *db)
{
    FILE *in;

    if(!st_db_open_db_file(db, "r", &in))
        return false;

    if( ! (
           st_db_read_size(db, in)
        && st_db_alloc_students(db)
    ))
    {
        fclose(in);
        return false;
    }


    for(int i = 0; i < db->size; i++)
    {
        if(!st_db_read_student(&(db->students[i]), in))
        {
            free(db->students);
            db->size = 0;
            fclose(in);
            return false;
        }
    }
    return true;
}

bool st_db_alloc_students(st_db_t *db)
{
    db->students = calloc(db->size, sizeof(st_student_t));
    if(db->students == NULL)
    {
        st_db_last_error = ERROR_MALLOC;
        return false;
    }
    return true;
}


size_t st_db_size(st_db_t *db)
{
    return db->size;
}

st_student_t st_db_get(st_db_t *db, int i)
{
    return db->students[i];
}

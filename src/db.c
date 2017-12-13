#include "db.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

struct st_db {
    char *filepath;
    size_t size;
    size_t max_size;
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
    FILE * db_file = fopen(db->filepath, "a+");
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
    long tmp;
    if(0 >= fscanf(in, "%li\n", &tmp))
    {
        st_db_last_error = ERROR_EOF;
        return false;
    }
    if(tmp < 0)
    {
        st_db_last_error = ERROR_EOF;
        return false;
    }
    *value = tmp;
    return true;
}
bool st_db_read_birth_year_attribute(unsigned short * value, FILE *in)
{
    int tmp;
    if(0 >= fscanf(in, "%i\n", &tmp))
    {
        st_db_last_error = ERROR_EOF;
        return false;
    }
    if(tmp < 0)
    {
        st_db_last_error = ERROR_EOF;
        return false;
    }
    *value = tmp;
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
    long long tmp;
    if(0 >= fscanf(in, "%lli\n", &tmp))
    {
        db->size = 0;
        return feof(in);
    }
    if(tmp < 0)
    {
        db->size = 0;
        st_db_last_error = ERROR_EOF;
        return false;
    }
    db->size = tmp;
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
    db->max_size = db->size;
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



bool st_db_add(st_db_t *db, st_student_t student)
{

    if(db->size == db->max_size)
    {
        size_t new_allocated_size =
            (db->size + 1) * sizeof(st_student_t);
        st_student_t * temp_students =
        realloc(db->students, new_allocated_size);
        if(temp_students == NULL)
        {
            st_db_last_error = ERROR_MALLOC;
            return false;
        }
        db->max_size++;
        db->students = temp_students;
    }

    db->students[db->size] = student;
    db->size++;
    return true;
}


bool st_db_write_size(st_db_t *db, FILE *out)
{
    if(0 >= fprintf(out, "%zi\n", db->size))
    {
        st_db_last_error = ERROR_WRITING;
        return false;
    }
    return true;
}
bool st_db_write_string_attribute(const char * str, FILE *out)
{
    if(0 >= fprintf(out, "%s\n", str))
    {
        st_db_last_error = ERROR_WRITING;
        return false;
    }
    return true;
}
bool st_db_write_id_attribute(unsigned int id, FILE *out)
{
    if(0 >= fprintf(out, "%u\n", id))
    {
        st_db_last_error = ERROR_WRITING;
        return false;
    }
    return true;
}
bool st_db_write_birth_year_attribute(unsigned short by, FILE *out)
{
    if(0 >= fprintf(out, "%hu\n", by))
    {
        st_db_last_error = ERROR_WRITING;
        return false;
    }
    return true;
}

bool st_db_write_student(st_student_t *student, FILE *out)
{
    return
        st_db_write_string_attribute(student->first_name, out)
    &&  st_db_write_string_attribute(student->last_name, out)
    && st_db_write_id_attribute(student->id, out)
    && st_db_write_birth_year_attribute(student->birth_year, out);
}

bool st_db_save(st_db_t *db)
{
    FILE *out;
    if(!st_db_open_db_file(db, "w", &out))
        return false;

    if(!st_db_write_size(db, out))
        return false;

    for(int i = 0; i < db->size; i++)
    {
        if(!st_db_write_student(& db->students[i], out))
            return false;
    }

    return true;
}

void st_db_remove(st_db_t *db, int to_be_deleted)
{
    for(int i = to_be_deleted; i < db->size - 1; i++)
    {
        db->students[i] = db->students[i+1];
    }
    db->size--;
}

bool st_db_remove_by_id(st_db_t *db, unsigned int id)
{
    for(int i = 0; i < db->size; i++)
    {
        if(db->students[i].id == id)
        {
            st_db_remove(db, i);
            return true;
        }
    }
    st_db_last_error = ERROR_ID_NOT_FOUND;
    return false;
}


void st_db_free(st_db_t *db)
{
    if(db->max_size)
        free(db->students);

    free(db->filepath);
    free(db);
}

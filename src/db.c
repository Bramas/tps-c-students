#include "db.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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


bool st_db_load(st_db_t *db)
{
    FILE *in = fopen(db->filepath, "r");
    if(in == NULL)
    {
        st_db_last_error = ERROR_CANNOT_OPEN_DB_FILE;
        return false;
    }

    fscanf(in, "%zi", &(db->size));
    printf("Taille: %zi\n", db->size);

    if(!st_db_alloc_students(db))
    {
        fclose(in);
        return false;
    }

    for(int i = 0; i < db->size; i++)
    {
        fgets(
            db->students[i].first_name,
            MAX_STUDENT_STRLEN,
            in
        );
        fgets(
            db->students[i].last_name,
            MAX_STUDENT_STRLEN,
            in
        );

        fscanf(in, "%u", &(db->students[i].id));
        fscanf(in, "%hu", &(db->students[i].birth_year));
        printf("%s %s %u %hu\n",
            db->students[i].first_name,
            db->students[i].last_name,
            db->students[i].id,
            db->students[i].birth_year
        );
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
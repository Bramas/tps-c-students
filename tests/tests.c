#include "db.h"
#include <stdio.h>
#include <stdbool.h>


bool test_db_init(void)
{
   if(st_db_init("/tmp")!=NULL)
   {
      fprintf(stderr, "doit retourner null lorsque "
      "le fichier est un dossier\n");
      return false;
   }

   remove("/tmp/students.txt");
   if(st_db_init("/tmp/students.txt")==NULL)
   {
      fprintf(stderr, "doit retourner non-null lorsque le fichier n'existe pas\n");
      return false;
   }
   FILE * test_db_file = fopen("/tmp/students.txt", "r");
   if(test_db_file == NULL)
   {
      fprintf(stderr, "la bdd doit être créer si le fichier"
      " n'extiste pas\n");
      return false;
   }
   fclose(test_db_file);
   if(st_db_init("/tmp/students.txt")==NULL)
   {
      fprintf(stderr, "doit retourner non-null lorsque le fichier existe\n");
      return false;
   }
   return true;
}

bool test_db_load(void)
{
   st_db_t *db = st_db_init("test1_db.txt");
   if(db==NULL)
   {
      fprintf(stderr, "doit retourner non-null lorsque le fichier existe\n");
      return false;
   }
   if(!st_db_load(db))
   {
      fprintf(stderr, "db_load doit retourner true "
      "pour un fichier correctement formaté: test1_db.txt\n");
      return false;
   }

   for(int i = 1; i <= 3; i++)
   {
      char path[40];
      sprintf(path, "test_db_wrong_format_%i.txt", i);

      db = st_db_init(path);
      if(db==NULL)
      {
         fprintf(stderr, "doit retourner non-null lorsque le fichier existe\n");
         return false;
      }

      if(st_db_load(db))
      {
         fprintf(stderr, "db_load doit retourner false"
         " pour un fichier non correctement formaté: %s\n", path);
         return false;
      }
   }
   return true;
}


int main(void)
{
   if(!test_db_init())
   {
      return 1;
   }
   if(!test_db_load())
   {
      return 1;
   }

   puts("all tests are successfull");
}
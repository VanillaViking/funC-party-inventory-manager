#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "database.h"
#include "bstree.h"

char* strdup(const char* str) {
    size_t len = strlen(str) + 1;
    char* new_str = (char*)malloc(len);
    if (new_str) {
        strcpy(new_str, str);
    }
    return new_str;
}


int list_databases(const char *filename, char *db_filenames[MAX_DATABASES]) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening the file");
        return -1;
    }

    char db_name[MAX_NAME_SIZE];
    int lineCount = 0;

    while (lineCount < MAX_DATABASES && fgets(db_name, sizeof(db_name), file) != NULL) {
        db_name[strcspn(db_name, "\n")] = '\0';

        db_filenames[lineCount] = strdup(db_name);

        if (db_filenames[lineCount] == NULL) {
            perror("Error allocating memory for a line");
            break;
        }

        lineCount++;
    }

    fclose(file);
    return lineCount;
}

void add_database(char* filename, int new_db_pin) {
   FILE *db_p = fopen(filename, "w");
   
   /* This will later be used to check the validity of user entered PINs */
   char valid_check[] = "VALID\n";
   fwrite(valid_check, 1, sizeof(valid_check), db_p);
   fclose(db_p);

   encrypt_db(filename, new_db_pin);
}


void encrypt_db(char* filename, int pin) {
   FILE *db_p;
   FILE *temp;
   char db_char;

   db_p = fopen(filename, "r");
   temp = fopen("temp", "w");
   if (db_p == NULL) {
      printf("Read error");
      return;
   }

    while ((db_char = fgetc(db_p)) != EOF) {
        db_char = db_char + pin;
        fputc(db_char, temp);
    }

   fclose(db_p);
   fclose(temp);

   remove(filename);
   rename("temp", filename);

}

void decrypt_db(char* filename, int pin) {
   FILE *db_p;
   FILE *temp;
   char db_char;

   db_p = fopen(filename, "r");
   temp = fopen("temp", "w");

    while ((db_char = fgetc(db_p)) != EOF) {
      db_char = db_char - pin;
      fputc(db_char, temp);
   }

   fclose(db_p);
   fclose(temp);

   remove(filename);
   rename("temp", filename);

}

int attempt_decrypt(char* filename, int pin) {
   FILE *db_p;
   char valid_check[6];

   db_p = fopen(filename, "r");
   fscanf(db_p, "%5s", valid_check);
   fclose(db_p);
   valid_check[5] = '\0';
   
   int i = 0;
   while (i < 5) {
      valid_check[i] = valid_check[i] - pin;
      i++;
   }

   if (strcmp(valid_check, "VALID") == 0) {
      decrypt_db(filename, pin);
      return 1;
   }
   return 0;

}

/**/
void read_from_db(char db_filename[MAX_NAME_SIZE], bstree_t* productTree) {
   FILE *db_p;
   product_t read_product;
   int successful_fields;
   char product_strings[MAX_DESCRIPTION_SIZE + MAX_NAME_SIZE + 1];
   char* title;
   char* description;

    /* memset is required to ensure that the string terminates with \0 
     * regardless of the size */
    memset(product_strings, '\0', MAX_NAME_SIZE + MAX_DESCRIPTION_SIZE + 1);

   db_p = fopen(db_filename, "r");
   if (db_p == NULL) {
      printf("Read error");
      return;
   }

   char valid_check[5];
   /* get rid of PIN validation line*/
   fscanf(db_p, "%5s\n", valid_check);

   do {
      successful_fields = fscanf(db_p, "%d\t%d\t%d\t%d\t%d\t%d\t%lf\t%[^\n]s\n", 
                                     &read_product.id,
                                     &read_product.date_added.day,
                                     &read_product.date_added.month,
                                     &read_product.date_added.year,
                                     &read_product.quantity,
                                     &read_product.category,
                                     &read_product.price_per_unit,
                                     product_strings
                                     );

      if (successful_fields == 8) {
         title = strtok(product_strings, ";");
         description = strtok(NULL, ";");
         strcpy(read_product.title, title);
         strcpy(read_product.description, description);
         insert_node(productTree, product_to_node(read_product, 0));
      }
   } while (successful_fields == 8);
   
   fclose(db_p);

}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "database.h"
#include "bstree.h"


/*******************************************************************************
 * Function to duplicate a string
 * 
 * inputs:
 * - str: The string to dublicate
 * outputs:
 * - a copy of the string
*******************************************************************************/
char* strdup(const char* str) {
    size_t len = strlen(str) + 1;
    char* new_str = (char*)malloc(len);
    if (new_str) {
        strcpy(new_str, str);
    }
    return new_str;
}

/*******************************************************************************
 * Function to check whether a file exists or not
 * 
 * inputs:
 * - filename: The name of the file to check
 * outputs:
 * - int 1 if exists, 0 if not
*******************************************************************************/
int file_exists(const char *filename)
{
    FILE *fp = fopen(filename, "r");
    int is_exist = FALSE;
    if (fp != NULL)
    {
        is_exist = TRUE;
        fclose(fp); 
    }
    return is_exist;
}

/*******************************************************************************
 * Lists all databases that have been created using party inventory manager
 * 
 * inputs:
 * - filename: The file that stores the information of all databases
 * - db_filenamees: A list off ALL Database filenames
 * outputs:
 * - int the number of lines that were read
*******************************************************************************/
int list_databases(const char *filename, char *db_filenames[MAX_DATABASES]) {
   if (!file_exists(filename)) {
      /* create the file if it does not exist */
      FILE *temp = fopen(filename, "a");
      fclose(temp);
   }
    FILE *file = fopen(filename, "r");
    if (file == NULL) { 
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


/*******************************************************************************
 * Adds a database to the list of dataabses
 * 
 * inputs:
 * - filename: The new database filename
 * - new_db_pin: The PIN for the new database
 * outputs:
 * - 
*******************************************************************************/
void add_database(char* filename, int new_db_pin) {
   #ifdef DEBUG
   printf("DEBUG: Adding database %s PIN %d\n", filename, new_db_pin);
   #endif

   FILE *db_p = fopen(filename, "w");
   
   /* This will later be used to check the validity of user entered PINs */
   char valid_check[] = "VALID";
   fprintf(db_p, "%s\n", valid_check);
   fclose(db_p);

   FILE *db_list = fopen(DB_LIST, "a");
   fprintf(db_list, "%s\n", filename);
   fclose(db_list);
}


/*******************************************************************************
 * Encrypts a file using the caesar cipher
 * 
 * inputs:
 * - filename: The database filename
 * - new_db_pin: The PIN for the database
 * outputs:
 * - 
*******************************************************************************/
void encrypt_db(char* filename, int pin) {
   #ifdef DEBUG
   printf("DEBUG: Encrypt DB %s with PIN %d\n", filename, pin);
   #endif
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


/*******************************************************************************
 * Decrypts a file that is encrypted using caesar cipher. It is recommended to
 * call attempt_decrypt first to check if the PIN is correct.
 * 
 * inputs:
 * - filename: The database filename
 * - new_db_pin: The PIN for the database
 * outputs:
 * - 
*******************************************************************************/
void decrypt_db(char* filename, int pin) {
   #ifdef DEBUG
   printf("DEBUG: Decrypt DB %s with PIN %d\n", filename, pin);
   #endif

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

/*******************************************************************************
 * Checks if the given PIN is correct 
 * call attempt_decrypt first to check if the PIN is correct.
 * 
 * inputs:
 * - filename: The database filename
 * - new_db_pin: The PIN for the database
 * outputs:
 * - 
*******************************************************************************/
int attempt_decrypt(char* filename, int pin) {
   #ifdef DEBUG
   printf("DEBUG: Attempt to Decrypt DB %s with PIN %d\n", filename, pin);
   #endif

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


/*******************************************************************************
 * Reads all elements from the given file into product tree
 * 
 * 
 * inputs:
 * - filename: The database filename
 * - productTree: The main binary search tree structure
 * outputs:
 * - 
*******************************************************************************/
void read_from_db(char db_filename[MAX_NAME_SIZE], bstree_t* productTree) {
   #ifdef DEBUG
   printf("DEBUG: Read from file %s\n", db_filename);
   #endif

   FILE *db_p;
   product_t read_product;
   int successful_fields;
   char product_strings[MAX_DESCRIPTION_SIZE + MAX_NAME_SIZE + 1];
   char* title;

    /* memset is required to ensure that the string terminates with \0 
     * regardless of the size */
    memset(product_strings, '\0', MAX_NAME_SIZE + MAX_DESCRIPTION_SIZE + 1);

   db_p = fopen(db_filename, "r");
   if (db_p == NULL) {
      printf("Read error");
      return;
   }

   char valid_check[6];
   /* get rid of PIN validation line*/
   fscanf(db_p, "%5s\n", valid_check);
   
   int count = 0;
   do {
      successful_fields = fscanf(db_p, "%d %d %d %d %d %d %lf %[^\n]s\n", 
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
         /* description = strtok(NULL, ";"); */
         strcpy(read_product.title, title);
         /* strcpy(read_product.description, description); */
         insert_node(productTree, product_to_node(read_product));
      }
      count++;
   } while (successful_fields == 8);

   #ifdef DEBUG
   printf("DEBUG: Successfuly read %d Entries\n", count);
   #endif

   fclose(db_p);

}

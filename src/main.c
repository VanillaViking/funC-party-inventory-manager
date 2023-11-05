/*******************************************************************************
 * 48430 Fundamentals of C Programming - Assignment 3
 * Name: Ashwin Rajesh 
 * Student ID: 14259321
 * Name: Benjamin Allen
 * Student ID: 13590777
 * 
*******************************************************************************/

#include <stdio.h> /* printf, scanf, getchar, FILE, fopen, fclose */ 
#include <string.h> /* strncpy, memset */
#include <stdlib.h>
#include "bstree.h"
#include "database.h"
#include "main.h"


/*******************************************************************************
 * Global Application State
*******************************************************************************/
bstree_t productTree;

/*******************************************************************************
 * Main
*******************************************************************************/
int main(void){
   char db_filename[MAX_NAME_SIZE];
   int current_pin;
   
   dbSelect(db_filename, &current_pin);

   mainMenu(db_filename, current_pin);
   return 0;
}


void promptSave(char* db_filename) {
   printf("Save changes? [Y/n]");
   char c[10];

   scanf("%s", c);
   
   if (strcmp(c, "y") == 0 || strcmp(c, "Y") == 0 || strcmp(c, "") == 0) {
      saveToDatabase(db_filename);
   }
}

void quit(char* db_filename, const int current_pin) {

   promptSave(db_filename);
   
   encrypt_db(db_filename, current_pin);
   exit(0);
}


void dbSelect(char db_filename[MAX_NAME_SIZE], int* current_pin) {
   int selection;
   printf("\n-----PARTY INVENTORY MANAGER-----\n");
   printf("[0] New Database\n");

   char *db_filenames[MAX_DATABASES];
   int db_list_len = list_databases(DB_LIST, db_filenames);
   int success;

   do {

      int i;
      for (i = 0; i < db_list_len; i++) {
         printf("[%d] %s\n", i+1, db_filenames[i]);
      }

      printf("Select database to operate: ");
      success = scanf("%d", &selection);
   } while (success != 1 || selection < 0 || selection > db_list_len);
      
   selection--;

   char new_db[MAX_NAME_SIZE];
   char pin_str[50];
   int new_db_pin;
   
   /* New Database */
   if (selection == -1) {
      printf("Enter new database name: ");
      scanf("%19s", new_db);
      /* write name to dbs.txt */
      success = 0;

      do {
         printf("Enter new database PIN (3 digits): ");
         fflush(stdin);
         success = scanf("%s", pin_str);
         new_db_pin = atoi(pin_str);
         if (success != 1 || new_db_pin <= 0 || new_db_pin > 999) printf("\nInvalid PIN, try again\n");
      } while (success != 1 || new_db_pin <= 0 || new_db_pin > 999);

      add_database(new_db, new_db_pin);
      strcpy(db_filename, new_db);
      *current_pin = new_db_pin;

   /* Existing Database */
   } else {
      success = 0;
      int db_pin;
      char pin_str[50];
      strcpy(db_filename, db_filenames[selection]);
      
      do {
         printf("Enter PIN for %s: ", db_filename);
         fflush(stdin);
         success = scanf("%s", pin_str);
         db_pin = atoi(pin_str);
         if (success != 1 || db_pin <= 0 || db_pin > 999) {
            printf("Invalid PIN, try again\n");
         } else {
            if (attempt_decrypt(db_filename, db_pin)) {
               read_from_db(db_filename, &productTree);
               printf("Decryption successful.\n");
               *current_pin = db_pin;
               break;
            } else {
               printf("Decryption unsuccessful.\n");
               success = 0;
               /* currently loops until correct PIN is entered - should be an exit option/wrong database */
            }
         }
      } while (success != 1 || db_pin <= 0 || db_pin > 999);  
   }
   return;
}


/*******************************************************************************
 * This function prints the initial menu with all instructions on how to use
 * this program.
 * inputs:
 * - 
 * outputs:
 * - 
*******************************************************************************/
void mainMenu(char db_filename[MAX_NAME_SIZE], int current_pin) {
   int mainChoice = -1;

   do {
      printf("\n-----MAIN MENU-----\n"
             "0. exit\n"
             "1. product menu\n"
             "2. inventory menu\n"
             "3. database menu\n"
             "Enter your choice>\n");
      
      int valid = scanf("%d", &mainChoice);
      while (valid != 1) {
         getchar(); 
         valid = scanf("%d", &mainChoice);
      }

      switch (mainChoice) {
         case EXIT:
            quit(db_filename, current_pin);
            break;
         case PRODUCT: 
            productMenu(db_filename, current_pin);
            break;
         case INVENTORY: 
            inventoryMenu(db_filename, current_pin);
            break;
         case DATABASE:
            databaseMenu(db_filename, current_pin);
            break;
         default:
            printf("Invalid choice.");
            break;
      }
   } while (mainChoice != 0);
}


/* submenu for product choices */
void productMenu (char db_filename[MAX_NAME_SIZE], int current_pin) {
   int productChoice;

   do {
      printf("\n-----PRODUCT MENU-----\n"
         "0. exit\n"
         "1. add new product\n"
         "2. add existing product\n"
         "3. back\n"
         "Enter your choice>\n");

      int valid = scanf("%d", &productChoice);
      while (valid != 1) {
         getchar(); 
         valid = scanf("%d", &productChoice);
      }

      switch (productChoice) {
         case EXIT:
            quit(db_filename, current_pin);
            break;
         case ADD_NEW: 
            insert_node(&productTree, product_to_node(newProduct(), 23));
            break;
         case ADD_OLD:
            addExistingProduct();
            break;
         case PRODUCT_BACK:
            break;
         default:
            printf("Invalid choice.");
            break;
      }
   } while (productChoice != 3);
}


/* brings up menu of options relating to the inventory */
void inventoryMenu (char db_filename[MAX_NAME_SIZE], int current_pin) {
   int inventoryChoice;
   displayInventory();


   do {   
      printf("\n-----INVENTORY MENU-----\n"
         "0. quit\n"
         "1. display inventory\n" 
         "2. search inventory\n"
         "3. delete item\n"
         "4. edit item\n"
         "5. back\n"
         "Enter your choice>\n");

      int valid = scanf("%d", &inventoryChoice);        
      while (valid != 1) {
         getchar(); 
         valid = scanf("%d", &inventoryChoice);
      }
      
      switch (inventoryChoice) {
         case EXIT:
            quit(db_filename, current_pin);
            break;
         case DISPLAY:
            displayInventory();
            break;
         case SEARCH: 
            searchInventory();
            break;
         case DELETE:
            deleteItem();/*
            displayInventory();*/
            break;
         case EDIT:
            editItem();/*
            displayInventory();*/
            break;
         case INVENTORY_BACK:
            break;
         default:
            printf("Invalid choice.");
            break;
      }
   } while (inventoryChoice != INVENTORY_BACK);
}


/* prints database menu, and user selects between options  */
void databaseMenu (char db_filename[MAX_NAME_SIZE], int current_pin) {
   int databaseChoice;
   
   do {   
      printf("\n-----DATABASE MENU-----\n"
         "0. exit\n"
         "1. save to database\n"
         "2. switch database\n"
         "3. back\n"
         "Enter your choice>\n");

      int valid = scanf("%d", &databaseChoice);
      while (valid != 1) {
         getchar(); 
         valid = scanf("%d", &databaseChoice);
      }
      
      switch (databaseChoice) {
         case EXIT:
            quit(db_filename, current_pin);
            break;
         case SAVE_DB: 
            saveToDatabase(db_filename);
            break;
         case SWITCH_DB: 
            switchDatabase(db_filename, &current_pin);
            break;
         case DB_BACK:
            break;
         default:
            printf("Invalid choice.");
            break;
      }
   } while (databaseChoice != 3);
}


/* create a new product and add to the inventory list */
product_t newProduct () {
   
   int c;
   while ((c = getchar()) != '\n' && c != EOF);

   product_t newproduct;
   printf("Enter product name>\n");
   scanf("%20[^\n]s", newproduct.title);

   printf("Enter date:\n");
   while (TRUE) {
      printf("Enter day>");
      int valid = scanf("%u", &newproduct.date_added.day);
        
      /* clear extraneous characters from input buffer */
      while (valid != 1) {
         getchar(); 
         valid = scanf("%u", &newproduct.date_added.day);
      }

      if (valid == 1 && 
         newproduct.date_added.day > 0 && 
         newproduct.date_added.day <= 31) {
         break;
      }

      printf("Invalid day. ");
   }

   while (TRUE) {
      printf("Enter month>");
      int valid = scanf("%u", &newproduct.date_added.month);

      /* clear extraneous characters from input buffer */
      while (valid != 1) {
         getchar(); 
         valid = scanf("%u", &newproduct.date_added.month);
      }

      if (newproduct.date_added.month > 0 && newproduct.date_added.month <= 12) {
         break;
      }

      printf("Invalid month. ");
   }

   while (TRUE) {
      printf("Enter year>");
      int valid = scanf("%u", &newproduct.date_added.year);
      /* clear extraneous characters from input buffer */
      while (valid != 1) {
         getchar(); 
         valid = scanf("%u", &newproduct.date_added.year);
      }
      if (newproduct.date_added.year >= 2000 && newproduct.date_added.year <= 2030) {
         break;
      }
      printf("Invalid year. ");
   }

   while (TRUE) {
      printf("\nEnter category number>\n"
         "0. speaker\n"
         "1. microphone\n"
         "2. light\n"
         "3. chair\n"
         "4. table\n");
      int valid = scanf("%d", &newproduct.category);
        
      /* clear extraneous characters from input buffer */
      while (valid != 1) {
         getchar(); 
         valid = scanf("%d", &newproduct.category);
      }

      if (valid == 1 && newproduct.category >=0 && newproduct.category <= 4) {
         break;
      }

      printf("Invalid category. ");
   }

   printf("Enter unit price>\n");
   scanf("%lf", &newproduct.price_per_unit);
   
   int validQuant;
   do {printf("Enter quantity>\n");
      
      scanf("%d", &newproduct.quantity);
      if (&newproduct.quantity > 0) {
         break;
      }
   } while (validQuant == FALSE);

   /* 
      id is auto generated 
      current id repeats the same for each item - "...02"
   */
   /*printf("", id)*/
   
   return newproduct;
} 


/* updates an existing product with an additional quantity */
void addExistingProduct() {
   /*int idscan;*/
   printf("Enter ID>\n");
   /*scanf("%d", &idscan);
   goto id ... */
      
   printf("Enter added quantity>\n");
   /*scanf("%d", &newquantity);
   quantity =+ newquantity*/
}


/* displays current inventory list: automatic upon inventoryMenu call */
void displayInventory () {
   printf("\nCURRENT INVENTORY\n");
   printf("|----ID----||---Name---||-Category-||--$Price--||-Quantity-|\n");
   print_from(productTree.root);
}


/* enables user to search for specific item within inventory list */
void searchInventory () {
   char query[MAX_NAME_SIZE]; 

   printf("Enter product name>\n");
   scanf("%s", query);

   printf("\nSEARCH RESULTS\n");
   name_search(productTree.root, query);
   
}


/* enables user to sort and view inventory by either name, price or category */
void deleteItem() {
   int id;
   printf("Enter product ID>\n");
   scanf("%d", &id);


   erase(&productTree, id);
}


/* make changes to pre existing item within inventory */
void editItem () {
   int id;
   printf("Enter product ID>\n");
   scanf("%d", &id);

   node_t* node = tree_find(&productTree, id);
   if (node == NULL) {
      printf("Item not found\n");
      return;
   }

   product_t edited_product = newProduct();
   edited_product.id = id;

   node->data = edited_product;
}


/* encrypts and saves current inventory to chosen database */
void saveToDatabase(char* db_filename) {
   FILE *db_p;
   db_p = fopen(db_filename, "w");

   /* This will later be used to check the validity of user entered PINs */
   fprintf(db_p, "VALID\n");
   
   save_to_database(db_p, productTree.root);

   fclose(db_p);
}


/* decrypts and prints selected database to inventory */
void switchDatabase(char db_filename[MAX_NAME_SIZE], int* current_pin) {
   promptSave(db_filename);
   
   /* reset tree */
   productTree.root = NULL;
   productTree.size = 0;

   dbSelect(db_filename, current_pin);
   
}


/*******************************************************************************
 * This function prompts the user to enter information about the employee to 
 * add, and then pushes the new employee to employeelist
 * 
 * inputs:
 * - employeelist: the list of employees
 * - employee_len: number of employees in the list
 * outputs:
 * - none
*******************************************************************************/

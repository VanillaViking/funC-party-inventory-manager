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

   /* product_t test1 = {0, "jbl partybox 1000", "speaker great for family gatherings", {23,10,2023}, 4, SPEAKER, 500}; */
   /* product_t test2 = {0, "jbl partybox 2000", "speaker great for family gatherings", {22,10,2023}, 4, SPEAKER, 500}; */
   /* product_t test3 = {0, "jbl partybox 3000", "speaker great for family gatherings", {23,10,2024}, 4, SPEAKER, 500}; */
   /* product_t test4 = {0, "jbl partybox 4000", "speaker great for family gatherings", {20,10,2023}, 4, SPEAKER, 500}; */
   /* product_t test5 = {0, "jbl partybox 5000", "speaker great for family gatherings", {25,10,2023}, 4, SPEAKER, 500}; */

   /* node_t* test_node1 = product_to_node(test1, 3); */
   /* node_t* test_node2 = product_to_node(test2, 4); */
   /* node_t* test_node3 = product_to_node(test3, 5); */
   /* node_t* test_node4 = product_to_node(test4, 6); */
   /* node_t* test_node5 = product_to_node(test5, 7); */

   /* insert_node(&productTree, test_node1); */
   /* insert_node(&productTree, test_node2); */
   /* insert_node(&productTree, test_node3); */
   /* insert_node(&productTree, test_node4); */
   /* insert_node(&productTree, test_node5); */
   
   /* saveToDatabase(); */
   /* displayInventory(); */

   /* encryptDb(234); */
   /* decryptDb(234); */
   
   /* encrypt_db("database.pim", 343); */

   dbSelect(db_filename, &current_pin);

   mainMenu(db_filename, current_pin);
   return 0;
}


/**/
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
   int new_db_pin;
   
   /* New Database */
   if (selection == -1) {
      printf("Enter new database name: ");
      scanf("%19s", new_db);
      success = 0;

      do {
         printf("Enter new database PIN: ");
         success = scanf("%d", &new_db_pin);
         if (success != 1 || new_db_pin < 0 || new_db_pin > 999) printf("Invalid PIN, try again\n");
      } while (success != 1 || new_db_pin < 0 || new_db_pin > 999);

      add_database(new_db, new_db_pin);
      strcpy(db_filename, new_db);
      *current_pin = new_db_pin;

   /* Existing Database */
   } else {
      success = 0;
      int db_pin;
      strcpy(db_filename, db_filenames[selection]);
      
      do {
         printf("Enter PIN for %s: ", db_filename);
         success = scanf("%d", &db_pin);
         if (success != 1 || db_pin < 0 || db_pin > 999) printf("Invalid PIN, try again\n");
         else {
            if (attempt_decrypt(db_filename, db_pin)) {
               read_from_db(db_filename, &productTree);
               printf("Decryption successful.\n");
               break;
            } else {
               printf("Decryption unsuccessful.\n");
            }
         }
      } while (success != 1 || db_pin < 0 || db_pin > 999);
      
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
   int mainChoice;

   do {
      printf("\n-----MAIN MENU-----\n"
             "0. exit\n"
             "1. product menu\n"
             "2. inventory menu\n"
             "3. database menu\n"
             "Enter your choice>\n");

      scanf("%d", &mainChoice);

      switch (mainChoice) {
         case EXIT:
            return;
            break;
         case PRODUCT: 
            productMenu();
            break;
         case INVENTORY: 
            inventoryMenu();
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


/**/
void productMenu (void) {
   int productChoice;

   do {
      printf("\n-----PRODUCT MENU-----\n"
         "0. exit\n"
         "1. add product\n"
         "2. back\n"
         "Enter your choice>\n");

      int valid = scanf("%d", &productChoice);

      while (valid != 1) {
         getchar(); 
         valid = scanf("%d", &productChoice);
      }

      switch (productChoice) {
         case EXIT:
            exit(0);
            break;
         case ADD: 
            addProduct();
            break;
         case PRODUCT_BACK:
            break;
         default:
            printf("Invalid choice.");
            break;
      }
   } while (productChoice != 2);
}


/**/
void inventoryMenu (void) {
   int inventoryChoice;

   do {   
      printf("\n-----INVENTORY MENU-----\n"
         "0. back\n"
         "1. display inventory\n"
         "2. search inventory\n"
         "3. sort inventory\n"
         "4. edit item\n"
         "5. back\n"
         "Enter your choice>\n");

      scanf("%d", &inventoryChoice);
      
      switch (inventoryChoice) {
         case EXIT:
            exit(0);
            break;
         case DISPLAY: 
            displayInventory();
            break;
         case SEARCH: 
            searchInventory();
            displayInventory();
            break;
         case SORT:
            sortInventory();
            displayInventory();
            break;
         case EDIT:
            editItem();
            break;
         case INVENTORY_BACK:
            break;
         default:
            printf("Invalid choice.");
            break;
      }

   } while (inventoryChoice != 5);
}


/**/
void databaseMenu (char db_filename[MAX_NAME_SIZE], int current_pin) {   
   int databaseChoice;

   do {   
      printf("\n-----DATABASE MENU-----\n"
         "0. exit\n"
         "1. save to database\n"
         "3. encrypt list\n"
         "4. decrypt list\n"
         "5. back\n"
         "Enter your choice>\n");

      scanf("%d", &databaseChoice);
      
      switch (databaseChoice) {
         case EXIT:
            exit(0);
            break;
         case SAVE_DB: 
            saveToDatabase(db_filename, current_pin);
            break;
         case DB_BACK:
            break;
         default:
            printf("Invalid choice.");
            break;
      }

   } while (databaseChoice != 5);
    
}



/**/
void addProduct () {

   int isthisnew;
   printf("Is this a new product?\n"
      "0 - NO\n"
      "1 - YES\n");
   scanf("%d", &isthisnew);

   if (isthisnew) {  
      product_t newproduct;
   
      printf("Enter product name>\n");
      scanf("%s", newproduct.title);

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
            valid = scanf("%u", &newproduct.date_added.day);
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
            valid = scanf("%u", &newproduct.date_added.day);
        }

        if (newproduct.date_added.year > 2000 && newproduct.date_added.year <= 2030) {
            break;
        }

        printf("Invalid year. ");
    }

      printf("Enter category>\n");
      scanf("%d", &newproduct.category);
   
      printf("Enter unit price>\n");
      scanf("%lf", &newproduct.price_per_unit);
   
      printf("Enter quantity>\n");

      /* 
         enter quantity
      
         id is auto generated 
      */

   } else {
      printf("Enter ID>\n");
      /*scanf("");*/
      
      printf("Enter quantity>\n");
      /*scanf("");*/
   }
}


/**/
void displayInventory () {
   print_from(productTree.root);
}


/**/
void searchInventory () {
   
}


/**/
void sortInventory () {
   
}


/**/
void editItem () {
   
}


/**/
void saveToDatabase(char* db_filename, int pin) {
   FILE *db_p;
   db_p = fopen(db_filename, "w");

   /* This will later be used to check the validity of user entered PINs */
   char valid_check[] = "VALID\n";
   fwrite(valid_check, 1, sizeof(valid_check), db_p);
   
   save_to_database(db_p, productTree.root);

   fclose(db_p);

   

   encrypt_db(db_filename, pin);
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

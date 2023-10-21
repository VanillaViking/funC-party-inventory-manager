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
#include "main.h"


/*******************************************************************************
 * Global Application State
*******************************************************************************/
bstree_t productTree;
char* dbFileName = "database.pim";

/*******************************************************************************
 * Main
*******************************************************************************/

int main(void){

   product_t test1 = {0, "jbl partybox 1000", "speaker great for family gatherings", {23,10,2023}, 4, SPEAKER, 500};
   product_t test2 = {0, "jbl partybox 2000", "speaker great for family gatherings", {22,10,2023}, 4, SPEAKER, 500};
   product_t test3 = {0, "jbl partybox 3000", "speaker great for family gatherings", {23,10,2024}, 4, SPEAKER, 500};
   product_t test4 = {0, "jbl partybox 4000", "speaker great for family gatherings", {20,10,2023}, 4, SPEAKER, 500};
   product_t test5 = {0, "jbl partybox 5000", "speaker great for family gatherings", {25,10,2023}, 4, SPEAKER, 500};

   node_t* test_node1 = product_to_node(test1, 3);
   node_t* test_node2 = product_to_node(test2, 4);
   node_t* test_node3 = product_to_node(test3, 5);
   node_t* test_node4 = product_to_node(test4, 6);
   node_t* test_node5 = product_to_node(test5, 7);

   insert_node(&productTree, test_node1);
   insert_node(&productTree, test_node2);
   insert_node(&productTree, test_node3);
   insert_node(&productTree, test_node4);
   insert_node(&productTree, test_node5);
   
   readFromDatabase();
   displayInventory();


   dbSelect();

   mainMenu();
   return 0;
}


/**/
void dbSelect(void) {
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
void mainMenu(void) {
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
            databaseMenu();
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
void databaseMenu (void) {   
   int databaseChoice;

   do {   
      printf("\n-----DATABASE MENU-----\n"
         "0. exit\n"
         "1. save to database\n"
         "2. read from database\n"
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
            saveToDatabase();
            break;
         case READ_DB: 
            readFromDatabase();
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
void saveToDatabase () {
   FILE *db_p;
   db_p = fopen(dbFileName, "w");
   
   save_to_database(db_p, productTree.root);

   fclose(db_p);
}


/**/
void readFromDatabase () {
   FILE *db_p;
   product_t read_product;
   int successful_fields;
   char product_strings[MAX_DESCRIPTION_SIZE + MAX_NAME_SIZE + 1];
   char* title;
   char* description;

    /* memset is required to ensure that the string terminates with \0 
     * regardless of the size */
    memset(product_strings, '\0', MAX_NAME_SIZE + MAX_DESCRIPTION_SIZE + 1);

   db_p = fopen(dbFileName, "r");
   if (db_p == NULL) {
      printf("Read error");
      return;
   }


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
         insert_node(&productTree, product_to_node(read_product, 0));
      }
   } while (successful_fields == 8);


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

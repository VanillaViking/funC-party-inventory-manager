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
#include <math.h>
#include "main.h"
#include "bstree.h"

/*******************************************************************************
 * Main
*******************************************************************************/
int main(void){
   /*char dbFileName[] = "database";*/
   int choice;
   
   bstree_t product_tree = {0, NULL};

   product_t test1 = {0, "jbl partybox 1000", "speaker great for family gatherings", {23,10,2023}, 4, "Speakers", 500};
   product_t test2 = {0, "jbl partybox 2000", "speaker great for family gatherings", {22,10,2023}, 4, "Speakers", 500};
   product_t test3 = {0, "jbl partybox 3000", "speaker great for family gatherings", {23,10,2024}, 4, "Speakers", 500};
   product_t test4 = {0, "jbl partybox 4000", "speaker great for family gatherings", {20,10,2023}, 4, "Speakers", 500};
   product_t test5 = {0, "jbl partybox 5000", "speaker great for family gatherings", {25,10,2023}, 4, "Speakers", 500};

   node_t* test_node1 = product_to_node(test1, 3);
   node_t* test_node2 = product_to_node(test2, 4);
   node_t* test_node3 = product_to_node(test3, 5);
   node_t* test_node4 = product_to_node(test4, 6);
   node_t* test_node5 = product_to_node(test5, 7);

   insert_node(&product_tree, test_node1);
   insert_node(&product_tree, test_node2);
   insert_node(&product_tree, test_node3);
   insert_node(&product_tree, test_node4);
   insert_node(&product_tree, test_node5);

   erase(&product_tree, test_node1->key);

   print_from(product_tree.root);

   tree_find(&product_tree, 2023102551);
   


   while (TRUE) {
      printMainMenu();
      printf("Enter your choice>\n");
      scanf("%d", &choice);

      switch (choice) {
         case ADD_PRODUCT:
            break;
         case DELETE_PRODUCT:
            break;
         case DISPLAY_INVENTORY:
            break;
         case SEARCH_INVENTORY:
            break;
         case SORT:
            break;
         case SAVE_TO_DB:
            break;
         case READ_FROM_DB:
            break;
         case EXIT:
            return 0;
            break;
         case PRINT_MENU:
            break;
         default:
            printf("Invalid choice.");
            break;
      }
   }
}

/*******************************************************************************
 * This function prints the initial menu with all instructions on how to use
 * this program.
 * inputs:
 * - none
 * outputs:
 * - none
*******************************************************************************/
void printMainMenu(void) {
    printf("\n"
         "0. exit\n"
         "1. add product\n"
         "2. delete product\n"
         "3. display inventory\n"
         "4. search inventory\n"
         "5. sort inventory\n");
}


void printProductMenu (void) {
    printf("\n"
         "0. back\n");
}


void printInventoryMenu (void) {
    printf("\n"
         "0. back\n"
         "1. \n");
}


void printDatabaseMenu (void) {
    printf("\n"
         "0. back\n"
         "1. save to database\n"
         "2. read from database\n");
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

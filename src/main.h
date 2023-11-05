#ifndef MAIN
#define MAIN

#include <stdio.h>
#define DB_LIST "dbs.txt"
#define TRUE 1
#define FALSE 0
#define MAX_NAME_SIZE 20
#define MAX_DESCRIPTION_SIZE 120
#define MAX_CATEGORY_SIZE 20
/*******************************************************************************
 * List structs
*******************************************************************************/
enum mainChoice {
    EXIT,
    PRODUCT,
    INVENTORY,
    DATABASE,
};

enum productChoice {
    PRODUCT_EXIT,
    ADD_NEW,
    ADD_OLD,
    PRODUCT_BACK,
};

enum inventoryChoice {
    INVENTORY_EXIT,
    DISPLAY,
    SEARCH,
    DELETE,
    EDIT,
    INVENTORY_BACK,
};

enum databaseChoice {
    DB_EXIT,
    SAVE_DB,
    SWITCH_DB,
    DB_BACK,
};

enum Category {
    SPEAKER,
    MICROPHONE,
    LIGHT,
    CHAIR,
    TABLE,
};

typedef struct {
    int day;
    int month;
    int year;
} date_t;

typedef struct {
    int id;
    char title[MAX_NAME_SIZE];
    char description[MAX_DESCRIPTION_SIZE];
    date_t date_added;
    int quantity;
    int category;
    double price_per_unit;
} product_t;


/*******************************************************************************
 * Function prototypes 
*******************************************************************************/
void quit(char* db_filename, const int current_pin);
void dbSelect(char db_filename[MAX_NAME_SIZE], int* current_pin);
void mainMenu(char db_filename[MAX_NAME_SIZE], int current_pin);
void productMenu(char db_filename[MAX_NAME_SIZE], int current_pin);
void inventoryMenu(char db_filename[MAX_NAME_SIZE], int current_pin);
void databaseMenu (char db_filename[MAX_NAME_SIZE], int current_pin);
product_t newProduct();
void addExistingProduct(/* id */);
void displayInventory();
void searchInventory();
void deleteItem();
void editItem();
void saveToDatabase(char* db_filename);
void switchDatabase(char db_filename[MAX_NAME_SIZE], int* current_pin);

#endif

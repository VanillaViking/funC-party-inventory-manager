#ifndef MAIN
#define MAIN

/*******************************************************************************
 * List header files - do NOT use any other header files. Note that stdlib.h is
 * included in case you want to use any of the functions in there. However the
 * task can be achieved with stdio.h and string.h only.
*******************************************************************************/
/*******************************************************************************
 * List preprocessing directives - you may define your own.
*******************************************************************************/
#define TRUE 1
#define FALSE 0
#define MAX_NAME_SIZE 20
#define MAX_DESCRIPTION_SIZE 120
#define MAX_CATEGORY_SIZE 20
/*******************************************************************************
 * List structs - you may define struct date_time and struct flight only. Each
 * struct definition should have only the fields mentioned in the assignment
 * description.
*******************************************************************************/
enum mainChoice {
    EXIT,
    PRODUCT,
    INVENTORY,
    DATABASE,
};

enum productChoice {
    PRODUCT_EXIT,
    ADD,
    PRODUCT_BACK,
};

enum inventoryChoice {
    INVENTORY_EXIT,
    DISPLAY,
    SEARCH,
    SORT,
    EDIT,
    INVENTORY_BACK,
};

enum databaseChoice {
    DB_EXIT,
    SAVE_DB,
    READ_DB,
    DB_BACK,
};

enum Category {
    SPEAKER,
    MICROPHONE,
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
 * Function prototypes - do NOT change the given prototypes. However you may
 * define your own functions if required.
*******************************************************************************/
void dbSelect(void);
void mainMenu(void);
void productMenu(void);
void inventoryMenu(void);
void databaseMenu(void);
void addProduct();
void displayInventory();
void searchInventory();
void sortInventory();
void editItem();
void saveToDatabase();
void readFromDatabase();
void deleteItem();

#endif

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
enum Choice {
    EXIT,
    ADD_PRODUCT,
    DELETE_PRODUCT,
    DISPLAY_INVENTORY,
    SEARCH_INVENTORY,
    SORT,
    SAVE_TO_DB,
    READ_FROM_DB,
    PRINT_MENU,
};

enum Category {
    SPEAKER
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
    char category[MAX_CATEGORY_SIZE];
    double price_per_unit;
} product_t;

/*******************************************************************************
 * Function prototypes - do NOT change the given prototypes. However you may
 * define your own functions if required.
*******************************************************************************/
void printMainMenu(void);
void addProduct();
int deleteProduct();
void displayInventory();
void searchInventory();
void sortInventory();
void saveToDatabase();
int readFromDatabase();

#endif

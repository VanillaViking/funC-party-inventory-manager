#ifndef DB
#define DB

#define MAX_DATABASES 10
#include "bstree.h"

int list_databases(const char* filename, char *db_filenames[MAX_DATABASES]);
void add_database(char* filename, int new_db_pin);
void encrypt_db(char* filename, int pin);
void decrypt_db(char* filename, int pin);
int attempt_decrypt(char* filename, int pin);
void read_from_db(char db_filename[MAX_NAME_SIZE], bstree_t* productTree);

#endif

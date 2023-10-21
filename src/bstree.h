#ifndef BST
#define BST

#include <stdio.h>
#include <stdlib.h>
#include "main.h"

typedef struct node {
    int key;
    product_t data;
    struct node* parent;
    struct node* right;
    struct node* left;

} node_t;

typedef struct {
    int size;
    node_t* root;
} bstree_t;


node_t* product_to_node(product_t data, int random_seed);
void insert_node(bstree_t* tree, node_t* new_node);
node_t* tree_find(bstree_t* tree, int node_key);
/* node_t* tree_min(bstree_t* tree); */
node_t* min(node_t* node);
node_t* successor(bstree_t* tree, int node_key);
void erase(bstree_t* tree, int node_key);

void print_from(const node_t* node);
void save_to_database(FILE* db_p, const node_t* node);

#endif

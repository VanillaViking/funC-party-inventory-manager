#include "bstree.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*******************************************************************************
 * provide a secure random integer from the given file. 
 * 
 * 
 * inputs:
 * - filename: The database filename
 * - productTree: The main binary search tree structure
 * outputs:
 * - int: randomly genereated integer 
*******************************************************************************/
static int randomize_helper(FILE *in)
{
    unsigned int  seed;

    if (!in)
        return -1;

    if (fread(&seed, sizeof seed, 1, in) == 1) {
        fclose(in);
        srand(seed);
        return 0;
    }

    fclose(in);
    return -1;
}

/*******************************************************************************
 * provide a secure random integer from the given file. 
 * 
 * 
 * inputs:
 * - filename: The database filename
 * - productTree: The main binary search tree structure
 * outputs:
 * - int: randomly genereated integer 
*******************************************************************************/
static int randomize(void)
{
    if (!randomize_helper(fopen("/dev/urandom", "r")))
        return 0;
    if (!randomize_helper(fopen("/dev/arandom", "r")))
        return 0;
    if (!randomize_helper(fopen("/dev/random", "r")))
        return 0;

    /* No randomness sources found. */
    return -1;
}

/*******************************************************************************
 * Converts a product to a binary search tree node
 * 
 * 
 * inputs:
 * - product_t: The product type to be converted to a node
 * - productTree: The main binary search tree structure
 * outputs:
 * - int: randomly genereated integer 
*******************************************************************************/
node_t* product_to_node(product_t data) {
   if (randomize() == -1) printf("WARNING: no randomness sources found.\n");

   node_t* new_node = malloc(sizeof(node_t));

   /* the tree key is the date along with a random number. This is so that there is less chance of duplicate keys*/
   new_node->key = (data.date_added.year * 1000000) + (data.date_added.month * 10000) + (data.date_added.day * 100) + (rand() % 100);
   data.id = new_node->key;

   #ifdef DEBUG
   printf("DEBUG: New node key: %d\n", new_node->key);
   #endif

   new_node->data = data;
   new_node->parent = NULL;
   new_node->right = NULL;
   new_node->left = NULL;

   return new_node;
}


/*******************************************************************************
 * Inserts a new node into the tree
 * 
 * 
 * inputs:
 * - bstree_t: The main product tree of the app
 * - node_t: The node to be added into the trere
 * outputs:
 * - 
*******************************************************************************/
void insert_node(bstree_t* tree, node_t* new_node) {
   node_t* node = tree->root;
   node_t* parent_node = tree->root;
   int went_right;

   if (node == NULL) {
#ifdef DEBUG
      printf("DEBUG: Root is null. Creating new root.\n");
#endif
      tree->root = new_node;
      tree->size++;
      return;
   }

   while (node != NULL) {
      parent_node = node;

      if (new_node->key > node->key) {
         node = node->right;
         went_right = TRUE;
      } else {
         node = node->left;
         went_right = FALSE;
      }
   }

   new_node->parent = parent_node;
   if (went_right) {
      parent_node->right = new_node;
   } else {
      parent_node->left = new_node;
   }

   tree->size++;
   return;

}

/*******************************************************************************
 * Saves the entire product tree to the database file
 * uses pre-order traversal to preserve the structure of the tree
 * 
 * inputs:
 * - db_p: The pointer to the file stream of the database
 * - node: the root node
 * outputs:
 * - 
*******************************************************************************/
void save_to_database(FILE* db_p, const node_t* node) {
   if (node == NULL) return;

   #ifdef DEBUG
   printf("DEBUG: SAVING %d %d %d %d %d %d %lf %s;%s\n", 
           node->data.id,
           node->data.date_added.day,
           node->data.date_added.month,
           node->data.date_added.year,
           node->data.quantity,
           node->data.category,
           node->data.price_per_unit,
           node->data.title,
           node->data.description
          );
   #endif

   fprintf(db_p, "%d %d %d %d %d %d %lf %s;%s\n",
           node->data.id,
           node->data.date_added.day,
           node->data.date_added.month,
           node->data.date_added.year,
           node->data.quantity,
           node->data.category,
           node->data.price_per_unit,
           node->data.title,
           node->data.description
           );

   save_to_database(db_p, node->left);
   save_to_database(db_p, node->right);
}

/*******************************************************************************
 * Prints a single node
 * 
 * 
 * inputs:
 * - node: The node to print
 * outputs:
 * - 
*******************************************************************************/
void print_node(const node_t* node) {
   if (node == NULL) return;

   char category_str[50];
   switch (node->data.category) {
      case 0:
         strcpy(category_str, "Speaker");
         break;
      case 1:
         strcpy(category_str, "Microphone");
         break;
      case 2:
         strcpy(category_str, "Light");
         break;
      case 3:
         strcpy(category_str, "Chair");
         break;
      case 4:
         strcpy(category_str, "Table");
         break;
   }

   printf("|%-10d|", node->key);
   printf("|%-10.10s|", node->data.title);
   printf("|%-10s|", category_str);
   printf("|$%-9.2lf|", node->data.price_per_unit);
   printf("|%-10d|\n", node->data.quantity);
}


/*******************************************************************************
 * Print all the sub-nodes from the given node
 * 
 * 
 * inputs:
 * - node: The node to start from
 * outputs:
 * - 
*******************************************************************************/
void print_from(const node_t* node) {
   if (node == NULL) return;

   print_from(node->left);
   print_node(node);
   print_from(node->right);
}

/*******************************************************************************
 * Searches the entire tree for the matching names
 * 
 * 
 * inputs:
 * - node: The node to start from
 * outputs:
 * - 
*******************************************************************************/
void name_search(const node_t* node, char query[MAX_NAME_SIZE]) {
   if (node == NULL) return;
   
   name_search(node->left, query);
   if (strstr(node->data.title, query) != NULL) {
      print_node(node);
   }
   name_search(node->right, query);
}

char category_str[50];

/*******************************************************************************
 * Find the given key in the tree
 * 
 * 
 * inputs:
 * - tree: The main product tree to search in
 * - query_key: The key to search for
 * outputs:
 * - node_t found node or NULL if not found 
*******************************************************************************/
node_t* tree_find(bstree_t* tree, int query_key) {
   node_t* node = tree->root;

   while (node != NULL) {
      if (node->key < query_key) {
         node = node->right;
      } else if (node->key > query_key) {
         node = node->left;
      } else {
         return node;
      }
   }
   return node;
}

/*******************************************************************************
 * Find the minimum key in the tree
 * 
 * inputs:
 * - node: the root of the tree
 * outputs:
 * - node_t found node or NULL if not found
*******************************************************************************/
node_t* min(node_t* node) {
   while(node->left != NULL) {
      node = node->left;
   }
   return node;
}

/*******************************************************************************
 * Find the successor of the given node key
 * 
 * inputs:
 * - tree: the main product tree
 * - node_key: the key to find the successor for
 * outputs:
 * - node_t found node or NULL if not found
*******************************************************************************/
node_t* successor(bstree_t* tree, int node_key) {
   node_t* node = tree_find(tree, node_key);
   
   if (node->right != NULL) {
      return min(node->right);
   }

   while (node != NULL) {
      if (node->key > node_key) return node;
      node = node->parent;
   }

   return NULL;
}

/*******************************************************************************
 * Delete the given node from tree
 * 
 * inputs:
 * - tree: the main product tree
 * - node_key: the key to delete
 * outputs:
*******************************************************************************/
void erase(bstree_t* tree, int node_key) {
   node_t* node_to_remove = tree_find(tree, node_key);
   if (node_to_remove->key != node_key) return;

   /* Reference to the pointer between the node to be removed, and it's parent */
   node_t** parent_to_node;
   if (node_to_remove->parent == NULL) {
      parent_to_node = &tree->root;
   } else if (node_to_remove->parent->right->key == node_to_remove->key) {
      parent_to_node = &node_to_remove->parent->right;
   } else {
      parent_to_node = &node_to_remove->parent->left;
   }


   /* no children */
   if (node_to_remove->right == NULL && node_to_remove->left == NULL) {
      *parent_to_node = NULL;
   }

   /* no right child */
   else if (node_to_remove->right == NULL && node_to_remove->left != NULL) {
      node_to_remove->left->parent = node_to_remove->parent;
      *parent_to_node = node_to_remove->left;
   } 

   /* no left child */
   else if (node_to_remove->right != NULL && node_to_remove->left == NULL) {
      node_to_remove->right->parent = node_to_remove->parent;
      *parent_to_node = node_to_remove->right;
   }

   /* both children */
   else {
      node_t* s = successor(tree, node_key);

      if (s->parent != node_to_remove) {
         s->parent->left = s->right;
         if (s->right != NULL) s->right->parent = s->parent;
         s->right = NULL;
      }

      s->parent = node_to_remove->parent;
      *parent_to_node = s;

      s->left = node_to_remove->left;
      s->left->parent = s;

      if (s != node_to_remove->right) {
         s->right = node_to_remove->right;
         node_to_remove->right->parent = s;
      }

   }
   
   /* freedom, at last! */
   free(node_to_remove);
   tree->size--;
   return;
}

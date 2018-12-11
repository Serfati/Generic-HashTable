#ifndef LIST_H
#define LIST_H

#include "Defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * Self-referential linked data structure.

 * Holds a pointer to some generic data and a pointer to the next
 * node in the sequence.
 */
typedef struct _node* node;

/**
 * Linked list node main structure.
 *
 * Contains a pointer to the head and tail nodes, as well as an integer for
 * describing the length of the list. Also contains a pointer to a function to
 * free node data objects in case they were dynamically allocated.
 */
typedef struct _list* list;

/**
 * Create a list node containing a pointer to "data".
 *
 * @param data A (Element) argument pointing to the node's data.
 * @return nd A (node *) struct argument containing a pointer to "data".
 */
node nodeCreate( Element );

/**
 * Destroy a list node, freeing all associated memory.
 *
 * @param nd A pointer to the list node to be destroyed.
 * @param free_func Pointer to "void function (Element )" that frees "nd->data".
 */
status deleteNode( list  , Element );

status nodeRemove (list , node );
/**
 * Create a list, initialising with a head node and functions.
 *
 * @see list_node_create
 * @param free_func Pointer to "void function (Element )" that frees "node->data"
 * @return A pointer to a list.
 */
list createLinkedList( freeFunction , printFunction  ,equalFunction , copyFunction );

void initLinkedList( list ,freeFunction , printFunction  ,equalFunction , copyFunction );
/**
 * Destroy a list from top to bottom, freeing memory for each node as it goes.
 * @param A pointer to list to be destroyed.
 */

status destroyList(list );
/**
 * Append a list node to a list.
 *
 * @param ls A pointer to the list to append a node to.
 * @param A pointer to the element to be appended to the list.
 */

status appendNode( list , Element );

Element searchInList( list  , Element );

void displayList( list ) ;

void displayNode( list  , Element );

#endif // LIST_H 

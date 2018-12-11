/*
 ============================================================================
 Name        : My Globus Atlas
 Authors     : Avihai Serfati and Ricky Shama {(204520803) , (032496994)}
 Version     : 3.0
 Copyright   : BGU, Read Only
 Description : Generic Linked List ADT in C, Ansi-Style
 ============================================================================
 */

#include "LinkedList.h"

struct _node {
	Element data;
	//	struct _node* next;
	node next;
};


struct _list{
	int length;
	node head;
	node tail;

	// Functions pointers
	freeFunction freef;
	printFunction printf;
	equalFunction compareTo;
	copyFunction copyf;
};


node nodeCreate( Element data )
{
	node nd = (node) malloc(sizeof(struct _node));
	if(nd == NULL){
		printf("Unable to allocate memory.");
		return NULL ;
	}
	nd->data = data;
	nd->next = NULL;
	return nd;
}


list createLinkedList( freeFunction free_func, printFunction print_func ,equalFunction comp_func, copyFunction copy_func)
{
	list ls = (list) malloc(sizeof(struct _list));
	if(ls == NULL){
		printf("Unable to allocate memory.");
		return NULL;
	}
	ls->length = 0;

	// Create/set head and tail nodes
	ls->head = NULL;
	ls->tail = NULL;

	// Pointer to a functions
	ls->freef = free_func;
	ls->printf = print_func;
	ls->compareTo = comp_func;
	ls->copyf = copy_func;

	return ls;
}


void initLinkedList( list ls,freeFunction free_func, printFunction print_func ,equalFunction comp_func, copyFunction copy_func){
	ls = createLinkedList(free_func, print_func, comp_func, copy_func );
	return;
}


status appendNode( list ls , Element data )
{
	if( ls == NULL || data == NULL) return failure;
	node nd = nodeCreate(data);
	// If first item in list, set head
	if (!ls->head)
	{
		ls->head = nd;
		ls->tail = nd;
	}
	else{
		nd->next = ls->head; // Link address part
		ls->head = nd;
	}
	return success;
}


status deleteNode(list ls, Element data)
{
	if (ls == NULL || data == NULL) return 1;
	node curr= ls->head;
	while (curr) {
		if (ls->compareTo(curr->data, data)) break;
		curr = curr->next;
	}
	node tmp = NULL;
	if ( ls == NULL || curr == NULL) return 1;

	if (ls->head == curr) {
		ls->head = ls->head->next;
		//freef needed
        free(curr);
		curr = NULL;
	} else {
		tmp = ls->head;
		while (tmp->next && tmp->next != curr) tmp = tmp->next;
		if (tmp->next) {
			tmp->next = curr->next;
			//freef needed
            free(curr);
			curr = NULL;
			return 0;
		}
	}
	return 1;
}


Element searchInList( list ls , Element data ){
	if( ls == NULL || data == NULL) return NULL;
	node current = ls->head;  // Initialize current
	while (current != NULL)
	{
		if (ls->compareTo(current->data, data) == true)
			return current->data;
		current = current->next;
	}
	return NULL;
}


void displayNode( list ls , Element data )
{
	if( ls == NULL || data == NULL) return;
	ls->printf(data);
}


void displayList ( list ls )
{
	if (ls == NULL) return;
	node nd = ls->head;
	while (nd != NULL)
	{
		displayNode(ls, nd->data);
		nd = nd->next;
	}
}


status destroyList( list ls )
{
	if (ls == NULL) return failure;
	node curr= ls->head;
	while (curr != NULL) {
		deleteNode(ls, curr->data);
		curr = curr->next;
	}
	return success;
}

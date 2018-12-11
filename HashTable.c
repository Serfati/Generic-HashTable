/*
 ============================================================================
 Name        : My Globus Atlas
 Authors     : Avihai Serfati and Ricky Shama {(204520803) , (032496994)}
 Version     : 3.0
 Copyright   : BGU, Read Only
 Description : Generic Hash Table ADT in C, Ansi-Style
 ============================================================================
 */

#include "HashTable.h"
#include "KeyValuePair.h"
#include "LinkedList.h"
#include "Defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


static status printF (Element elem){
	if(elem == NULL)
		return failure;
	displayValue(elem);
	return success;
}


static bool compf( Element key1, Element key2 ){
	if (key1 == NULL || key2 == NULL)
		return false;
	return isEqualKey(key1,key2);
}


static Element copyf( Element toCopy ){
	if(toCopy == NULL)
		return NULL;
	Pair newOne = (Pair)copyPair(toCopy);
	return newOne;
}


static status freef( Element pair ){
	if(pair == NULL)
		return 1;
	destroyKeyValuePair(pair);
	return 0;
}


struct hashTable_s {
	transformIntoNumberFunction transformKeyIntoNumber;
	// key funcs
	copyFunction copyKey;
	freeFunction freeKey;
	printFunction printKey;
	//val funcs
	copyFunction copyValue;
	freeFunction freeValue;
	printFunction printValue;
	//pair
	equalFunction equalKey;

	int hashNumber;
	int num_elements;

	list* list_arr;
};

/*
  ----------------
  Find the slot in hashtable with a function;

  Return value
  ------------
  hashTable int slot

 */
static int hashSlot( hashTable ht ,Element key ){
	int keyTrans = ht->transformKeyIntoNumber(key);
	int slot = keyTrans%ht->hashNumber;
	return slot;
}


/*
  ----------------
  Initialize the hashtable structure instance.

  Return value
  ------------
  hashTable allocating space for the slots.

 */
hashTable createHashTable ( copyFunction copyKey, freeFunction freeKey,printFunction printKey,
		copyFunction copyValue, freeFunction freeValue,printFunction printValue, equalFunction equalKey,
		transformIntoNumberFunction transformKeyIntoNumber, int hashNumber){
	if (hashNumber <= 0 ||copyValue == NULL || copyKey == NULL || printValue == NULL||printKey == NULL|| freeValue == NULL
			||freeKey == NULL || transformKeyIntoNumber == NULL || equalKey == NULL)
		return NULL;
	//mallocs
	hashTable ht = ( hashTable ) malloc(sizeof( struct hashTable_s ));
	ht->hashNumber = hashNumber;
	ht->list_arr = ( list* )malloc( hashNumber*sizeof( list ) );
	if(!(ht->list_arr) || !ht)
		return NULL;

	// init each slot of the HT with blank linkedlist
	int i;
	for (i = 0 ; i < hashNumber ; i++)
		ht->list_arr[i] = createLinkedList( freef, printF, compf, copyf );

	// key functions
	ht->copyKey = copyKey;
	ht->freeKey = freeKey;
	ht->printKey = printKey;
	// value functions
	ht->copyValue = copyValue;
	ht->freeValue = freeValue;
	ht->printValue = printValue;
	// pair functions
	ht->equalKey = equalKey;
	// hash function
	ht->transformKeyIntoNumber = transformKeyIntoNumber;
	ht->num_elements = 0;

	return ht;
}


/*
 -------------------
 Cleans up the dynamically allocated memory regarding the hashtable and chains.

 ht : pointer to hashtable that is to be destroyed

   Returns :
  --------
  failure if error in free memory
  success on success

 */
status destroyHashTable( hashTable ht ) {
	if (ht == NULL)
		return failure;
	for( int i=0; i < ht->hashNumber; i++ )
		destroyList( ht->list_arr[i]);  // Free each list
	destroyList( ht->list_arr); // Free the array of list headers
	return success;
}


/*
  --------------------
  Inserts a new element into the hashtable. Does not check if the element
  already exists.

  ht : pointer to hashtable
  element : pointer to the data item to be stored
  slot : provide slot number if hash is already calculated, else give a negative number

  Returns :
  --------
  failure if error allocating memory for new node.
  success on success

 */
status addToHashTable( hashTable ht, Element key, Element value ) {
	if (ht == NULL || key == NULL || value == NULL) return failure;

	Pair pair = createKeyValuePair( key,value, ht->copyKey, ht->freeKey,
			ht->printKey, ht->copyValue,  ht->freeValue,
			ht->printValue, ht->equalKey );
	if (pair==NULL)
		return failure;
	int i;
	for(i=0; i < ht->hashNumber; i++)
		if (searchInList(ht->list_arr[i] , pair ) != NULL)
			return failure;//the key found  in hashTable
	int slot =  hashSlot(ht, key);

	list ls = ht->list_arr[slot];
	if ( ls  )
		if ( appendNode( ls , pair ) == success ){
			++ ht->num_elements;
			return success;
		}
	return failure;
}


/*
  -----------------
 Check if an element is present in the hashtable or not

 ht : pointer to hashtable
 Element to be searched in the hashtable for existence
 build from key

  Returns :
  --------
  NULL if no matching element is found
  pointer to matching element if found
 */
Element lookupInHashTable( hashTable ht, Element key ){
	if(ht == NULL || key == NULL)
		return NULL;
	Pair toCheck = createKeyValuePair(key, NULL ,ht->copyKey,ht->freeKey,ht->printKey,ht->copyValue,ht->freeValue,ht->printValue,ht->equalKey);
	int slot =  hashSlot(ht, key);
	Element elem = searchInList(ht->list_arr[slot], toCheck);
	if(elem != NULL)
		return getValue(elem);

	destroyKeyValuePair(toCheck);
	return NULL;
}


/*
  ------------------
  Deletes a node corresponding to an element of known slot

  ht : pointer to hashtable
  ht_node : pointer to the linked list node which holds the element.

  failure if error remove the node.
  success on success
 */
status removeFromHashTable( hashTable ht, Element key ){
	if (ht ==NULL || key == NULL ) return failure;
	Pair toCheck =createKeyValuePair(key, NULL ,ht->copyKey,ht->freeKey,ht->printKey,ht->copyValue,ht->freeValue,ht->printValue,ht->equalKey);
	int i;
	for( i=0; i < ht->hashNumber; i++ ){
		Element data = searchInList(ht->list_arr[i],toCheck);
		if (data != NULL){
			deleteNode(ht->list_arr[i] ,data);
			destroyKeyValuePair(toCheck);
			return success;
		}
	}
	return failure;
}


status displayHashElements( hashTable ht ){
	if (ht == NULL)
		return failure;
	int i = 0;
	while (i < ht->hashNumber){
		displayList(ht->list_arr[i]);
		i++;
	}
	return success;
}


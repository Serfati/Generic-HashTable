/*
 ============================================================================
 Name        : My Globus Atlas
 Authors     : Avihai Serfati and Ricky Shama (204520803) (032496994)
 Version     : 3.0
 Copyright   : BGU, Read Only
 Description : Generic key Value Pair ADT in C, Ansi-Style
 ============================================================================
 */

#include "KeyValuePair.h"


struct keyValuePair_t {
	Element value;
	Element key;

	//key func
	copyFunction copyKey;
	freeFunction freeKey;
	printFunction printKey;
	//val func
	copyFunction copyValue;
	freeFunction freeValue;
	printFunction printValue;

	//pair
	equalFunction equalKey;

};


Pair createKeyValuePair(Element key,Element value,copyFunction copyKey, freeFunction freeKey,
		printFunction printKey, copyFunction copyValue, freeFunction freeValue,
		printFunction printValue, equalFunction equalKey)
{
	Pair newPair = (Pair) malloc ( sizeof (struct keyValuePair_t) );
	if(newPair == NULL) {
		printf("Unable to allocate memory.");
		return NULL;
	}

	newPair->key = key;
	newPair->value = value;

	newPair->copyKey=copyKey;
	newPair->freeKey=freeKey;
	newPair->printKey=printKey;

	newPair->copyValue=copyValue;
	newPair->freeValue=freeValue;
	newPair->printValue=printValue;

	newPair->equalKey=equalKey;

	return newPair;
}


status destroyKeyValuePair(Pair pair){
	if(pair == NULL)
		return failure;
	pair->freeKey(pair->key);
	pair->freeValue(pair->value);
	free(pair);
	return success;
}


void displayValue(Pair pair){
	if(pair == NULL || (pair->value) == NULL)
		return;
	pair->printValue(pair->value);
}


void displayKey(Pair pair){
	if(pair == NULL || pair->key == NULL)
		return;
	pair->printKey(pair->key);
}

Element getValue(Pair pair){
	if(pair == NULL || pair->value == NULL)
		return NULL;

	return pair->value;
}

Element getKey(Pair pair){
	if(pair == NULL || (pair->key) == NULL)
		return NULL;

	return pair->key;
}


bool isEqualKey(Pair p1, Pair p2){
	if(p1 == NULL || p2 == NULL)
		return false;

	return p1->equalKey(p1->key, p2->key);
}

////////////////////////////
copyFunction copyPair (Element elem){
	if(elem== NULL)
		return NULL;

	Pair p = (Pair)elem;
	Pair p2 = createKeyValuePair( p->key,p->value,p->copyKey, p->freeKey,
			p->printKey, p->copyValue, p->freeValue, p->printValue, p->equalKey );
	return ( Element ) p2 ;
}

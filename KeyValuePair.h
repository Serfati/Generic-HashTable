#ifndef KEYVALPAIR_H
#define KEYVALPAIR_H

#include "Defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct keyValuePair_t *Pair;
Pair createKeyValuePair( Element,Element,copyFunction copyKey, freeFunction freeKey,
		printFunction printKey, copyFunction copyValue, freeFunction freeValue,
		printFunction printValue, equalFunction equalKey );
//Pair createPair( Element,Element);
status destroyKeyValuePair( Pair );
void displayValue( Pair );
void displayKey( Pair );
Element getValue( Pair );
Element getKey( Pair );
bool isEqualKey( Pair , Pair );

copyFunction copyPair (Element);
freeFunction freePair (Element);
printFunction printPair (Element);
#endif // KEYVALPAIR_H

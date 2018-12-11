# Generic HashTable library in pure C

generic-c-hashmap should be the easiest to use hash map for C possible.

It only knows how to find, put, remove, and iterate over entries.

You don't have make any adjustments at all to the elements to store. If you can find a hash function and an equality comparator for your data type, you can store it in a generic-c-hashmap.

#Hash function
Function to calculate/retrieve entry's hash. E.g.

#HowTo
To create a new hash table:

htable newTable(unsigned long (hashfunc)(void), int (equalsfunc)(void,void), void (clonekeyfunc)(void), void (clonevaluefunc)(void));***

#The Arguments of this function are:

an hash function which receives a key in void* format and returns an unsigned long hash,

an equals functions which receives two keys in void* format and returns 1 if they are equal 0 otherwise

two clone functions(possibly the same function if the key and values are of the same type)first the one for keys and then the one for the values. Both receive void* and return a void* copy of the argument.

Examples of all these functions have been provided for Strings and integers, as seen below.

To delete an hash table:
void deleteHtable(htable hashtable);

To insert a new key-value pair in hash table:
void put(htable hashtable, void key, void value);***

If key already exists value is replaced.

To get value from key:
void get(htable hashtable,void key);**

returns malloced copy of value that should be freed when no longer needed

To check if key exists in hash table:
int contains(htable hashtable,void key);*

Returns 1 if key exists, 0 if it doesn't.

To remove a key-value pair:
void removePair(htable hashtable,void key);*

Provided example required functions for String and Integers:
unsigned long hashString(void voidkey);*
unsigned long hashInt(void voidkey);*
void cloneString(void str);**
void cloneInt(void integer);**
int equalsString(void str1, void str2);**
int equalsInt(void int1, void int2);**



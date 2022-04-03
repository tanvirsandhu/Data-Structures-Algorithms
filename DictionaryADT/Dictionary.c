//Tanvir Sandhu
//November 14, 2021
//CSE 101 - Alex Pang
//Program 3

#include "List.h"
#include "HashTable.h"
#include "Dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Dictionary {
int		slots;				// total number of slots in hash table
int		size;				// number of elements currently in dictionary
ListPtr  *hash_table;	    // hash_table is array of ListPtrs
} Dictionary;			// dictionary is maintained as a hash table.

//TODO: Implement a key comparison function to pass to list

//this function compares the key of a kv pair to the second object and returns 0 if they are the same and -1 if they're not
int dataCompare(void *obj1, void *obj2) {
	  KVPair *obj = (KVPair*)obj1; 
	  if (strcmp(obj->key, obj2) != 0) {
        return -1;
    } else {
        return 0;
    }
}

//Hint: Look at List.h to see what kind of comparison function the list expects

//TODO: Implement all funcitons from headers
//
//mallocs space for dictionary and initializes values. also creates all the lists in each index of the hashtable
//returns pointer to the dictionary
Dictionary *dictionary_create(int hash_table_size, void (*dataPrinter)(void *data), void (*freeData)(KVPair *kvPair)) {
    Dictionary* dict = (Dictionary*)malloc(sizeof(Dictionary));

    dict->slots = hash_table_size;
    dict->size = 0;
    dict->hash_table = (ListPtr*)calloc(hash_table_size, sizeof(ListPtr));
	  
		for (int k = 0; k < hash_table_size; k++) {
				 dict->hash_table[k] = list_create(dataCompare, dataPrinter, (void*)freeData);
		}

    return dict;
}

//frees the space allocated for the dictionary
void dictionary_destroy(Dictionary *d, bool freeData) {
    for (int a = 0; a < d->slots; a++) {
			 if (list_length(d->hash_table[a]) > 0) {
					list_destroy(d->hash_table[a], freeData);
			 }
		}
		free(d->hash_table);
		free(d);
}

//if the dictionary exists, i find the hashed index and if that list exists and the key does not already exist, i add it and increment dict size
bool dictionary_insert(Dictionary *D, KVPair *elem) {
    if (D) {
        unsigned int index = ht_hash(elem->key, D->slots);
        ListPtr list;
        if (list_length(D->hash_table[index]) < 0) {
            return false; 
        }
        if (list_find_element(D->hash_table[index], elem->key) != -1) {
            return false;
        }
        D->size += 1;
        list_append(D->hash_table[index], elem);
        return true;
    }
    return false;
}

//i find the hashed index and check to make sure there is a value in that hash table that can be deleted
//then, i find the element in that list and remove it, returning the removed KVPair
KVPair *dictionary_delete(Dictionary *D, char *key) {
    KVPair* removed;
    unsigned int index = ht_hash(key, D->slots);
    if (list_length(D->hash_table[index]) >= 0) {
        int ind = list_find_element(D->hash_table[index], key); 
        if (ind != -1) {
            removed = list_del_index(D->hash_table[index], ind);
            D->size -= 1;
            return removed;
        }
        return NULL;
    }
    return NULL;
}

//i find the hashed index and check to make sure there is a value in that hash table list to search through
//then, if the element does not exist, i return NULL, otherwise, i return the KVPair that was found
KVPair *dictionary_find(Dictionary *D, char *k) {
    KVPair* found;
    unsigned int index = ht_hash(k, D->slots);
    if (list_length(D->hash_table[index]) >= 0) {
        int ind = list_find_element(D->hash_table[index], k); 
        if (ind == -1) {
            return NULL;
        } else {
            found = list_get_index(D->hash_table[index], ind);
            return found;
        }
        return NULL;
    }  
    return NULL;
}

//goes through the hash table from 0 to the number of hash lists and prints each one
void dictionary_print(Dictionary *D) {
    int i = 0;
    for (i = 0; i < D->slots; i++) {
        if (list_length(D->hash_table[i]) > 0) {
            list_print(D->hash_table[i]);
        }
    }
}

//returns the size of the dictionary
int dictionary_size(Dictionary *D) {
	  return D->size;
}

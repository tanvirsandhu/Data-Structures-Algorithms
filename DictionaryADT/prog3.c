//Tanvir Sandhu
//November 14, 2021
//CSE 101 - Alex Pang
//Program 3

#include "Dictionary.h"
#include "List.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <string.h>

//This is used internally by the output function. You don't need to change this value
#define WORD_BUFFER_SIZE 50

//i create this function to allocate space for a new KVPair and initalize the KVPair
KVPair *createKVPair(char *key, int value) {
	  KVPair *kvp = (KVPair*)malloc(sizeof(KVPair));

	  kvp->key = key;
	  kvp->value = value;

	  return kvp;
}

//prints the KVPair in k:v format
void dataPrinter(void *data) {
	 KVPair *kvp = (KVPair*)data;

	 fprintf(stdout, "%s:%d ", kvp->key, kvp->value);

	 }

//free the data of a kv pair when given one
void freeData(KVPair *data) {
	 free(data);
	 data = NULL;
}

//free the data of a void* when given one
void freeDict(void *data) {
	 free(data);

}

//compares two kvpairs and if they are equal, return 0, otherwise it will return -1 
int dictCompare(void *obj1, void *obj2) {
	  KVPair *obj = (KVPair*)obj1; 
	  if (strcmp(obj->key, obj2) == 0) {
        return 0;
    } else {
        return -1;
		}
}

//compares two KVPairs for key and value to sort the list in order of value and (A-Z) key
//this function is used by the list sort function to compare each kv pair and sort the list based on that
int listCompare(void *obj1, void *obj2) {
	 KVPair *obj = (KVPair*)obj1;
	 KVPair *obj3 = (KVPair*)obj2;

	 if (obj3->value == obj->value) {
			//i had to use strcmp for the keys of each kv pair 
			if (strcmp(obj->key, obj3->key) < 0) {
				 return 1;
			} else if (strcmp(obj->key, obj3->key) > 0) {
				 return -1;
			} else if (strcmp(obj->key, obj3->key) == 0) {
				 return 0;
			}
	 } else if (obj3->value > obj->value) {
			return -1;
	 } else {
			return 1;
	 }
}



 /**
 * @brief Checks if a character is in the char array.
 * 
 * @param ch The character to check
 * @param charArr The ckaracter array to compare against
 * @return true ch is in charArr
 * @return false ch is not in charArr
 */
bool any_char(char ch, char *charArr) {
    while (*charArr != 0) {
        if (ch == *charArr++) {
            return true;
        }
    }
    return false;
}

/**
 * @brief Gets the distance to the closest delimeter.
 * 
 * @param word The string to look through
 * @param delim The delimeter(s) to search for
 * @return uint8_t The number of characters in the word 
 */
uint8_t word_length(char *str, char *delims) {
    int i = 0;
    while (!any_char(str[i], delims) && str[i] != 0) {
        i++;
    }
    return i;
}

/**
 * @brief Prints the output to stdout. Accepts one line of output at a time.
 * 
 * @param wordFreqs A dictionary of words to format according to their frequency
 * @param wordLengths A dictionary of words to format according to their length
 * @param text One output line to format
 */
void printOutput(Dictionary *wordFreqs, Dictionary *wordLengths, char *text) {
    char wordBuffer[WORD_BUFFER_SIZE] = {0};

    while (*text != 0) {
        uint8_t length = word_length(text, " \n");
        assert(length < WORD_BUFFER_SIZE - 1);
        memcpy(wordBuffer, text, length);
        text = text + length;
        wordBuffer[length] = 0;
        KVPair *freq = dictionary_find(wordFreqs, wordBuffer);
        KVPair *len = dictionary_find(wordLengths, wordBuffer);
        if (freq == NULL && len == NULL) {
            printf("%s ", wordBuffer);
        } else {
            printf("<span style=\"");
            if (freq != NULL) {
                uint8_t r = (intptr_t)freq->value * 23;
                uint8_t g = (intptr_t)freq->value * 29;
                uint8_t b = (intptr_t)freq->value * 31;
                printf("color:#%02x%02x%02x;font-weight:bold;", r, g, b);
            }
            if (len != NULL) {
                printf("font-size:%ldpx;", 2 * (intptr_t)len->value);
           }
            printf("\">%s</span> ", wordBuffer);
        }

        if (*text != 0) { // If delimiter is not null byte, then skip over it. 
            text += 1;
        }
    }
    printf("<br/>\n");
}

int main(void) {
    // TODO: Read in stopwords from stdin. Treat spaces as word delimiters.
	  
    // TODO: Read in words from stdin. Treat spaces as word delimiters.
	 
    // TODO: Add each word to freq and length dictionary or update count, if not in stopwords
	 
	  //declaring variables, dictionaries and lists needed for main
	  char *stopWord[4096] = {};
    int stopInd = 0;
    char entryy[100];
    char stopEnd[8] = "====";
    int end = 0;
		char output[4096];
		char word[400];

		Dictionary *dictLen = dictionary_create(100, dataPrinter, freeData);
		Dictionary *dictFreq = dictionary_create(100, dataPrinter, freeData);
		ListPtr len = list_create(listCompare, dataPrinter, freeDict);
		ListPtr freq = list_create(listCompare, dataPrinter, freeDict);

	  //helper function i created to loop through an array of stopWords and check if the current entry in there
		int stopCheck(char *entry) {
			  int x = 0;
			  while (stopWord[x] != 0) {
					 //if the strcmp returns 0, the word is in the stopWord array so it returns 1
				   if (strcmp(stopWord[x], entry) == 0) {
							return 1;
					 } 
					 x+=1;
				}
		}

	  //this loops through each entry from the input file 
    while (fscanf(stdin, "%s", entryy) != EOF) {
        //fprintf(stdout, "%d ", strcmp(entry, stopEnd));
				//because i'm using the input and it kept getting overwritten, i created a strdup
				char *entry = strdup(entryy);
				if (strcmp(entry,stopEnd) == 0) {
					  //i set the int end to 1 to signify that the stopEnd has been reached
            end = 1;
						continue;
        }
				//if the stop end has not been reached yet, i add the current entry to an array of stop words until the end of the stop word section
        if (end != 1) {
            //this means we have not already processed the stop words
						stopWord[stopInd] = entry;
						//fprintf(stdout, "%s ", stopWord[stopInd]);
						stopInd += 1;
        } else if (end == 1) {
					  //if the stop word end has been reached, i go through each entry and check if it is in the stop words using the helper function
					  int x = 0;
						int ch = 0;
					  if (stopCheck(entry) == 1)	{
							 //if the entry is in the stopwords list, we don't read it
							 continue;
						} else {
							 if (dictionary_find(dictFreq, entry) != NULL) {
									//if the key already exists, find it, delete it, increment the freq and add it again to freq dictionary
									KVPair *kvp = dictionary_find(dictFreq, entry);
									kvp->value += 1;
									dictionary_delete(dictFreq, entry);
									dictionary_insert(dictFreq, kvp);
							 } else {
									//if the key does not already exist
									//initialize KVPair, insert to both dictionaries with 1 as freq and correct len, then add to lists for sorting later.
									//fprintf(stdout, "%s ", entry);
									KVPair *kvpFreq = createKVPair(entry, 1);
									int wordLen = (int)word_length(entry, " ");
									KVPair *kvpLen = createKVPair(entry, wordLen);
									dictionary_insert(dictLen, kvpLen);
									dictionary_insert(dictFreq, kvpFreq);

									list_append(len, kvpLen);
									list_append(freq, kvpFreq);
							 }
				   }
       } 	
    } 
		//sorts both frequency and length list with the true bool
		list_sort(freq, true);
		list_sort(len, true);

	  //this loop iterates through the frequency dictionary and list and removes everything except the top 25 KVPairs
		while(list_length(freq) > 25) {
			 KVPair *pair = list_del_index(freq, 0);
			 dictionary_delete(dictFreq, pair->key);
	  }
		//this loop iterates through the length dictionary and list and removes everything except the top 20 KVPairs
	  while(list_length(len) > 20) {
			 KVPair *pair = list_del_index(len, 0);
			 dictionary_delete(dictLen, pair->key);
	  } 
	  
		//to skip past the stop words when printing the formatted output, i seek to the beginning and looped until i hit the separator.
		//once hit, the loops breaks
		fseek(stdin, 0, SEEK_SET);
		while (fscanf(stdin, "%s", word) != EOF) {
			 char *dupe = strdup(word);
			 if (strcmp(dupe, stopEnd) == 0) {
					break;
			 }
		}
		//to skip the next newline, i seek 1 more in the file and then use the output function to format output.
		fseek(stdin, 1, SEEK_CUR);
	  while (fgets(output, 4096, stdin) != NULL) {
				  printOutput(dictFreq, dictLen, output);
	  }
		


    // TODO: Remove everything but top 25 freq words, and everything but top 20 len words
	  
    // Hint: You can try keeping the same KV elements in both dictionary and list.
    //       Give the list a comparator function which takes into account both word frequency and alphabetic order of word.
    //       Sort list once all words have been processed by the dictionary
    //       Then you can remove the ones not needed form the dictionary before passing it in.
}

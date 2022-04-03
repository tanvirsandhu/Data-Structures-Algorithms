Implemented a Dictionary ADT with Hash Tables and produced an application that uses it.
The application reads a document and determines the 25 most common words within that document.
In addition, it determines the 20 longest words in that document.
Ties in frequency or length are decided by the ascending alphabetical order of words.
The output of the application is the same as the input, but the font size and colors of those words will be changed.

The special format of the input is that each word is separated by a space or a new line. However, there is also a list of stop words which will be 
filtered out when calculating word lengths and frequencies. All words from the stop word list will be ignored and not added to the dictionary.All the stop
words are on the very first line of the input. Each word is separated by a space. The line after the stop words should be ignored. Then the full 
text starts. I have coded the hash table to contain 100 slots.

In addition, the program creates and manipulates dicitonaries using the following functions that I implemented:
  -dictionary_create(n, dp, fd) -- returns an empty dictionary with a hash table of n entries.
  -dictionary_size( D ) -- returns the number of elements currently in dictionary D.
  -dictionary_find( D, k ) -- returns the pointer to the node whose key is k, or NULL if k is not found. 
  -dictionary_insert( D, e ) -- inserts element e into the dictionary if an element with the same key does not already exist. 
  -dictionary_delete( D, k) -- deletes element with key k from the dictionary. 
  -dictionary_print( D ) -- prints the dictionary. 
  
Example input is given in test.in.

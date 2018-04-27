/* lookupWord2.cpp
        Illustrate looking up a word in a 2-D array of words.
        This builds off of parse3.cpp, adding the code to lookup 
        a word using the built-in function "strcmp()".

        Input file has:
            But yield who will
            to their 
            separation
        Output (running the program twice) is:
            Enter the word to lookup: their
            separation was found at position 5
            Press enter to continue...

            Enter the word to lookup: zebra
            zebra was not found in the array.
            Press enter to continue...

*/

#include <iostream>
#include <cstring>
#include <fstream>
#include <cassert>
using namespace std;

const int Size = 81;                // 80 characters for the line + 1 for the '\0'
const int MaxNumberOfWords = 34840;    // maximum number of words to be stored

int main()
{
   ifstream inStream;                          // declare an input stream for my use
   char **theWords= (char**)malloc(sizeof(char*)*MaxNumberOfWords);    // Array to store words from input line
   
   for(int i = 0; i < MaxNumberOfWords; i++){
		theWords[i] = (char*)malloc(sizeof(char)*Size);
   }
   
   int wordRow = 0;                            // Row for the current word
   char wordToLookup[ Size];                   // word to lookup
   bool wordWasFound = false;                  // flag to track whether or not word is found
   char c;                                     // stores return character after input
   
   inStream.open( "C:/Users/bushrabaqui/Desktop/Spring 2016/CS 141/Prog#3/dictionaryMax6.txt");
   assert( ! inStream.fail() );  // make sure file open was OK

   // Keep repeating while input from the file yields a word
   while ( inStream >> theWords[ wordRow]) {
      //printf("%s\n", theWords[ wordRow]);
      wordRow++;
   }
   // Prompt for and get the word to be looked up
   cout << "Enter the word to lookup: ";
   cin >> wordToLookup;
   cin.get( c);      // clear the "enter" character from the input buffer.

   // See if the word is found
   // Note that if we didn't know exactly the number of words in the array, 
   // (which could be less than the total number that *could* be stored) 
   // then we would need to initialize each array element to NULL so that
   // string compare wouldn't choke.
   int i;
   for (i=0; i<wordRow; i++)  {
      // See if this word matches
      if ( strcmp( wordToLookup, theWords[ i]) == 0 ){
         wordWasFound = true;
         break;      // quit looking
      }
   }

   if ( wordWasFound ){
      cout << wordToLookup << " was found at position " << i << endl;
   }
   else {
      cout << wordToLookup << " was not found in the array." << endl;
   }

   // Pause output display (for PC use)
   cout << "Press enter to continue...";
   cin.get( c);
   cout << "\nDone.\n";

   
   return (0);
}

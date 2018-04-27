/* ------------------------------------------------ 
 * Project : Decipher
 * Description: This program encodes, decodes, and decodes automatically given string from user. Encodes and decodes using
                given transposition value. Decodes automatically by finding the best possible transposition value and search
                words in dictionaryMax6.txt file.
 * ------------------------------------------------
*/

#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h>  //for boolean
#include <iostream>   //for input/output in C++
#include <cstring>
#include <fstream>    //to open text file
#include <cassert>    //to check if text file is opened correctly
using namespace std;

const int Size = 81;                     // 80 characters for the line + 1 for the '\0'
const long MaxNumberOfWords = 34840 ;    // maximum number of words to be stored


//displays author information
//no parameters
//does not return anything
void displayIdentifyingInfo()
{
	printf("Author: Anusha Pai and Bushra Baqui\n");
	printf("Program 3: Decipher\n");
	printf("Anusha Pai   TA: Chenwei Zhang 8am\n");
	printf("Bushra Baqui TA: Chenwei Zhang 9am\n");
	printf("Feb 21, 2016\n");
}//end of displayIdentifyingInfo()


//displays the options the user can choose
//no parameters
//does not return anything
void displayUserChoices()
{
	printf("Choose from the following options:\n");
	printf("     1. Encode some text \n");
	printf("     2. Decode using user-entered values\n");
	printf("     3. Decode automatically\n");
	printf("     4. Exit program\n");
}//end of displayUserChoices()


//encode function encodes given string(char userInput[]) by adding transposition value(int transpVal) to each character
//parameters: char userInput[] (to manipulate string)  &   int transpVal (to add each character in userInput)
//this function does not return anything
void encode(char userInput[], int transpVal)
{
	//checks for negative values and makes transpVal positive
	if(transpVal < 0)
	{
		transpVal = transpVal + 94 + 1;
	}
	  
	//loop to add each character by transpVal
   for(int j = 0; userInput[j] != '\0'; j++)
   {
		for(int k = 0; k < transpVal; k++)
		{
			//the character '~' at the end wraps around to the space character at the beginning of the range.
			//else simply adds one (ASCII)
			if(userInput[j] == '~')
   			{
   				userInput[j] = ' ';
			}
			else
			{
				userInput[j]++;
			}	
		}					
   }
}//end of encode(char userInput[], int transpVal)


//decode function decodes given string(char userInput[]) by 'subtracting' transposition value(int transpVal) to each character
//parameters: char userInput[] (to manipulate string)  &   int transpVal (to add each character in userInput)
//this function does not return anything
void decode(char userInput[], int transpVal)
{
	//checks for negative values and makes transpVal positive (therefore we are technically adding)
	if(transpVal < 0)
	{
		transpVal = transpVal + 94 + 1;
	}
	
	//loop to add each character by transpVal
	for(int j = 0; userInput[j] != '\0'; j++)
  	{
		for(int k = 0; k < transpVal; k++)
		{
			//the character '~' at the end wraps around to the space character at the beginning of the range.
			//else simply adds one (ASCII)
			if(userInput[j] == '~')
   			{
   				userInput[j]= ' ';
			}
			else
			{
				userInput[j]++;
			}	
		}					
   	}
}//end of decode(char userInput[], int transpVal)


//wordIsFound function returns true if wordToLookup is found in the dictionaryMax6.txt file, else returns false
//parameters: char *wordToLookup (finds this word in file)   &   int len (length of wordToLookup)
bool wordIsFound(char *wordToLookup, int len)
{
	ifstream inStream;                                 // declare an input stream for my use
	static char theWords[ MaxNumberOfWords][ Size];    // Array to store words from input line
	int wordRow = 0;                                   // Row for the current word
	bool wordWasFound = false;                         // flag to track whether or not word is found
	
	inStream.open( "C:\\Users\\Anusha Pai\\Desktop\\Program3\\dictionaryMax6.txt");
	assert( ! inStream.fail() );      // make sure file open was OK
	
	//Keeps repeating while input from the file yields a word
	while (inStream >> theWords[ wordRow]) 
	{
		wordRow++;
	}	
   
   	//character array to copy wordToLookup in
	char wordSearch[81];
   	strncpy(wordSearch, wordToLookup, len);
	
	//last element asigned to the null character (gets rid of junk values)
	wordSearch[len] = '\0';

    //loop to find if wordSearch is found in dictionaryMax6.txt
	for (int i=0; i < wordRow; i++)  
	{
		//See if this word matches
		if( strcmp( wordSearch, theWords[ i]) == 0 )
		{
		 wordWasFound = true;   //word is found
		 break;                 // quit looking
		}
	}
	return wordWasFound;
}//end of wordIsFound(char *wordToLookup, int len)


//findNumberOfWords function finds the number of words userInput[] has with each transposition value(0-95) and stores it in arr[]
//paramters: char userInput[] (used to decode and find number of words)  &   
//           char arr[] (the number of words found in each transposition value is stored in arr[] -- index is transposition value
void findNumberOfWords(char userInput[], char arr[])
{
	bool start = false;           //true when pStart is assigned
	char *pStart;                 //pointer to first element of word
	int len;                      //lenght of word
	bool wordFound;               //true if word is found... else false
	char *pSpace;                 //pointer to space/null character (end of word)
	int transPredict = 0;         //transposition value to send to decode function
	int countWords = 0;           //words found with each transPredict
	
	//nested for loop to decode, count how many words found with each transposition value(countWords), and stores countWords in arr[]
	for(int i = 0; i <= 95; i++)
	{
		countWords = 0;                   //resets before decoding
		decode(userInput, transPredict);   
		transPredict = 1;       

		//goes through each character and finds the word, then sends the word to wordIsFound function 
		for(int j = 0; j <= strlen(userInput); j++)
		{
			//if statements to separate word from userInput
			if((start == false) && userInput[j] != ' ' && userInput[j] != '\0')
			{
				start = true;
				pStart = &userInput[j];	   //pointer to first element of word
			}
			if((start == true) && (userInput[j] == ' ' || userInput[j] == '\0'))
			{
				pSpace = &userInput[j];
				len = pSpace - pStart;
				
				//checks if word is found and increments countWords if found
				wordFound = wordIsFound(pStart, len);
				if(wordFound)
				{
					countWords++;
				}
			
				start = false;    //resets start to find the next word
			
			}
		}
		arr[i] = countWords;   //assigns countWords to arr[] where 'i' is the tranposition value
	}
}//findNumberOfWords(char userInput[], char arr[])


/*------------------------------------------------------------------------------------------------*/

int main()
{
	displayIdentifyingInfo();
	printf("\n");
	displayUserChoices();
	
	//variables to store user input values
	int userChoice;  
	char returnKey;   
	int direction = 0;
	int transpVal;
	char userInput[81];
	
	//Recieves input for opions
	printf("Your choice: ");
	scanf("%d%c", &userChoice, &returnKey);
	
	//checks if userChoice is a valid choice or checks if user wants to exit
	if((userChoice != 1 && userChoice != 2 && userChoice != 3) || (userChoice == 4))
	{
		return 0;
	}
	
	if(userChoice == 1)
	{
		//receives input for text
		printf("Enter text to be encoded:");
		cin.getline(userInput, 80);
	}
	
	else if(userChoice == 2 || userChoice == 3)
	{
	 	//receives input for text
		printf("Enter text to be decoded:");
		cin.getline(userInput, 80);
	}
	
	if(userChoice == 1)
	{
		//receives input for direction
		printf("Enter direction (1 Forwards or 2 Reverse): ");
		scanf("%d%c", &direction, &returnKey);	
	}
	if(userChoice == 1 || userChoice == 2)
	{
		//receives input for transposition value
		printf("Enter transposition value: ");
		scanf("%d%c", &transpVal, &returnKey);
	}
	
	//variables used in switch-case statement	
	char forward[95];      //to store how many words found with forward direction
	int maxFor;            //max number of words found in forward direction
	int maxForTrans = 0;   //transposition value where maxFor exists
	int maxRev;            //max number of words found in reverse direction
	int maxRevTrans = 0;   //transposition value where maxRev exists
	char reverse[95];      //to store how many words found with reverse direction
	
	
	//difference apporaches for different userChoices
	switch(userChoice)
	{
		//Encode some text
		case 1:
			printf("\n");
			printf("Original and changed text are: \n");
			
			if(direction == 2)  //reverse direction
			{
				strrev(userInput);   //reverses userInput
				printf("%s\n", userInput);
			}
			else
			{
				printf("%s\n", userInput);
			}			
		
			encode(userInput, transpVal);
			printf("%s\n", userInput);  //result
		
			printf("\n");
			printf("Done.\n");
			
			break;	
		
		//Decode using user-entered values
		case 2:
			printf("\n");
			printf("Original and changed text are: \n");
			printf("%s\n", userInput);
	
			decode(userInput, transpVal);   
			
			//displays forwards output
			printf("%s   <-- Forwards\n", userInput);
			
			//reverse userInput
			strrev(userInput);  
			//displays reverse output
			printf("%s   <-- Reverse\n", userInput);
			    
			printf("\n");
			printf("Done.\n");
			break;
		
		//Decode automatically
		case 3: 
			printf("\n");
			//automatically decode using forward direction of userInput
			findNumberOfWords(userInput, forward);	
			
			//automatically decode using reverse direction of userInput
			strrev(userInput);
			findNumberOfWords(userInput, reverse);
			
			//initial values for maxFor and maxRev
			maxFor = forward[0];
			maxRev = reverse[0];
			
			//stores the max number of words in each array: forward and reverse
			for(int i = 0; i < 95; i++)
			{
				if(forward[i] > maxFor)
				{
					maxFor = forward[i];
					maxForTrans = i;  //stores transposition value
					
				}
				if(reverse[i] > maxRev)
				{
					maxRev = reverse[i];
					maxRevTrans = i;  //stores transposition value
				}
			}
			
			//check which direction finds the most words
			if(maxRev > maxFor)
			{
				decode(userInput, maxRevTrans);   //decode using reverse direction 
			}
			else
			{
				//reverse userInput back to forward direction
				strrev(userInput);
				decode(userInput, maxForTrans);   //decode using forward direction
			}
			
			printf("%s\n", userInput);
			printf("Done.\n");
			break;
		
		default:
			break;
	}
	
	return 0;
	
}


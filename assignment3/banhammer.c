# ifndef PREFIX
# define PREFIX "/afs/cats.ucsc.edu/users/g/darrell/"
# endif
# define BADSPEAK PREFIX "/badspeak.txt"
# define NEWSPEAK PREFIX "/newspeak.txt"
# define ESPERANTO PREFIX "/Esperanto.txt"
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <getopt.h>
# include <errno.h>
# include <ctype.h>
# include <stdbool.h>
# include "ll.h"
# include "bf.h"
# include "hash.h"
# include "bv.h"
# include "bf.h"
# include "aes.h"
int yylex(void);
extern char* yytext;
extern FILE* yyin;
bool moveToFront;
extern char *optarg;
uint32_t seeks, dictionary, translations, text, numCalls;

/**
 * Takes in array of listNode pointers, wordList[0] contains badspeak words, wordList[1] 
 * contains oldspeak words. Prints appropriate message and words in "linked-list".
 * 
 * @param listNode ** wordList has length 2, first index for badspeak words and second for 
 * oldspeak words
 */
void makeDecision(listNode **wordList)
{
	if(wordList[0] || wordList[1])
	{
		if(wordList[0])															
		{
			printf("Dear Comrade,\n\n");										//print badspeak message
			printf("You have chosen to use degenerate words that may cause hurt\n");
			printf("feelings or cause your comrades to think unpleasant thoughts.\n");
			printf("This is doubleplus bad. To correct your wrongthink and\n");
			printf("save community consensus we will be sending you to joycamp\n");
			printf("administered by Miniluv.\n\n");
			printf("Your errors:\n\n");
			printLL(wordList[0]);												//print badspeak words
			printf("\n");
			if(wordList[1])
			{
				printf("Think on these words during your vacation!\n\n");
				printLL(wordList[1]);
			}
		}
		else																	//print oldspeak message 
		{
			printf("Dear Comrade,\n\n");
			printf("Submitting your text helps to preserve feelings and prevent\n");
			printf("badthink. Some of the words that you used are not goodspeak.\n");
			printf("The list shows how to turn the oldspeak words into newspeak.\n\n");
			printLL(wordList[1]);												//print oldspeak wordList(oldwords and translations)
		}
	}	
}

void printStats(bloomF *A, bloomF *B)
/**
 * When user enters in s flag, print all the stats while running the program. 
 */
{
	float avg = (float)(seeks/numCalls);
	printf("%d ", numCalls);
	printf("Seeks %d, ", seeks);											//print out stats
	printf("Average %f, ", avg);
	printf("Dictionary %d, ", dictionary);
	printf("Translations %d, ", translations);
	printf("Text %d, ", text);
	printf("Densities: %.6f, %.6f\n", (float)countBF(A)/lenBF(A), (float)countBF(B)/lenBF(B));
	return; 																//return statement
}

/**
 * This is the main method, the primary function for running
 * this overall program. Takes in command line arguments, then 
 * proceeds to act based upon those arguments. 
 */
int main(int argc, char **argv)
{
	FILE *newspeakf, *badspeakf;											//newspeak and badspeak files to be read in
	bitV *vec = newVec(5);													//new bitvector created
	char c;																	//command line argument 
	enum sorts {STATS = 1, HASH_SIZE, BF_SIZE, M, DMTF};					//enum type for the type of sort to run
	uint32_t initA[] = {0xDeadD00d, 0xFadedBee, 0xBadAb0de, 0xC0c0aB0a}; 	// First Bloom filter 
	uint32_t initB[] = {0xDeadBeef, 0xFadedB0a, 0xCafeD00d, 0xC0c0aB0a};	// Second Bloom filter 
	uint32_t initH[] = {0xDeadD00d, 0xFadedBee, 0xBadAb0de, 0xC0c0Babe}; 	// Hash table
	uint32_t BFSz = 1048576, HTSz = 10000;
	while((c = getopt(argc, argv, "sh:f:mb")) != -1)			
	{
		switch(c)															//switch statement for the command line argument
		{																	//use setBit for specific index
			case 's' :														//case s
			{
				setBit(vec, STATS);
				break;
			}
			case 'h' :														//case h
			{
				setBit(vec, HASH_SIZE);
				HTSz = atoi(optarg);
				break;
			}
			case 'f' :														//case f
			{
				setBit(vec, BF_SIZE);
				BFSz = atoi(optarg);
				break;
			}
			case 'm' : 														//case m moveToFront is true
			{
				setBit(vec, M);
				moveToFront = 1;
				break;
			}
			case 'b' :														//case b moveToFront is false
			{
				moveToFront = 0;
				break;
			}
			default :														//default case
			{
				break;
			}
		}
	}
	bloomF *A = newBF(BFSz, initA);											//create new bloom filters and hashtable
	bloomF *B = newBF(BFSz, initB);
	hashTable *HT = newHT(HTSz, initH);
	listNode **mistakes = (listNode **)calloc(2, sizeof(listNode *));		//create "linked-list"
	newspeakf = fopen(NEWSPEAK, "r");										//read only for newspeak and badspeak txt files
	badspeakf = fopen(BADSPEAK, "r");
	char old [100];															//char arrays for reading in words in txt files
	char new [100];
	char bad [100];
	int tokenID = 0;														//used to make sure while loops run until end of file(EOF)
	while (tokenID != -1)													// Loop until the end of the file.
	{
		tokenID = fscanf(badspeakf, "%s \n", bad); 
		setBF(A, bad);
		setBF(B, bad);
		insertHT(HT, bad, "");
		dictionary++;
	}
	fclose(badspeakf);														//close badspeak
	tokenID = 0;															//reset tokenID to 0
	while (tokenID != -1)													// Loop until the end of the file.
	{
		tokenID = fscanf(newspeakf, "%s %s\n", old, new); 
		insertHT(HT, old, new);
		setBF(A, old);
		setBF(B, old);
		translations++;
	}
	fclose(newspeakf);														//close newspeak
	tokenID = 0;															//reset tokenID to 0
	while(tokenID != -1)													//Loop until end of file
	{
		tokenID = yylex();													//use yylex for user input
		text++;
		for(uint32_t i = 0; i < strlen(yytext); i++)						//set text to lowercase
		{
			yytext[i] = tolower(yytext[i]);
		}
		if(memBF(A, yytext) && memBF(B, yytext))							//word is in bloom filters
		{
			if(findHT(HT, yytext))											//word has entry in hashTable
			{
				if(strcmp(findHT(HT, yytext)->newspeak, "") && !findLL(&mistakes[1], yytext))
				{															//&mistakes[1] represents oldspeak words
					translations++;
					insertLL(&mistakes[1], findHT(HT, yytext)->oldspeak, findHT(HT, yytext)->newspeak);
				}
				else if(!strcmp(findHT(HT, yytext)->newspeak, "")&& !findLL(&mistakes[0], yytext))
				{															//&mistakes[0] represents badspeak words
					dictionary++;
					insertLL(&mistakes[0], findHT(HT, yytext)->oldspeak, findHT(HT, yytext)->newspeak);
				}
			}
		}
	}
	if(valBit(vec, STATS))													//only print stats if prompted by user
	{
		printStats(A, B);
	}
	else
	{
		makeDecision(mistakes);												//call makeDecision to determine what to print
	}
	delBF(A);																//delete bloom filters, hashtable, and bitvector 
	delBF(B);
	delHT(HT);
	delVec(vec);												
	return 0;																//return statement
}
# include <stdlib.h>
# include <stdint.h>
# include <string.h>
# include "aes.h"
# include "hash.h"
# include <stdio.h>
# include "ll.h"

//realLength() and hash() functions given by DDEL

extern bool moveToFront;

static inline int realLength(int l)
{
	return 16 * (l / 16 + (l % 16 ? 1 : 0));
}

uint32_t hash(hashTable *h, const char *key)
{
	uint32_t output[4] = { 0x0 };
	uint32_t sum		= 0x0;
	int keyL 			= strlen(key);
	uint8_t *realKey 	= (uint8_t *) calloc(realLength(keyL), sizeof(uint8_t));

	memcpy(realKey, key, keyL);

	for (int i = 0; i < realLength(keyL); i += 16)
	{
		AES128_ECB_encrypt((uint8_t *) h->s, 						//Salt
							(uint8_t *) realKey + i, 				//Input
							(uint8_t *) output);					//Output
		sum ^= output[0] ^ output[1] ^ output[2] ^ output[3];
	}
	free(realKey);
	return sum;
}

hashTable *newHT(uint32_t len, uint32_t b[])
{
	hashTable *HT = (hashTable *)malloc(sizeof(hashTable));			//allocate memory for hashTable
	HT->h = (listNode **)calloc(len, sizeof(listNode *));			//allocate memory for "linked-list"
	HT->l = len;													//set len of hashTable
	for(uint32_t i = 0; i < 4; i++)									//set salt of hashTable
	{
		HT->s[i] = b[i];
	}
	return HT;
}

void delHT(hashTable *HT)											
{
	delLL(*(HT->h));												//delete "linked-list" in hashTable
	free(HT);														//free hashTable and set it to NULL
	HT = NULL;
}

listNode *findHT(hashTable *HT, const char *key) 					//call hash and call findLL of hashTable at the index
{
	uint32_t ind = hash(HT, key)%(HT->l);
	return findLL(&(HT->h[ind]), key);
}

void insertHT(hashTable *HT, const char *key, const char *tran) 	//call hash and call insertLL of hashTable at the index
{
	uint32_t ind = hash(HT, key)%(HT->l);
	insertLL(&(HT->h[ind]), key, tran);
	return;
}

void printHT(const hashTable *HT)									//print the hashTable(includes the "linked-list")	
{
	for(uint32_t i = 0; i < HT->l; i++)
	{
		if(*(HT->h + i))											//hashTable of loop index
		{
			printLL(*(HT->h + i));
		}
		
	}
}
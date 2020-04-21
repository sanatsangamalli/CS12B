# ifndef NIL
# define NIL (void *) 0
# endif
# ifndef _BF_H
# define _BF_H
# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include "aes.h"

//outline of code given by DDEL

typedef struct bloomF {
	uint8_t *v;	//Vector
	uint32_t l;	//Length
	uint32_t s[4];	//Salt
} bloomF;

static inline int realLength(int l)
{
	return 16 * (l / 16 + (l % 16 ? 1 : 0));
}

//Each function has its own hash functions, determined by the salt.(copied from hash.c)

static inline uint32_t hashBF(bloomF *v, char *key)
{
	uint32_t output[4] = { 0x0 };
	uint32_t sum		= 0x0;
	int keyL 			= strlen(key);
	uint8_t *realKey 	= (uint8_t *) calloc(realLength(keyL), sizeof(uint8_t));

	memcpy(realKey, key, keyL);

	for (int i = 0; i < realLength(keyL); i += 16)
	{
		AES128_ECB_encrypt((uint8_t *) v->s, 						//Salt
							(uint8_t *) realKey + i, 				//Input
							(uint8_t *) output);					//Output
		sum ^= output[0] ^ output[1] ^ output[2] ^ output[3];
	}
	free(realKey);
	return sum;
}

//Create a new Bloom Filter of a given length and hash function.

static inline bloomF *newBF(uint32_t l, uint32_t b[])
{
	bloomF *bf = (bloomF *)malloc(sizeof(bloomF));	//Code
	bf->v = (uint8_t *)malloc((l/8  + 1)* sizeof(uint8_t));
	bf->l = l;
	for(uint32_t i = 0; i < 4; i++)
	{
		bf->s[i] = b[i];
	}
	return bf;
}

//Delete a Bloom filter

static inline void delBF(bloomF *bf)
{
	free(bf->v);
	bf->v = NULL;
	free(bf);
	bf = NULL;
	return;
}

//Return the value of position k in the Bloom filter

static inline uint32_t valBF(bloomF *bf, uint32_t k)	//do as same in bv
{
	uint32_t x = ((bf->v[k >> 3] & (0x1 << (k & 07))) >> (k & 07));
	return x;
}

static inline uint32_t lenBF(bloomF *x)
{ 
	return x->l; 
}

//Count bits in Bloom filter

static inline uint32_t countBF(bloomF *b)
{
	uint32_t counter = 0;
	for(uint32_t i = 0; i < b->l; i++)
	{
		if(valBF(b, i))
		{
			counter++;
		}
	}
	return counter;
}

//Set an entry in the Bloom filter

static inline void setBF(bloomF *x, char * key)
{
	uint32_t pos = hashBF(x, key)%(x->l);
	x->v[pos >> 3] |=  (0x1 << (pos & 07));		
	return;
}

//Clear an entry in the Bloom filter 

static inline void clearBF(bloomF *x, char *key)
{
	uint32_t pos = hashBF(x, key)%(x->l);
	x->v[pos >> 3] &= ~(0x1 << (pos & 07));
	return;
}

//Check membership in the Bloom filter

static inline uint32_t memBF(bloomF *x, char *key)
{
	return valBF(x, hashBF(x, key)%(x->l));
}

//print bits in bloom filter

static inline void printBF(bloomF *x)
{
	for (uint32_t i = 0; i < x->l; i += 1)		
	{
		if (valBF(x, i)) { printf("1"); }
		else              { printf("0"); }
	}
	printf("\n");
}

#endif

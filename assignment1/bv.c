# include <stdio.h>
# include <stdlib.h>
# include "bv.h"
# define _BVector
# include <stdint.h>

//code for setBit() clrBit() and valBit() given to us in example 19 on piazza by DDEL
bitV *newVec(uint32_t length)			// Create a new vector of specified length
{
	bitV * vector;									//create new bitvector and initalize appropriate number of bytes
	vector = (bitV *)(calloc(length, 8));
	vector->v = (uint8_t *)(calloc(length, 8));
	vector->l = length;								//set its length
	return vector;
}

void delVec(bitV * vec)			// Deletes a vector
{
	free(vec->v);				//free up the space and make it null
	vec->v = NULL;
	free(vec);
	vec = NULL;
	return;
}
void oneVec(bitV * vec)				// Creates a vector of all 1
{
	for(unsigned int i = 0; i < vec->l; i++)		//loop through and set all the bits equal to 1
	{
		setBit(vec, i);							
	}
	return;
}

void setBit(bitV * v, uint32_t loc)	// Sets a specified bit
{
	v->v[loc >> 3] |=  (0x1 << (loc & 07));		
	return;
}

void clrBit(bitV * v, uint32_t loc)	// Clears a specified bit
{
	v->v[loc >> 3] &= ~(0x1 << (loc & 07));
	return;
}

uint8_t valBit(bitV * v, uint32_t loc)	// Returns the value of a specified bit
{
	uint8_t x = ((v->v[loc >> 3] & (0x1 << (loc & 07))) >> (loc & 07));
	return x;
}


uint32_t lenVec(bitV * v)		// Return the length of the vector
{
	return v->l;
}

void printVec(bitV *v)			//prints out the vector
{
	for (uint32_t i = 0; i < v->l; i += 1)
	{
		if (valBit(v, i)) 
		{ 
			printf("1"); 
		}
		else             
		{
			printf("0"); 
		}
	}
	printf("\n");
}
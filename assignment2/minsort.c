//code given by DDEL
# ifndef _INSTRUMENTED
# define SWAP(x, y) {uint32_t t = x; x = y; y = t; moveCount += 3;}
# else
# define SWAP(x, y) {uint32_t t = x; x = y; y = t;}
# endif
# include <stdint.h>
# include "minsort.h"
# include <stdio.h>

//minIndex: find the index of the least element.
extern uint32_t moveCount;
extern uint32_t numCompares;

/**
 * This method takes an array, a range of indices to go between,
 * and proceeds to find the index of the smallest number. 
 *
 * @param uint32_t a[] is the array to look through
 * @param uint32_t first is the minimum index to start from in the array
 * @param uint32_t last is the max index to look through in the array
 * @return the index of the smallest number
 */
uint32_t minIndex(uint32_t a[], uint32_t first, uint32_t last)
{
	uint32_t smallest = first; 
	for(uint32_t i = first; i < last; i += 1)
	{
		smallest = a[i] < a[smallest] ? i : smallest;
		numCompares++;
	}
	return smallest;
}

//minSort : sort by repeatedly finding the least element .
/**
 * This is the main function for running minsort. 
 *
 * @param uint32_t a[] is the array to sort
 * @param length is the length of the array
 */
void minSort(uint32_t a[], uint32_t length)
{
	for(uint32_t i = 0; i < length - 1; i += 1)
	{
		uint32_t smallest = minIndex(a, i, length);				//gets smallest index from minIndex() method
		if(smallest != i)	// It ’s silly to swap with yourself !
		{
			SWAP(a[smallest], a[i]);
		}
	}
	return;
}
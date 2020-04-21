//code in python given by DDEL
# ifndef _INSTRUMENTED
# define SWAP(x, y) {uint32_t t = x; x = y; y = t; moveCount += 3;}
# else
# define SWAP(x, y) {uint32_t t = x; x = y; y = t;}
# endif
# include "quicksort.h"
# include <stdlib.h>
# include <stdio.h>
# include <stdint.h>
uint32_t partition(uint32_t a[], uint32_t l, uint32_t r);
extern uint32_t moveCount;
extern uint32_t numCompares;

/**
 * This is the main function for running quickSort. It finds 
 * the index to partition the array, then recursively calls 
 * itself to partition the left half of the array and then
 * the right half.
 * 
 * @param uint32_t a[] is the array to be sorted
 * @param uint32_t left is the minimum index of the array to start from
 * @param uint32_t right is the maximum index of the array to reach
 */
void quickSort(uint32_t a[], uint32_t left, uint32_t right)
{
	uint32_t index = 0;
	if(left < right)
	{
		index = partition(a, left, right);
		quickSort(a, left, index - 1);
		quickSort(a, index + 1, right);
	}
}

/**
 * This is a helper method that splits the array into 3 parts, 
 * and then swaps elements so that they are in order. 
 *
 * uint32_t a[] is the array to traverse
 * @param uint32_t left is the minimum index of the array to start from
 * @param uint32_t right is the maximum index of the array to reach
 * @return the index of the array to partition from
 */
uint32_t partition(uint32_t a[], uint32_t left, uint32_t right)
{
	uint32_t pivot = a[left];
	uint32_t ind1 = left + 1; 
	uint32_t ind2 = right;
	int done = 1;
	while(done != 0)
	{
		while(a[ind1] <= pivot && ind1 <= ind2)
		{
			ind1++;
			numCompares += 1;
		}
		while(a[ind2] >= pivot && ind2 >= ind1)
		{
			ind2--;
			numCompares += 1;
		}
		if(ind1 > ind2)
		{	
			done = 0;
		}
		else
		{
			SWAP(a[ind1], a[ind2]);
		}
	}
	SWAP(a[left], a[ind2]);
	return ind2;
}

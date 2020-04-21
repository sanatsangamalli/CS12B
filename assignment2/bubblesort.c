//pseudocode given by DDEL
# ifndef _INSTRUMENTED
# define SWAP(x, y) {uint32_t t = x; x = y; y = t; moveCount += 3;}
# else
# define SWAP(x, y) {uint32_t t = x; x = y; y = t;}
# endif
# include <stdint.h>
# include <stdio.h>
# include "bubblesort.h"
extern uint32_t moveCount;
extern uint32_t numCompares;

/**
 * This is the main function for running bubbleSort. It goes
 * through the array looking at consecutive elements, and 
 * "bubbles" the biggest elements towards the top via SWAP. 
 *
 * @param uint32_t a[] is the array to be sorted
 * @param uint32_t len is the length of the array
 */
void bubbleSort(uint32_t a[], uint32_t len)
{
	for(uint32_t i = 0; i < len; i++)
	{
		for(uint32_t j = 1; j <= len - 1; j++)
		{
			if(a[j-1] > a[j])
			{
				SWAP(a[j-1], a[j]);
			}
			numCompares++;
		}
	}
}
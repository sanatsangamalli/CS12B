//code in python provided by DDEL
# include <stdlib.h>
# include "mergesort.h"
extern uint32_t moveCount;
extern uint32_t numCompares;

/**
 * This method is the main function for running mergeSort. It
 * divides the array into 2 smaller arrays(recursively), and 
 * then adds them back to the array in order. 
 *
 * @param uint32_t a[] is the array to be sorted
 * uint32_t len is the length of the array
 */
void mergeSort(uint32_t a[], uint32_t len)
{
	if(len > 1)
	{
		uint32_t mid = len/2;
		uint32_t (*leftList);
		if(len % 2 == 1)
		{	
			leftList = calloc(mid + 1, sizeof(uint32_t));
			moveCount++;
		}
		else
		{
			leftList = calloc(mid, sizeof(uint32_t));
			moveCount++;
		}
		uint32_t (*rightList) = calloc(mid, sizeof(uint32_t));
		moveCount++;
		mergeSort(leftList, mid);
		mergeSort(rightList, mid + 1);
		uint32_t l, r = 0;
		for(uint32_t i = 0; i < len; i++)
		{
			if(l < (sizeof(leftList)/sizeof(uint32_t)) && r < (sizeof(rightList)/sizeof(uint32_t)))
			{
				if(leftList[l] < rightList[r])
				{
					a[i] = leftList[l];
					l += 1;
					numCompares++;
					moveCount++;
				}
				else
				{
					a[i] = rightList[r];
					r += 1;
					moveCount++;
				}
			}
			else if(l < (sizeof(leftList)/sizeof(uint32_t)))
			{
				a[i] = leftList[l];
				l += 1;
				moveCount++;
			}
			else
			{
				a[i] = rightList[r];
				r += 1;
				moveCount++;
			}
		}
	}
}
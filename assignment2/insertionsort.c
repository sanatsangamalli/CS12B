//pseudocode given by DDEL
# include <stdint.h>
# include "insertionsort.h"
extern uint32_t moveCount;
extern uint32_t numCompares;

/** 
 * This is the main function for running insertionSort.
 * It takes one element from the list and inserts it 
 * into its position relative to the continually growing 
 * sorted sublist.
 *
 * @param uint32_t a[] is the array to be sorted
 * @param uint32_t len is the length of the array
 */
void insertionSort(uint32_t a[], uint32_t len)
{
	uint32_t temp = 0; 
	for(uint32_t i = 1; i < len; i++)
	{
		temp = a[i];
		moveCount++;
		int32_t j = (int32_t)(i-1);
		while(j >= 0 && a[j] > temp)
		{
			numCompares++;
			a[j+1] = a[j];
			j--;
			moveCount += 1;
		}
		a[j+1] = temp;
		moveCount++;
	}
}
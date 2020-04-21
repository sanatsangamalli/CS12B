# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <string.h>
# include <stdint.h>

int main(void)
{
	int32_t length = 0;										//tracks the length or array at all times
	char input = 'I';										//keeps track of input to see what operation to do
	int numToBeAdded;										//if 'I' is inputted, keeps track of number to be inserted
	int *arr = malloc(sizeof(int));							//initialize size of array and allocate memory for it using malloc
	while(input != 'Q')										//while loop runs while the user doesn't enter the 'Q' input
	{
		printf("Action? (Insert, Print, or Quit): ");		//prompt user
		scanf(" %c", &input);								//scan user input
		if(input == 'P')									//case where user input is 'P' to print array
		{
			if(length == 0)									//case where no elements in array
			{
				printf("Length = 0:");
			}
			else											//print out array
			{
				printf("Length = %d:", length);				
				for(int i = 0; i < length; i++)				
				{
					printf(" %d", arr[i]);
				}
			}
			printf("\n");									//new line
		}
		else if(input == 'I')								//'I' option to insert in another element at end of array
		{
			printf("Enter an integer: ");					//prompt user
			scanf("%d", &numToBeAdded);						//scan user input of number to be added
			length++;										//element added so have to increment length
			if(length == 1)									//case where this is now the first element
			{
				arr[0] = numToBeAdded;
			}
			else											//if array contains elements need ot call realloc to resize array
			{
				int *tempPtr;								//have to declare temporary pointer, create copy of array, resize array
				tempPtr = arr;
				tempPtr = (int *)realloc(arr, sizeof(int) * length);
				if(tempPtr == NULL)							//error handling in the case of the temporary pointer being null
				{
					free(arr);
					printf("Error on realloc {tempPtr} [%d: %s]\n", errno, strerror(errno));
					return errno;
				}
				tempPtr[length-1] = numToBeAdded;				//add element to end of array		
				arr = tempPtr;
			}
		}
	}
	free(arr);												//free function
	arr = NULL;												//set the array equal to null
	return 0;												//return statement 
}
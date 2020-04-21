# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "sieve.h"
# include "bv.h"
void printFactorization(bitV *v, uint32_t n);

int main(void)
{
	bitV *vec = newVec(100001);					//create new bitvector and run it through sieve
	sieve(vec);
	uint32_t perfExp = 2;												//2 variables to find perfect number via formula given in assignment1 prompt
	uint32_t nextPerfNum = pow(2, perfExp-1) * (pow(2, perfExp)-1);
	for (uint32_t i = 2; i < vec->l; i += 1)						//loop through all the numbers
	{
		if (valBit(vec, i)) 				//prime number, then print it out
		{ 
			printf("%d P", i);
		}
		else              					//composite number, print it and its factors out
		{
			printf("%d C:", i); 		
			printFactorization(vec, i);		//call to find the prime factorization of the number
			if(i == nextPerfNum)			//number is a perfect number, print it out
			{
				printf("\n%d E: 1", i);
				for(uint32_t j = i/2; j >= 2 ; j--)		//for loop to print out all the factors of the number, prime or not
				{
					if(i%j == 0)						//number is divisible by index of for loop
					{
						printf(" %d", i/j);
					}
				}
				for(uint32_t k = perfExp + 1; k < lenVec(vec)/2; k++)			//for loop to find the next perfect number, index starts at last perfect	
				{																//number exponent + 1
					if(valBit(vec, k))											//index of for loop is prime
					{
						uint32_t merPrime = pow(2, k) - 1;						//calculate mersenne prime(according to formula given in assignment1 prompt)
						if(valBit(vec, merPrime))								//if the mersenne prime is prime
						{
							perfExp = k;										//set exponent equal to index in for loop
							nextPerfNum = pow(2, perfExp-1) * merPrime;			//find next perfect number via formula given in assignment1 prompt
							k = lenVec(vec)/2 + 1;								//set index greater than allowed value to break out of loop
						}
					}
				}
			}
		}
		printf("\n");							//new line
	}
	delVec(vec);								//delete vector
	return 0;									//return statement
}

void printFactorization(bitV *v, uint32_t num)
{
	uint32_t test = num;					//copy of the number to modify
	uint32_t arrFactors[32] = {0};			//array to store the factors of the number
	uint32_t ind1 = 0;						//2 indices to help store factors in increasing order
	uint32_t ind2 = 0;
	for (uint32_t k = 2; k <= sqrtl(num); k += 1)
	{
		if(test%k ==0)								//number is divisible by index
		{
			if (valBit(v, k) && test != k) 			//prime number and does not equal index
			{ 
				arrFactors[ind1] = k;				//set array at ind1 to index of for loop
				ind1++;								//increment ind1
				test /= k;							//divide test by for loop index
				if (valBit(v, test)) 				//test is also a prime number(large)
				{  
					arrFactors[31-ind2] = test;		//because test is a larger prime, store it at the end of the array
					ind2++;							//increment ind2
				}
				else
				{
					k = 1;							//reset the index of the for loop to 1 because a number might have a repeated prime factor
				}
			}
		}
	}
	for(int i = 0; i < 32; i++)						//for loop to run through the array
	{
		if(arrFactors[i] != 0)						//array elements initialized to 0, so if the array at the index 
			printf(" %d",arrFactors[i]);			//is not 0, print it out because it is a factor
	}
}
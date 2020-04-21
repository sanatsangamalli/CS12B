# include <stdint.h>
# include <math.h>
# include "sieve.h"
# include "bv.h"
# define _BVector

//Sieve of Eratosthenes code given by DDEL
void sieve(bitV *v)
{
	oneVec(v);
	clrBit(v, 0);
	clrBit(v, 1);
	setBit(v, 2);
	for(uint32_t i = 2; i <= sqrtl(lenVec(v)); i++)
	{
		if(valBit(v, i))
		{
			for(uint32_t k = 0; (k + i) * i <= lenVec(v); k += 1)
			{
				clrBit(v, (k + i) * i);
			}
		}
	}
	return;
}


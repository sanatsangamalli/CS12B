//skeleton for this program provided by DDEL
# include <pthread.h>
# include <errno.h>
# include <getopt.h>
# include <stdlib.h>
# include <stdio.h>
	
void *threadEntry(void *myArgs);
void threadSafe();

pthread_mutex_t mutex;
int counter = 0;

struct threadArgs {
	int data;
};

void *threadEntry(void *myArgs)
{
	struct threadArgs *args = (struct threadArgs *)myArgs;
	threadSafe();
	return args;
}

void threadSafe()
{
	pthread_mutex_lock(&mutex);											//acquire mutex
	counter++;															//increment counter
	pthread_mutex_unlock(&mutex);										//release mutex
}

int main(int argc, char * argv[])
{
	pthread_t thisThread;												
	struct threadArgs args;
	int input;
	char c;
	while((c = getopt(argc, argv, "n:")) != -1)							//get command line argument
	{
		switch(c)
		{
			case 'n' :													//case 'n'
			{
				input = atoi(optarg);									//number of threads
				break;
			}
			default :													//default case
			{
				printf("no input specified");
				break;
			}
		}
	}
	counter = 0;
	pthread_mutex_init(&mutex, NULL);									//initalize mutex
	args.data = 1000;													//per instructions in PDF
	for(int i = 0; i < input; i++)										//loop through all threads
	{
		pthread_create(&thisThread, NULL, threadEntry, &args);			//create a thread
		for(int k = 1; k < args.data; k++)								//run each thread through 1000 times
		{
			threadEntry(&args);											//entry point function for thread
		}
		pthread_join(thisThread, NULL);										
	}	
	pthread_mutex_destroy(&mutex);										//destroy mutex
	printf("%d\n", counter);											//print out counter
	return 0;															//return statement
}
/**
 * Assignment 0: Left, right, and center. Run a game with up to
 * 10 players, each starts with $3. Roll up to 3 dice, and based 
 * on what you roll, you either give money to the left player, rightplayer, 
 * put in it the pot, or keep the money. The game is over when only one player has money.
 *
 * @author Sanat Sangamalli(ssangama@ucsc.edu)
 */
 
#include<stdio.h>
#include<stdlib.h>
int checkPlayersLeft(int arr [],int x);
typedef enum faciem {LEFT, RIGHT, CENTER, PASS} faces;							//global variable of different types of faces

int main(void)
{
	faces die [] = {LEFT, RIGHT, CENTER, PASS, PASS, PASS};						//lines 8 to 18 given in program assignment
	const char *names[] = {"Whoopi",
						"Dale",
						"Rosie",
						"Jimmie",
						"Barbara",
						"Kyle",
						"Raven",
						"Tony",
						"Jenny",
						"Clint"};
	unsigned int seed;															//represents seed to be entered by user
    int numPlayers, numRolls = 0, pot = 0;										//declared and initialized variables such as number of players, amount in pot, and number of rolls
    printf("Enter Seed: ");														//prompt user for seed input
    scanf("%u", &seed);															//get seed user input 
    srand(seed);																//use srand() function on seed
	do																			//do while loop to get number of players from user until good input given
	{
		printf("\nHow many players? ");											//prompt user for number of players
		scanf("%d", &numPlayers);												//get number of players from user input 
	}while(numPlayers < 1 || numPlayers > 10);
	printf("\n");
	int cash [numPlayers];														//int array representing amount of cash each player has
	for(int i =0; i < numPlayers; i++)											//set each players initial amount to $3 for start of game
	{
		cash[i] = 3;	
	}
	while((checkPlayersLeft(cash,numPlayers)) != 1){							//while loop checking if number of players active in game doesn't equal 1
		for(int i = 0; i < numPlayers; i++)
		{
			if(cash[i] > 0 && checkPlayersLeft(cash,numPlayers) != 1){			//if statement checks if player has cash, otherwise skips roll, and if game is done
				if(cash[i] >= 3)												//if-else block determines number of rolls a player gets
				{																//case where player's cash exceeds 3, then numRolls is 3
					numRolls = 3;
				}
				else
				{																//else case where numRolls equal to cash a player has
					numRolls = cash[i];
				}
				printf("%s rolls... ",names[i]);
				for(int k = 0; k < numRolls; k++)								//runs through each roll a player gets 
				{				
					faces face = die[rand()%6];									//gets index of a face by using rand() method
					switch (face)												//switch statement determines what to do based on the face rolled
					{
						case LEFT:												//rolls left face
							if(i == 0)											//special case where at index 0 and left face rolled 
							{
								cash[numPlayers-1]++;							//increment element at end of array
								printf("gives $1 to %s ", names[numPlayers-1]);
							}
							else
							{
								cash[i-1]++;									//otherwise just increment previous index
								printf("gives $1 to %s ", names[i-1]);
							}
							cash[i]--;											//decrement current index because it gave money
							break;
						case RIGHT:												//rolls right face
							if(i == numPlayers -1)								//special case where at index end of array and right face rolled
							{
								cash[0]++;										//increment element at first index fo array
								printf("gives $1 to %s ", names[0]);
							}
							else
							{
								cash[i+1]++;									//otherwise just increment element one index ahead
								printf("gives $1 to %s ", names[i+1]);
							}
							cash[i]--;											//decrement current index because it gave money
							break;
						case CENTER:											//center face rolled
							pot++;												//increment amount of money in pot
							printf("puts $1 in the pot ");
							cash[i]--;											//decrement current index because it gave money
							break;
						default:												//pass face set as default case in switch statement
							printf("gets a pass ");
							break;
					}															//end of switch statement
				}																//end of inner/nested for loop
				printf("\n");													//new line because end of player's turn
			}				
		}																		//end of outer for loop
	}																			//end of while loop
	for(int x = 0; x < numPlayers; x++)											//for loop finds index of player who won, uses that to print winning message
	{
		if(cash[x] != 0)														//if statement isolates index of player who won
		{
			printf("%s wins the $%d pot with $%d left in the bank!\n", names[x], pot, cash[x]);//print win message
			break;																//break out of loop
		}
	}																			//end of for loop
	return 0;																	//return statement for main
}

/**
 * This function checks the number of active players left in the game, and
 * is implemented in the while loop as the check condition. The game is over 
 * when the number of active players is equal to 1. Being "active" is defined 
 * as having money. A player that is currently inactive can become active again 
 * by recieving money.
 * 
 * @param an array of the amount of cash each player has 
 * @param an int representing the total number of players in the game
 * @return the number of active players in the game(players who have money)
 */
int checkPlayersLeft(int arr [], int people)									
{																				
	int numPlayersInGame = 0;													//variable to represent number of players left in game
	for(int i = 0; i < people; i++)												//for loop counts number of people left in game
	{
		if(arr[i] > 0)
		{
			numPlayersInGame++;													//if player has cash increment variable numPlayersInGame
		}
	}																			//end of for loop
	return numPlayersInGame;													//return statement 
}
# include "ll.h"
# include <stdio.h>
# include <stdint.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

extern bool moveToFront;
extern uint32_t seeks, numCalls;

listNode *newNode(const char *oldWord, const char *newWord)
{
	listNode *n = (listNode *)malloc(sizeof(listNode));												//allocate memory for the listNode and char ptr's
	char *temp1 = malloc(sizeof(oldWord));
	strcpy(temp1, oldWord);																			//copy oldword into temp char ptr  
	n->oldspeak = temp1;																			//set oldspeak as temp char ptr
	char *temp2 = malloc(sizeof(newWord));
	strcpy(temp2, newWord);
	n->newspeak = temp2;
	return n;																						//return node
}

listNode *insertLL(listNode **n, const char *key, const char *tran) 
{
	listNode *give = newNode(key, tran);															//create new node 
	listNode *curr = *n;																			//curr as head and prev as null
	listNode *prev = NULL;
	if(curr == NULL)																				//case of no entries
	{
		*n = give;																					//set head as new entry, return it
		return give;
	}
	else if(curr->next == NULL)																		//1 entry case
	{
		if(!(strcmp(curr->oldspeak, give->oldspeak)) && !(strcmp(curr->newspeak, give->newspeak)))	//if new node is a duplicate
		{
			delNode(give);																			//delete new node and return head
			return *n;
		}
		else																						//otherwise set new node as head
		{
			give->next = *n;
			*n = give;
			return give;
		}
	}
	if(!(strcmp(curr->oldspeak, give->oldspeak)) && !(strcmp(curr->newspeak, give->newspeak)))		//recheck for duplicate, delete new node and return head
	{
			delNode(give);
			return *n;
	}
	while(curr->next != NULL)																		//till it reaches last node(excluding null)
	{
		prev = curr;																				//set prev as old curr, curr as next in list
		curr = curr->next;
		if(!(strcmp(curr->oldspeak, give->oldspeak) || strcmp(curr->newspeak, give->newspeak)))		//oldspeak or newspeak match
		{
			prev->next = curr->next;																//set prev's next as curr's next
			delNode(curr);																			//delete curr
			give->next = *n;																		//set new node as head, and return it
			*n = give;
			return give;
		}
	}
	give->next = *n;																				//if it gets this far, set new node as head and return it
	*n = give;
	return give;
}

listNode *findLL(listNode **n, const char *key) 													
{		
	numCalls++;																						//findLL is called
	for(listNode *temp = *n; temp != NULL ; temp = temp->next)										//runs till temp ptr is NULL
	{
		seeks++;																					//iterateing through
		if(strcmp(temp->oldspeak, key) == 0)
		{
			if(moveToFront)																			//if moveToFront, then insertLL at front
			{
				insertLL(n, temp->oldspeak, temp->newspeak);
			}
			return temp;																			//otherwise just return temp ptr
		}
	}
	return NULL;
}

void delNode(listNode *n)																			
{
	free(n->oldspeak);																				//free the char ptr's
	free(n->newspeak);
	free(n);																						//free node
	n = NULL;																						//make node NULL
	return;
}

void delLL(listNode *n)
{
	while(n != NULL)																				//keep calling delNode till list is NULL
	{
		listNode *temp = n;
		n = n->next;
		delNode(temp);
	}
	return;
}

void printLL(listNode *n)																			
{
	for(listNode *temp = n; temp != NULL; temp = temp->next)										//loop through listNodes
	{
		if(strcmp(temp->newspeak, ""))																//words with translations
		{
			printf("%s -> %s", temp->oldspeak, temp->newspeak);
		}
		else																						//bad words
		{
			printf("%s", temp->oldspeak);
		}
		printf("\n");
	}
}
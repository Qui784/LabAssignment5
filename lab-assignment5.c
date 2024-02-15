/*
Author:	Quianna
Class:	COP3502 Lab
Title:	Lab 4
Date:	02/07/2024
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	char letter;
	struct node* next;
} node;

// Returns number of nodes in the linkedList.
int length(node* head)
{
	//	variable to store length of list
	int len = 0;

	//	for segmentation fault
	if (head == NULL)
		return 0;
	
	//	loop through nodes in linked list
	while (head != NULL)
	{
		//	increase the length variable
		len++;
		//	go to next node
		head = head->next;
	}

	//	return the length of the linked list
	return len;
}

// parses the string in the linkedList
//  if the linked list is head -> |a|->|b|->|c|
//  then toCString function wil return "abc"
char* toCString(node* head)
{	
	//	for segmentation fault
	if (head == NULL)
		return NULL;

	//	allocate space for a a char pointer that holds the string
	char* string = (char*) malloc ((length(head) + 1) * sizeof(char));

	//	variable for index in string
	int i = 0;

	//	loop through nodes in linked list
	while (head!= NULL)
	{
		//	assign letter of head to character at index of string
		string[i] = head->letter;
		//	increment i
		i++;
		//	move to next node in list
		head = head->next;
	}

	//	assign last character in string to null character
	string[i] = '\0';

	//	return string
	return string;
}

// inserts character to the linkedlist
// if the linked list is head -> |a|->|b|->|c|
// then insertChar(&head, 'x') will update the linked list as follows:
// head -> |a|->|b|->|c|->|x|
void insertChar(node** pHead, char c)
{
	//	create temp nodes
	node *t, *temp;
	//	allocate space for temp
    temp = (node *) malloc(sizeof(node));
	//	assign temp letter to new character
    temp->letter = c;
	//	assign temp next to NULL
    temp->next = NULL;

	//	if pHead is empty
    if (*pHead == NULL)
        *pHead = temp;	//	assign pHead to temp
    else	//	pHead is not empty
    {
		//	t is dereferenced pHead
        t = *pHead;
		//	loop through nodes in t until last node
        while(t->next != NULL)
            t = t->next;
        //	next value of last node in t is temp
		t->next = temp;
    }
}

// deletes all nodes in the linkedList.
void deleteList(node** pHead)
{
	//	create a temp node pointer
	node *temp;

	//	if head is null, return
	if (pHead == NULL)
		return;

	//	loop through nodes
	while (*pHead != NULL)
	{
		//	assign temp to dereferenced pHead
        temp = *pHead;
		//	move pHead to next node in linked list 
        *pHead = (*pHead)->next;
		//	delete temp
        free(temp);
    }

}

int main(void)
{
	int i, strLen, numInputs;
	node* head = NULL;
	char* str;
	char c;
	FILE* inFile = fopen("input.txt","r");

	fscanf(inFile, " %d\n", &numInputs);
	
	while (numInputs-- > 0)
	{
		fscanf(inFile, " %d\n", &strLen);
		for (i = 0; i < strLen; i++)
		{
			fscanf(inFile," %c", &c);
			insertChar(&head, c);
		}

		str = toCString(head);
		printf("String is : %s\n", str);

		free(str);
		deleteList(&head);

		if (head != NULL)
		{
			printf("deleteList is not correct!");
			break;
		}
	}

	fclose(inFile);
}
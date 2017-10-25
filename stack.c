#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "global.h"

#define size 100



//struct stackT
//{
//	int array[size];
//	int top;
//};


// function to create a stack of a given size
struct stackT* createStack()
{
	struct stackT* sStack = (struct stackT*)malloc(sizeof(struct stackT));
	sStack ->top = -1;
	

	int i;
	for(i=0;i<SIZE;i++)
	    sStack->array[i] = (char*)malloc(sizeof(char)*5); 


	return sStack;
}


// function to check if the stack is full or not
int isFull(struct stackT* aStack)
{
	return ((aStack->top)==SIZE);
}


// function to check if the stack is empty or not

int isEmpty(struct stackT* aStack)
{
	return ((aStack->top)==-1);
}


// function to push a number into  stack
void push(struct stackT* aStack,char* reg)
{
	if(isFull(aStack))
		return;
	int i;
	strcpy(aStack->array[++aStack->top],reg);
//	printf("%s pushed into stack\n",aStack->array[aStack->top]);
//	for(i=0;i<=aStack->top;i++)
//		printf("Element : %s\n",aStack->array[i]);
//	printf("size is %d\n",aStack->top);
}



// function to pop a number from the stack
char* pop(struct stackT* aStack)
{
	char *str;
	str = (char*)malloc(sizeof(char)*5);
	if(isEmpty(aStack))
		return NULL;
//	printf("size is %d\n",aStack->top);
//	printf("Top String %s",aStack->array[aStack->top]);
	//strcpy(str,aStack->array[aStack->top--]);
	str = aStack->array[aStack->top];
//	printf("Popped string is %s\n",str);
	aStack->top--;
	return str;
}




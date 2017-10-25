#ifndef STACK_H_
#define STACK_H_


// a function to create an empty stack
struct stackT* createStack();


// a function to check if a stack is full or not
int isFull (struct stackT* aStack);


// a function to check if the stack is empty ir not
int isEmpty (struct stackT* aStack);


// a function to push a number into a stack
void push (struct stackT* aStack,char* reg);


// a function to pop a number from a stack
char*  pop (struct stackT* aStack);



#endif 

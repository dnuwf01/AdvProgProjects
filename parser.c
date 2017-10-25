/**
 *
 * The parse file reads the document from the file and checks if it is a legal statement or not.
 *
  	
 * @author Debarghya Nandi
 *
 */ 



#include <string.h>
#include "global.h"
#include "stack.h"



int lookahead;



/**
 *
 * Parses a given set of statements
 * @param the file name to be read
 * */

parse(char* file)
{
  
  fp = fopen(file,"r");   // reads the given file
  lookahead = lexan(fp);
  match(BEGIN);   // matches BEGIN of file
  myStack = createStack();
  regCounter=1;
  currRegister = (char*)malloc(sizeof(char)*5);
  blockReport = (char*)malloc(sizeof(char)* 1000);
  while(lookahead!=END && lookahead!=DONE) 
   {
	statement();
   }
  if(lookahead==DONE) error("Illegal Statement encountered !!!\n");
  else match(END);  // matches END of file
  error("Program legal: Successfully compiled !!!\n");
}







/**
 * A function that takes in the statement and select the particular operation to work on
 *
 * */

statement()
{
	
    
    switch(lookahead){
    case IF:
    	printf("GOTO L3\n");
	selectorIf();
	break;
    
    case ELSE:
	printf("GOTO L2\n");
	selectorElse();
	break;
    
    case WHILE:
    	printf("GOTO L1\n");
	iterator();
    	break;

    case ID:
  	 assignment();          
         break;
    case INT:
	emit(INT,tokenval);  // declaration
	declaration();
	break;
        
    case CONSTANT:
	constant_declaration();
	break;
    
    default:
	error("Illegal Statement encountered !!!!!!!\n");
	
  }	
 
}  


/****************************************
 * handles a declaration statement 
 * i.e int a;
****************************************/

declaration()
{
     match(INT);
     //printf("Printing the declared variable: %s",getLexeme());
     //struct symbolInfo* node = (struct symbolInfo*)malloc(sizeof(struct symbolInfo));
    // node = givePointer(getLexeme());
     if(check_decl_status(givePointer(getLexeme())))
	printf("Redeclaration Case!!!!!!!!!\n");
     else set_decl_status(givePointer(getLexeme()),TRUE);

    //struct symbolInfo* node = givePointer(getLexeme());
     //printf("Printing the accessNode value %d",accessNode(getLexeme()));
     match(ID);
     match(';');
}





/**
 *A function to carry out the operation of the iterator
* i.e. while(a>b)endwhile;
* **/


iterator()
{
  match(WHILE);
  expr();
  match(';');
  while(lookahead != ENDWHILE)
  {
        statement();
  }	
  match(ENDWHILE);
  match(';');
}






/**
 * A function to carry out the assignment operation
 * 
 * */

assignment()
{
  
  //expr();
 // struct symbolInfo* node = givePointer(getLexeme());
  if(!check_decl_status(givePointer(getLexeme()))) printf("Error::: Variable not declared !!!");
  //char *c = (char*)malloc(sizeof(char)*5); 
  //strcpy(c,getLexeme()); 
  match(ID);
  match('=');
  expr();
  
  //char* result = pop(myStack);
  printf("%s: = %s\n",getLexeme(),pop(myStack));
  match(';');
}







/**
 *
 *A function to implement the selector operation
 * 
 **/
selectorIf()
{
 if(lookahead == IF){
 match(IF);
 expr();
 pop(myStack);
 match(';');
 while(lookahead!=ENDIF)    // my selector block accepts a max of 10 statements, else it is impossible 
 {
	 statement();
 }
}
match(ENDIF);match(';');

// if(lookahead == ELSE){
  
 //  match(ELSE); 
  // while(lookahead!=ENDELSE)
//	statement();

 //} 
// match(ENDELSE);
// match(';');
}


selectorElse()
{
    if(lookahead == ELSE)
    {
	match(ELSE);
	while(lookahead!=ENDELSE)
		statement();
	
	match(ENDELSE);
	match(';');
    }
}








char* generateRegister()
{
	char* str;
	str = (char*)malloc(sizeof(char)*5);
	char* num;
	num = (char*)malloc(sizeof(char)*5);
	strcat(str,"r");
//	printf("one - %s\n",str);
	sprintf(num,"%d",regCounter);
	strcat(str,num);
//	printf("two - %s\n",str);
	regCounter++;
//	printf("Printing register value from generator: %s\n",str);
	return str;
}








/**
 *
 * A function to handle constant declaration
 *
 *
 * */


constant_declaration()
{
    emit(CONSTANT,tokenval);
    match(CONSTANT);
    emit(ID,tokenval);match(ID);
    while(lookahead==NUM)
    {
	match(NUM);
    }
}





/**
 *
 * The expression function representing the expression non-terminal for parsing
 *
  */


expr()
{
  //printf("expr"); 
  int t;
  char *c,*d;
  c = (char*)malloc(sizeof(char)*5);
  d = (char*)malloc(sizeof(char)*5);
  term();
  while(1) {
    switch(lookahead) {
      case '+': case '-':
        t = lookahead;
        match(lookahead); term();
	currRegister = generateRegister();
	c = pop(myStack);
	d = pop(myStack);
	printf("%s : = %s %c %s \n",currRegister,c,t,d);
	push(myStack,currRegister);
//	emit(t, NONE);
        continue;
      default:
        return;
    }
  } 
}





/**
 *
 *
 * The term function representing the term non - terminal for parsing
 *
 *
 *
 **/

term()
{
  //printf("term");
  int t;
  char *a,*b;
  a=(char*)malloc(sizeof(char)* 5);
  b = (char*)malloc(sizeof(char)*5);
  factor();
  while(1) {
    switch(lookahead) {
      case '*': case '/': case DIV: case MOD: case '<': case '>': case'=':case'!': case ':': case LE: case GE: case EE: case NE:
 	t = lookahead;
        match(lookahead);factor(); 
	currRegister = generateRegister();
	a=pop(myStack);
	b=pop(myStack);
	printf("%s : = %s %c %s \n",currRegister,a,t,b);
	
	
//	emit(t,NONE);
	continue;
      
     default:
 //       if(lookahead==NUM) factor();     // if we have multiple digits in a number
	return;
    }
  }

}




/**
 *
 *A factor function representing the factor non -terminal for parsing
 *
 * */


factor()
{
    //printf("factor");
    switch(lookahead) {
      case '(':
        match('('); expr(); match(')'); break;
      case NUM:
//	printf("pushing number into stack : %d\n",tokenval);
//	push(myStack,tokenval);
//	intVal =(intVal*10)+tokenval;
//	match(NUM); if(lookahead == NUM) factor();
	printf("Printing tokenval: %d",tokenval);
	currRegister = generateRegister();
	push(myStack,currRegister);
	printf("%s : = %d\n",currRegister,tokenval); *currRegister = '\0';
//	intVal=0;
//	emit(NUM,intVal); break;
  //      emit(NUM, tokenval);
        match(NUM); break;
      case ID:
	if(!check_decl_status(givePointer(getLexeme()))) printf("Error :: Variable not declared !!\n");
	currRegister = generateRegister();
	push(myStack,currRegister);
	printf("%s : = %s\n",currRegister,getLexeme()); * currRegister = '\0';
	
//	emit(ID, tokenval); 
	match(ID); break;
      default:
        error("Illegal statement encountered !!!!\n");
    }
  
}




/***
 *
 * Matches a given entity with the present lookahead, if match proceeds to the next lookahead, else gives an error
 *
 *
 */



match(int t)
{
  if(lookahead == t)
   {
	 lookahead = lexan(fp);
   }
  else
  {
      	printf("lookahead -> %d\n",lookahead);
	printf("to match -> %d\n",t);
	error("Illegal statement encountered !!!!!\n");
       
  }
}


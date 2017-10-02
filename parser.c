/**
 *
 * The parse file reads the document from the file and checks if it is a legal statement or not.
 *
 * @author Debarghya Nandi
 *
 * 
 *
 *
 * */








#include "global.h"




int lookahead;



/**
 *
 * Parses a given set of statements
 *
 * */

parse(char* file)
{
  
  fp = fopen(file,"r");   // reads the given file
  lookahead = lexan(fp);
  match(BEGIN);   // matches BEGIN of file

  statement();

  match(END);  // matches END of file
  exit(1);
}







/**
 * A function that takes in the statement
 *
 * */

statement()
{
	
while(lookahead != END){ 
    
    switch(lookahead){
    case IF:
    	selector();
	break;
    
    case WHILE:
    	iterator();
    	break;

    case ID:
  	 assignment();
         break;
    case INT:
	emit(INT,tokenval); 
	match(INT);
	continue;
        
    case CONSTANT:
	constant_declaration();
	break;
    default:
	
	error("No action\n");
  }	
  }
}  






/**
 *A function to carry out the operation of the iterator
* 
**/


iterator()
{
  match(WHILE);
  expr();
  match(';');
}






/**
 * A function to carry out the assignment operation
 *
 * */

assignment()
{
  expr();
  match(';');
}







/**
 *
 *A function to implement the selector operation
 * 
 * */
selector()
{
 match(IF);
 expr();
 match(';');
}







/**
 *
 *A function to handle constant declaration
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
 * */


expr()
{
 
  int t;
  term();
  while(1) {
    switch(lookahead) {
      case '+': case '-':
        t = lookahead;
        match(lookahead); term(); emit(t, NONE);
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
 
  int t;
  factor();
  while(1) {
    switch(lookahead) {
      case '*': case '/': case DIV: case MOD: case '<': case '>': case'=': case ':': case LE: case GE: case EE:
 	t = lookahead;
        match(lookahead);factor(); emit(t,NONE);
	continue;
      
     default:
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
    switch(lookahead) {
      case '(':
        match('('); expr(); match(')'); break;
      case NUM:
        emit(NUM, tokenval);match(NUM); break;
      case ID:
	emit(ID, tokenval); match(ID); break;
      default:
        error("syntax error factor");
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
      error("syntax error match");
       
  }
}

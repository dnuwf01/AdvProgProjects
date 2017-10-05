/**
 *
 * The parse file reads the document from the file and checks if it is a legal statement or not.
 *
  	
 * @author Debarghya Nandi
 *
 */ 




#include "global.h"




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
    	selector();
	break;
    
    case WHILE:
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
  
  expr();
  match(';');
}







/**
 *
 *A function to implement the selector operation
 * 
 **/
selector()
{

 match(IF);
 expr();
 match(';');
 while(lookahead!= ENDIF)    // my selector block accepts a max of 10 statements, else it is impossible to check for missing endif, results in an infinite      
 {
    statement();
 }
 
 match(ENDIF);
 match(';');
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
      case '*': case '/': case DIV: case MOD: case '<': case '>': case'=':case'!': case ':': case LE: case GE: case EE: case NE:
 	t = lookahead;
        match(lookahead);factor(); emit(t,NONE);
	continue;
      
     default:
        if(lookahead==NUM) factor();     // if we have multiple digits in a number
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
      error("Illegal statement encountered !!!!!\n");
       
  }
}

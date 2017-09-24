
#include "global.h"

int lookahead;

parse()
{
 //printf("entered parse"); 
 lookahead = lexan();
  match(BEGIN);
 // printf("completed begin");
  while(lookahead != END){ 
    
    if(match(IF))
    {
	expr();match(';');
    }
    else if(match(WHILE))
    {
	expr();match(';');
    }
    else if(lookahead==ID){
  	 expr(); 
    	match(';');
    }
    else
	{
		error("syntax error\n");
	}
  }
  match(END);
}

expr()
{
  printf("expr");
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

term()
{
  printf("term");
  int t;
  factor();
  while(1) {
    switch(lookahead) {
      case '*': case '/': case DIV: case MOD: case '<': case '>':case'=':
        t = lookahead;
        match(lookahead); 
	if(t== '<' || t == '>' || t=='='){
		if(lookahead!='=')
		{
			factor(); emit(t, NONE);
			continue;
		}
		else 
		{
			int t1 = lookahead;
			lookahead=lexan();
			factor();	
			emit(t,NONE);
			emit(t1,NONE);
			//lookahead=lexan();
	     	}
	}
	else 
	{
		factor();emit(t,NONE);
	}
        continue;
      
      default:
        if(constant == 1) factor;
	else return;
    }
  }

}


factor()
{
    printf("factor");
    switch(lookahead) {
      case '(':
        match('('); expr(); match(')'); break;
      case NUM:
        emit(NUM, tokenval); match(NUM);constant=0; break;
      case ID:
	printf("printing ID");emit(ID, tokenval); match(ID); break;
     // case IF:
  //	emit(IF,tokenval);match(IF);expr();break;
    //  case WHILE:
//	emit(WHILE,tokenval); match(WHILE); expr(); break;
      default:
        error("syntax error factor");
    }
  
}

int match(int t)
{
  if(lookahead == t)
   {
	// printf("matched: %d",t);
	 lookahead = lexan();
	 return 1;
   }
  else
  {
       //printf("Lookahead %d",lookahead);
      // printf(" to match ->>%d",t);
     //  printf("syntax error match");
       return 0;
       
  }
}

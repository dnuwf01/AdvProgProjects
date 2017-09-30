
#include "global.h"

int lookahead;

parse()
{
 //printf("entered parse"); 
  fp = fopen("file1.txt","r");
  lookahead = lexan(fp);
  match(BEGIN);
 // printf("completed begin");
  while(lookahead != END){ 
    
    switch(lookahead){
    case IF:
    	match(IF);expr();match(';');
	break;
    
    case WHILE:
    	match(WHILE);expr();match(';');
    	break;

    case ID:
  	 expr(); 
       	 match(';');
         break;
    case INT:
	emit(INT,tokenval); 
	match(INT);
	 continue;
        // expr(); match(';');
	 //break; 
    case CONSTANT:
	emit(CONSTANT,tokenval);
	match(CONSTANT);
	emit(ID,tokenval);match(ID);
	while(lookahead==NUM)
	{
		match(NUM);
	}
	break;
    default:
	//printf("No action lookahead %d\n",lookahead);
	error("No action\n");
	
  }
}
  match(END);
  exit(1);
}

expr()
{
 // printf("expr");
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
 // printf("term");
  int t;
  factor();
  while(1) {
    switch(lookahead) {
      case '*': case '/': case DIV: case MOD: case '<': case '>': case'=': case ':': case LE: case GE: case EE:
 //       printf("check1\n");
	t = lookahead;
        match(lookahead);factor(); emit(t,NONE);
	continue;
      
     default:
//	 printf("lookahead is %c\n",lookahead);
         return;
    }
  }

}


factor()
{
//    printf("factor");
    switch(lookahead) {
      case '(':
        match('('); expr(); match(')'); break;
      case NUM:
        emit(NUM, tokenval);match(NUM); break;
      case ID:
	emit(ID, tokenval); match(ID); break;
     // case IF:
  //	emit(IF,tokenval);match(IF);expr();break;
    //  case WHILE:
//	emit(WHILE,tokenval); match(WHILE); expr(); break;
      default:
        error("syntax error factor");
    }
  
}

match(int t)
{
  if(lookahead == t)
   {
//	 printf("matched: %d\n",t);
	 lookahead = lexan(fp);
//	 printf("ne ->tval %d\n",tokenval);
//	 printf("next-> %d\n",lookahead);
	 
	 //return 1;
   }
  else
  {
       printf("Lookahead %d",lookahead);
       printf(" to match ->>%c",t);
      error("syntax error match");
      // return 0;
       
  }
}

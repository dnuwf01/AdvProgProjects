
#include "global.h"

emit(int t, int tval)
{
      switch(t) {
    //  printf("%d",t);	
      case '+': case '-': case '*': case '/':
          printf("%c\n",t); break;
      case DIV:
          printf("DIV\n"); break;
      case MOD:
          printf("MOD\n"); break;
      case NUM:
          printf("%d\n", tval); break;
      case ID:
          printf("%s\n",getLexeme()); break;
      case IF:
	  printf("IF");
      case WHILE:
	  printf("WHILE");
      case '<': case'>': case'=':
	  printf("%c\n",t);break;
      default:
	printf("The charcter is  %c",t);
        error("token %d, tokenval %d\n", t, tval);
    }
}

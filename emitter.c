/**
 *
 * The emitter file for the project
 *
 * @author Debarghya Nandi
 *
 *
 *
 * */
#include "global.h"

emit(int t, int tval)
{
      switch(t) {
      case '+': case '-': case '*': case '/':
          printf("%c\n",t); break;
      case DIV:
          printf("DIV\n"); break;
      case MOD:
          printf("MOD\n"); break;
      case NUM:
          printf("%d\n",tval); break;
      case ID:
          printf("%s\n",getLexeme()); break;
      case IF:
	  printf("IF");
      case WHILE:
	  printf("WHILE");
      case '<': case'>': case'=': case'!': 
	  printf("%c\n",t);break;
      case LE:
	  printf("<=\n"); break;
      case GE:
	  printf(">=\n"); break;
      case EE:
	  printf("==\n"); break;
      case NE:
	  printf("!=\n"); break;
      case INT:
	  printf("INT\n"); break;
      case CONSTANT:
	  printf("Constant Declaration:\n"); break;
      case ':':
	  printf(""); break;
      default:
	printf("The charcter is  %c",t);
        error("token %d, tokenval %d\n", t, tval);
    }
}

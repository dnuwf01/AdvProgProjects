/**

This one follows the regular grammar to produce lexemes and and it is later evaluated whether its a token or not
*/




#include "global.h"

char lexbuf[BSIZE];

int lineno = 1;
int tokenval =  NONE;

// returns the token from the text
int lexan()
{
  int t;
  while(1)  {
    t = getchar(); // stores the next val
    if (t == ' ' || t == '\t')
      ;
    else if (t == '\n')
      lineno++;
    else if (isdigit(t)) {
      ungetc(t, stdin);
      scanf("%d", &tokenval);
      return NUM;
    }

    else if (isalpha(t)) {
      int p, b = 0;
      while (isalnum(t)) { // if alpha numeric
        lexbuf[b] = t;
        t = getchar();
        b++;
        if(b >= BSIZE)
          error("compiler error");
      }  
      lexbuf[b] = EOS; // put the last character as end of string
      if(t != EOF)   
        ungetc(t, stdin);
      p = lookup(lexbuf); // check if it is a preexisting symbol
      if(p==NOT_FOUND)
        p = insert(lexbuf, ID); // if it's not there insert the symbol with a value
      tokenval = p;  // returns the last entry to the symbol table
      return getTokenType(p); // returns the token type of the last symbol
    }

    else if (t == EOF)
      return DONE;

    else {
      tokenval = NONE;
      return t;
    }

  }
}

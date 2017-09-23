
#include "global.h"

#define STRMAX 999
#define SYMMAX 999



/**
this structure contains the actual token and an optional value attributed to it
*/
struct entry {
	char *lexptr;
	int token;
};

// we create an array of the structure
struct entry symtable[SYMMAX];

// the *lexptr points to the array here
char lexemes[STRMAX];

int lastchar = -1;   // index for the lexeme table
int lastentry = 0; // index for the symbol table


// contains some reserved keywords and their values
struct entry keywords[] = {
   "begin",BEGIN,
   "end", END,
   "div", DIV,
   "mod", MOD,
   0 , 0
};

init()
{
  struct entry *p;
  for(p = keywords; p->token; p++) // this loop starts with the base address of keywords and loops through it till it has a value to it
    insert(p->lexptr, p->token); // makes a call to the insert function
}

// checks if the string is already in the symbol table
int lookup(char s[])
{
   int p;
   for(p = lastentry; p > 0; p--)
    if(! strcmp(symtable[p].lexptr, s) )
       return p;
       
   return NOT_FOUND;
}

int insert(char s[], int tok)
{
  int len;
  len = strlen(s); // calculates the length of the string
  if(lastentry + 1 >= SYMMAX) 
     error("symbol table full"); // checks if the symbol table is full
  if (lastchar + len + 1 >= STRMAX)
     error("lexeme array full");  // checks if the lexeme array is full
  lastentry = lastentry + 1; // increment the entry value
  symtable[lastentry].token = tok; // fix the new value of the lexeme
  symtable[lastentry].lexptr = &lexemes[lastchar + 1]; // fix the pointer to the next lexeme in the lexeme array
  lastchar = lastchar + len + 1;    // increment the index of the lexeme array by the size of the previous lexeme
  strcpy(symtable[lastentry].lexptr, s);  // copy the string in the lexptr array
  return lastentry;   // returns the last entry of the symbol table
}

char * getLexeme(int pos)
{
  return symtable[pos].lexptr;
}

int getTokenType(int pos)
{
  return symtable[pos].token;
}

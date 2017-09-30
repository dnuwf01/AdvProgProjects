
#include "global.h"
#include <string.h>
#define STRMAX 999
#define SYMMAX 999



/**
 * This structure contains the token,tokentype, and the pointer to the next datastructure
 *
 *  *
 */
struct symbolInfo{
	
	char lexptr[STRMAX];
	int tokentype;
	struct symbolInfo* next;
};

// a string array to keep the lexeme
char lexemeArr[SYMMAX];


/**
this structure contains the actual token and an optional value attributed to it
*/
struct entry {
	char lexptr[SYMMAX];
	int token;
};

// we create an array of the structure
//struct entry symtable[SYMMAX];

// the *lexptr points to the array here
//char lexemes[STRMAX];

//int lastchar = -1;   // index for the lexeme table
//int lastentry = 0; // index for the symbol table


// create  a hash table 
struct symbolInfo hashArray[SYMMAX];




// contains some reserved keywords and their values
struct entry keywords[] = {
   "begin",BEGIN,
   "end", END,
   "div", DIV,
   "mod", MOD,
   "if",IF,
   "while",WHILE,
   "<=",LE,
   ">=",GE,
   "==",EE,
   "int",INT,
   "def",CONSTANT,
   0 , 0
};

init()
{
  //printf("entered init");
  // allocating memory for the hashArray
//  hashArray = (struct symbolInfo*)malloc(sizeof(struct symbolInfo)*SYMMAX);

  struct entry *p;
  for(p = keywords; p->token; p++) // this loop starts with the base address of keywords and loops through it till it has a value to it
    insert(p->lexptr, p->token); // makes a call to the insert function
}

// checks if the string is already in the symbol table
/*
int lookup(char s[])
{
   int p;
   for(p = lastentry; p > 0; p--)
    if(! strcmp(symtable[p].lexptr, s) )
       return p;
       
   return NOT_FOUND;
}
*/

// a function to lookup for the given string in the hash table
// returns the hash value of the given table.
int lookup(char s[])
{
	int val=hashval(s);
	struct symbolInfo* aNode = &hashArray[val];
//	printf("The entered string is %s and the first value at hashArray index is %s",s,hashArray[val].lexptr);
	if(strcmp(aNode->lexptr,s)==0)
	{
//		printf("found if !!!");
		return aNode->tokentype;
	}
	else
	{
		while(aNode)
		{
			if(strcmp(aNode->lexptr,s)==0)
			{
//				printf("found else !!!");
				return aNode->tokentype;
			} 
		aNode = aNode->next;
		}	
	}
	return NOT_FOUND;
}


/*
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
*/

// a function to insert into the hash table
int insert(char s[], int tok)
{
	

	// create a new node for symbolInfo
	struct symbolInfo* node = (struct symbolInfo*)malloc(sizeof(struct symbolInfo));
//	printf("copying string");
	strcpy(node->lexptr,s);
//	printf("copying tokentype");
	node->tokentype=tok;
//	printf("initialise next");
	node->next=NULL;

//	printf("check insert %s",node->lexptr);

	//check for the hash value and insert it into the table accordingly
	int hval = hashval(s);
	// initialise a pointer to the hashed value
	struct symbolInfo* anchor = &hashArray[hval];	





	if(anchor->lexptr[0]=='\0')
	{
		strcpy(anchor->lexptr,s);
		anchor->tokentype=tok;
		anchor->next=NULL;
//		printf("inserted if%s",hashArray[hval].lexptr);
		return anchor->tokentype;
	}
	else
	{
//		printf("The garbage string at this index is %s",anchor->lexptr);
		struct symbolInfo* aNode = anchor;
		while(aNode)
		{
			aNode= aNode->next;
		}
		aNode = node;
//		printf("inserted else  %s",aNode->lexptr);
		return aNode->tokentype;
	}
}
/*
char * getLexeme(int pos)
{
  return symtable[pos].lexptr;
}
*/



// a function to set the given lexeme
void setLexeme(char s[])
{
	strcpy(lexemeArr,s);
}









// a function to return the given lexeme
char* getLexeme()
{
	return lexemeArr;
}










// function to return the tokentype
int getTokenType(int i)
{
	return i;
}





/*
int getTokenType(int pos)
{
  return symtable[pos].token;
}

*/


// a function to calculate the hash value for a given string and return it
int hashval(char str[])
{
    int i=0;
    int val=0;
    while(str[i]!='\0')
    {
	val+=str[i];
	i++;
    }
//    printf("The hash value is %d",val%SYMMAX);
   return val%SYMMAX;
}

/**
 *
 *  In this file, we implement the symbol structure using a hash table.
 *  We use a symbolInfo datastucture, which contains the lexptr array, tokentype and a pointer to the next symbol pointer.
 *  In case of collision the open hashing is done to link a new node to the already popuated index.
 *
 *  @author Debarghya Nandi
 *
 *
 *
 *
 * */




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

/* a string array to keep the lexeme*/
char lexemeArr[SYMMAX];


/**
this structure contains the actual token and a tokentype value attributed to it
*/
struct entry {
	char lexptr[SYMMAX];
	int token;
};


// creates  a hash table 
struct symbolInfo hashArray[SYMMAX];




// contains some reserved keywords and their values
struct entry keywords[] = {
   "begin",BEGIN,
   "end", END,
   "div", DIV,
   "mod", MOD,
   "if",IF,
   "endif",ENDIF,
   "while",WHILE,
   "endwhile",ENDWHILE,
   "<=",LE,
   ">=",GE,
   "==",EE,
   "!=",NE,
   "int",INT,
   "def",CONSTANT,
   0 , 0
};

init()
{

  struct entry *p;
  for(p = keywords; p->token; p++) // this loop starts with the base address of keywords and loops through it till it has a value to it
    insert(p->lexptr, p->token); // makes a call to the insert function
}


/**
 *
 * This function looks up the symbol table, to see if a specific symbol is already present in the symbol table or not.
 * @param the lexeme string to be looked up
 * @return the tokentype if present
 * else returns -1
 *
 * */
int lookup(char s[])
{
	int val=hashval(s);
	struct symbolInfo* aNode = &hashArray[val];
	if(strcmp(aNode->lexptr,s)==0)
	{
		return aNode->tokentype;
	}
	else
	{
		while(aNode)
		{
			if(strcmp(aNode->lexptr,s)==0)
			{
				return aNode->tokentype;
			} 
		aNode = aNode->next;
		}	
	}
	return NOT_FOUND;
}

/**
 *
 * This function inserts a new symbol into the symbol table. The hashvalue of the symbol is calculated in the hashVal function and then nodes are traversed to 
 * insert the new node.
 * @param s[]: the lexeme string to be inserted
 * @param tok : the tokentype for the lexeme string
 * @return the tokentype after inserting
 * 
 *
 * */
int insert(char s[], int tok)
{
	

	// create a new node for symbolInfo
	struct symbolInfo* node = (struct symbolInfo*)malloc(sizeof(struct symbolInfo));
	strcpy(node->lexptr,s);
	node->tokentype=tok;
	node->next=NULL;


	//check for the hash value and insert it into the table accordingly
	int hval = hashval(s);
	// initialise a pointer to the hashed value
	struct symbolInfo* anchor = &hashArray[hval];	





	if(anchor->lexptr[0]=='\0')
	{
		strcpy(anchor->lexptr,s);
		anchor->tokentype=tok;
		anchor->next=NULL;
		return anchor->tokentype;
	}
	else{
		struct symbolInfo* aNode = anchor;
		while(aNode)
		{
			aNode= aNode->next;
		}
		aNode = node;
		return aNode->tokentype;
	}
}



/**
 *  A function to set the current lexeme array
 *  @param the lexeme to be set
 */  

void setLexeme(char s[])
{
	strcpy(lexemeArr,s);
}









/**
 *  A function to return the current lexeme array
 *  @return the lexeme
 */
  
char* getLexeme()
{
	return lexemeArr;
}



/**
 * A function to return the tokentype
 * @return the tokentype
 */


int getTokenType(int i)
{
	return i;
}






/**
 *  A function to calculate the hash value for a given string and return it. Hash value is calculated based on the ASCII value.
 *  @param str: the lexeme string for which the hash value is to be calculated
 *  @return the hash value.
 */

  
int hashval(char str[])
{
    int i=0;
    int val=0;
    while(str[i]!='\0')
    {
	val+=str[i];
	i++;
    }
   return val%SYMMAX;
}

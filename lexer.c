/**
* This one follows the regular grammar to produce lexemes and and it is later evaluated whether its a token or not
* 
* @author Debarghya Nandi
*
*
*/




#include "global.h"




char lexbuf[BSIZE];

int lineno = 1;
int tokenval =  NONE;

/**
 *  returns the tokentype from the character read
 *
 */

  
int lexan(FILE* fp)
{
 
  int t;
  char c;
  
 


 while(1)  {
    t = getc(fp); //  gets the next character from the file
    
    if (t == ' ' || t == '\t')    // if tab space/space found we move to the next character
      ;
    else if (t == '\n')    // if newline found we move to the next line
      lineno++;
    
    else if (isdigit(t)) {   // if a digit is found we return NUM
      tokenval=t;
      return NUM;
    }
    
    else if(t=='<')            // if we get a < sign we take the next character to check for '=', then return accordingly
    {
	while((c=getc(fp))==(' ' || '\n'));
	if(c == '='){
	  int k = lookup("<=");
		if(k!=NOT_FOUND)
			return getTokenType(k);
	}
	else {
	    ungetc(c,fp);
	    tokenval=NONE;
	    return t;    	
	}
	   
    }
    
    else if(t=='>')            // if we get a > sign we take the next character to check for '='. then return accordingly
    {
	while((c=getc(fp))==(' ' || '\n'));
	if(c == '='){
	  int k = lookup(">=");
		if(k!=NOT_FOUND)
			return getTokenType(k);
	}
	else {
	    ungetc(c,fp);
	    tokenval=NONE;
	    return t;    	
	}
	   
    }
    
    else if(t=='=')            // if we get a = sign we take the next character to check for '=', then return accordingly
    {
	while((c=getc(fp))==(' ' || '\n'));
	if(c == '='){
	  int k = lookup("==");
		if(k!=NOT_FOUND)
			return getTokenType(k);
	}
	else {
	    ungetc(c,fp);
	    tokenval=NONE;
	    return t;    	
	}
	   
    }
    else if(t=='#')          // set the flag for defining constant, the command being #def constant
    {
	cflag=1;
    }
    else if(isalpha(t) && cflag==1)      // check for #def constant
    {
      int p=0;
      int b=0;
      c=t;
      while(isalnum(t)){
	lexbuf[b]=t;
	t=getc(fp);
	b++;
	if(b>= BSIZE)
	   error("compiler error");
     }
     lexbuf[b]=EOS;
     	
     if(t!=EOF)
	ungetc(t,fp);
	
     if(strcmp(lexbuf,"def")==0){
	p= lookup(lexbuf);
     	tokenval=p;setLexeme(lexbuf);
	cflag=0;
     	return CONSTANT;
     }
     else error("constant error!");
	
    }	
    
    else if(t=='$')                        // check for the $ sign, as it represents the beginning of a comment line.
    {

	while((t=getc(fp))!='\n');
	lineno++;
	// ignore whole line
	printf("Comment line!!!!\n");
	
    }	
   	
    else if (isalpha(t) && cflag==0){         // the condition for any alphanumeric input
      int p, b = 0;
      int ct=0;
      while (isalnum(t) || t=='_') { // if alpha numeric
        lexbuf[b] = t;
        t = getc(fp);
	if(lexbuf[b]=='_' && t=='_') error("Cannot have consecutive underscores for identifier !!!!\n");	
        b++;
        if(b >= BSIZE)
          error("compiler error");
      }  
      lexbuf[b] = EOS; // put the last character as end of string
      
      if(lexbuf[b-1]=='_') error("Identifier name cannot end with underscore !!!!\n");

      







 
      if(t != EOF)   
        ungetc(t, fp);
      p = lookup(lexbuf); // check if it is a preexisting symbol
      if(p==NOT_FOUND)
        p = insert(lexbuf, ID); // if it's not there insert the symbol with a value
      tokenval = p;  // returns the last entry to the symbol table
      setLexeme(lexbuf);
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

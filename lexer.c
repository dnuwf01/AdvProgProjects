/**

This one follows the regular grammar to produce lexemes and and it is later evaluated whether its a token or not
*/




#include "global.h"




char lexbuf[BSIZE];

int lineno = 1;
int tokenval =  NONE;

// returns the token from the text
int lexan(FILE* fp)
{
 // printf("entered lexan\n");
  int t;
  char c;
  
  while(1)  {
    t = getc(fp); // stores the next val
  //  printf("la: %c\n",t);
    //printf(isdigit(t));
    if (t == ' ' || t == '\t')
      ;
    else if (t == '\n')
      lineno++;
    else if (isdigit(t)) {
     // printf("number found");
      tokenval=t;
      return NUM;
    }
    else if(t=='<')
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
    
    else if(t=='>')
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
    
    else if(t=='=')
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
    else if(t=='#')
    {
	cflag=1;
    }
    else if(isalpha(t) && cflag==1)
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
	
     //printf("%s",lexbuf);
     if(strcmp(lexbuf,"def")==0){
     //	printf("constant decl\n");
	p= lookup(lexbuf);
     	tokenval=p;setLexeme(lexbuf);
     //	printf("token value %d\n",tokenval);
	cflag=0;
     	return CONSTANT;
     }
     else error("constant error!");
	
    }	
    
    else if(t=='$')
    {

       //  printf("che ");
	while((t=getc(fp))!='\n');
	lineno++;
	// ignore whole line
	printf("Comment line!!!!\n");
	
    }	
   	
    else if (isalpha(t) && cflag==0) {
     // printf("che ");
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
 //     printf("The result of lookup is %d",p);
      if(p==NOT_FOUND)
        p = insert(lexbuf, ID); // if it's not there insert the symbol with a value
      tokenval = p;  // returns the last entry to the symbol table
      setLexeme(lexbuf);
//      printf("lexer cholche!");
      return getTokenType(p); // returns the token type of the last symbol
    }

    else if (t == EOF)
      return DONE;

    else {
      //printf("che");
      tokenval = NONE;
      return t;
    }

  }
}

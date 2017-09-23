/**

Notes

Lexing/ tokenization is the process of converting a sequence of characters into a sequence of tokens.A program that performs lexical analysis 
is called a lexer.A lexer is generally combined with a parser, which together analyze the syntax of programming languages, web pages and so forth


A lexeme is a sequence of characters in the source program that matches the pattern for a token and is identified by a lexical analyzer
as an instance of the token.

A lexical token is the pair of a token name and an optional token value. The token name is the category of lexical unit.
e.g. 

identifier: x
keyword: if,while

The specification includes a set of rules, the lexical grammar that defines the lexical syntax. The lexical grammar consists of regular expressions
that define the set of possible character seequences of a token.

Tokenization refers to process of demarcating and possibly classifying sections of a token.
The parser retrieves the information from the lexer and stores it in an abstract syntax tree.This is necessary to avoid information loss.

Tokens are identified by the basic rules of lexer:
regular expressions  (REgex: translates an expression into an internal representation which can be executed and matched against a string 
representing the text being searched in)

specific sequences of characters followed by a flag
specific separating characters called delimiters
they are basically categorized as identifiers,operators, grouping symbols etc
A lexical analyser  just takes in the parenthesis as tokens, but does nothing to match '(' with ')'
---- they are loaded into datastructures for parsing

the first stage scanner is based on a FSM.
-- it has encoded within it information on the possible sequences of characters that are contained within any of the token it includes.
int -- may contain a series of numeric characters
  starts with first non-white space /..... goes on till../ till it reaches a character which does not match the sequence.
  
  evaluator goes over the lexeme to produce a value.
  mostly, there is no value.
  
  net_worth = ( assets - liabilities);
  
  
  identifier net_worth
  equal
  open parenthesis
  identifier assets
  minus
  identifier liabilities
  close parenthesis
  semi colon
   
   







*/






#include <stdio.h>
#include "global.h"

main()
{
  init();  // calls the init function in the symbol file
  printf("\n\nEnter arithmetic expressions terminated\n");
  printf("with semicolons (;).\n");
  printf("Press <ctrl> c to quit\n\n->"); 
  parse();
  exit(0);
}

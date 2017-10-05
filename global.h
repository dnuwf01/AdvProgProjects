#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define BSIZE 128
#define NONE -1
#define EOS '\0'
#define NUM 256
#define DIV 257
#define MOD 258
#define ID 259
#define DONE 260
#define BEGIN 400
#define END 401
#define IF 402
#define WHILE 403
#define NOT_FOUND 0
#define LE 404
#define GE 405
#define EE 406
#define INT 407
#define CONSTANT 408
#define ENDIF 409
#define ENDWHILE 410
#define NE 411


int tokenval; // the tokentype for the lexeme
int lineno;   // the current line number for buffer read
int cflag;   // the flag is used to differentiate between normal id and constant #def

FILE* fp;    // file pointer 

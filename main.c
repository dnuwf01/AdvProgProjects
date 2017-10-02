/**
 * The main file for the project
 *
 * @author Debarghya Nandi
 *
 * */



#include <stdio.h>
#include "global.h"

main(int argc,char* argv[])
{

 if(argc!=2) 
     error("CommandLine Error:  <./final><FILENAME>\n");
  init();   
  parse(argv[1]);
  exit(0);
}

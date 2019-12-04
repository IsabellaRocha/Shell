#include "headers.h"

char ** parse_args( char * line, int tokens ){
  char ** args = malloc(tokens * sizeof(char *));
  int c = 0;
  char * token;
  while (line != NULL){
    token = strsep(&line, " ");
    args[c] = token;
    c++;
  }
  for (;c <= tokens - 1; c++){
    args[c] = NULL;
  }
  return args;
}

void exit(){
  
}

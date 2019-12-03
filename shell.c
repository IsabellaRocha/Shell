#include "headers.h"

char ** parse_args( char * line ){
  char ** args = malloc(6 * sizeof(char *));
  int c = 0;
  char * token;
  while (line != NULL){
    token = strsep(&line, " ");
    args[c] = token;
    c++;
  }
  for (;c <= 5; c++){
    args[c] = NULL;
  }
  return args;
}

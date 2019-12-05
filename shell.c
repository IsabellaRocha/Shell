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


void cd(char * path){
  int err = chdir(path);
  if (err == -1){
    printf("errno %d error: %s\n", errno, strerror(errno));
  }
}

void execute(char** args){
    if(strcmp(args[0], "cd") == 0) {
        cd(args[1]);
    }
    pid_t cPID;
    cPID = fork();
    if(cPID == 0) {
        execvp(args[0], args);
        exit(0);
    }
    else {
        wait(&cPID);
    }
}

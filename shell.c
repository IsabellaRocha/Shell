#include "headers.h"

char ** parse_args( char * line, char * delimiter ){
  char ** args = malloc(10 * sizeof(char *));
  int c = 0;
  char * token;
  while (line != NULL){
    token = strsep(&line, delimiter);
    args[c] = token;
    c++;
  }
  for (;c <= 10 - 1; c++){
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
    if(strcmp(args[0], "exit") == 0){
        exit(0);
        //break;
    }
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
    free(args);
}

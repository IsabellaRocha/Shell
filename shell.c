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
  char * fullPath = getcwd(path, 50);
  printf("%s\n", fullPath);
}

void execute(char** args){
    if(strcmp(args[0], "cd") == 0) {
        cd(args[1]);
    }
    else {
        pid_t cPID;
        cPID = fork();
        if(cPID == 0) {
            execvp(args[0], args);
            if(errno != 0) {
                printf("Error: %s", strerror(errno));
                kill(getpid(), SIGTERM);
            }
        }
        else {
            wait(NULL);
        }
    }
}

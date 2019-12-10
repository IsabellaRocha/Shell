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

int redirect_stdout(char * filename){
  int fd = open(filename, O_WRONLY);
  int backup = dup(STDOUT_FILENO);
  dup2(fd_FILENO, STDOUT_FILENO);
  return fd;
}

int redirect_stdin(char * filename){
  int fd = open(filename, O_RDONLY);
  int backup = dup(STDIN_FILENO);
  dup2(fd_FILENO, STDIN_FILENO);
  return fd;
}

int redirect_stdout_append(char * filename){
  int fd = open(filename, O_APPEND);
  int backup = dup(0);
  dup2(filename_FILENO, 0);
  return fd;
}

void execute(char** args){
    int status;
    if(strcmp(args[0], "cd") == 0) {
        cd(args[1]);
    }
    else {
        if(fork() == 0) {
          bool fileout = false;
          bool filein = false;
            int c = 0;
            for (c; c < 10; c++){
              if (strcmp(args[c], ">") == 0){
                int fdout = redirect_stdout(args[c+1]);
                fileout = true;
              }
              if (strcmp(args[c], "<") == 0){
                int fdin = redirect_stdin(args[c+1]);
                filein = true;
              }
              if (strcmp(args[c], ">>") == 0){
                int fdout = redirect_stdout_append(args[c+1]);
                fileout = true;
              }
            }
            execvp(args[0], args);
            if(errno != 0) {
                printf("Error: %s\n", strerror(errno));
                kill(getpid(), SIGTERM);
            }
            if (fileout){
              close(fdout);
            }
            if (filein){
              close(fdin);
            }
        }
        else {
            wait(&status);
        }
    }
}

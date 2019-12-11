#include "headers.h"

char ** parse_args( char * line, char * delimiter ){
    char * parse = extraSpace(line);
    char ** args = malloc(10 * sizeof(char *));
    int c = 0;
    char * token;
    while (parse != NULL){
        token = strsep(&parse, delimiter);
        args[c] = token;
        c++;
    }
    for (;c <= 10 - 1; c++){
        args[c] = NULL;
    }
    free(parse);
    return args;
}

char * extraSpace(char * line) {
    char arg[50];
    char newLine[50];
    strcpy(arg, line);
    int idx = 0;
    int cur = 0;
    bool space = false;
    while(idx < strlen(line) && arg[idx] == ' ') { //Get rid of leading spaces
        idx++;
    }
    while(idx < strlen(line)) {
        if(arg[idx] != ' ') {
            space = false;
            newLine[cur] = arg[idx];
            cur++;
            idx++;
        }
        if(arg[idx] == ' ' && space){
            idx++;
        }
        if(arg[idx] == ' ' && !space) {
            space = true;
            newLine[cur] = arg[idx];
            idx++;
            cur++;
        }
    }
    if(cur > 0 && newLine[cur - 1] == ' ') { //In case there's a space after the last charcter
        newLine[cur - 1] = '\0';
    }
    newLine[cur] = '\0'; //Null to terminate execvp
    char * parse = malloc(50 * sizeof(char));
    strcpy(parse, newLine);
    return parse;
}
int redirect_stdout(char * filename){
  int fd = open(filename, O_WRONLY);
  int backup = dup(STDOUT_FILENO);
  dup2(fd, STDOUT_FILENO);
  return fd;
}

int redirect_stdin(char * filename){
  int fd = open(filename, O_RDONLY);
  int backup = dup(STDIN_FILENO);
  dup2(fd, STDIN_FILENO);
  return fd;
}

int redirect_stdout_append(char * filename){
  int fd = open(filename, O_APPEND);
  int backup = dup(0);
  dup2(fd, 0);
  return fd;
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
    int status;
    if(strcmp(args[0], "cd") == 0) {
        cd(args[1]);
    }

    else {
        if(fork() == 0) {
          /*
          bool fileout = false;
          bool filein = false;
          int fdin;
          int fdout;
            int c = 0;
            for (; c < 10; c++){
              if (strcmp(args[c], ">") == 0){
                fdout = redirect_stdout(args[c+1]);
                fileout = true;
              }
              if (strcmp(args[c], "<") == 0){
                fdin = redirect_stdin(args[c+1]);
                filein = true;
              }
              if (strcmp(args[c], ">>") == 0){
                fdout = redirect_stdout_append(args[c+1]);
                fileout = true;
              }
            }
            */
            execvp(args[0], args);
            if(errno != 0) {
                printf("Error: %s\n", strerror(errno));
                kill(getpid(), SIGTERM);
            }
            /*
            if (fileout){
              close(fdout);
            }
            if (filein){
              close(fdin);
            }
            */
        }
        else {
            wait(&status);
        }
    }
}

#include "headers.h"

char ** parse_args( char * line, char * delimiter ){
    char arg[50];
    char newLine[50];
    strcpy(arg, line);
    int idx = 0;
    while(arg[idx] == ' ') {
        idx++;
    }
    int cur = 0;
    bool space = false;
    while(idx < strlen(line)) {
        if(arg[idx] != ' ') {
            newLine[cur] = arg[idx];
            space = false;
            cur++;
            idx++;
        }
        if(arg[idx] == ' ' && !space) {
            newLine[cur] = arg[idx];
            idx++;
            cur++;
            space = true;
        }
        if(arg[idx] == ' ' && space) {
            idx++;
        }
        newLine[cur] = arg[idx];
        idx++;
        cur++;
    }
    if(cur > 0 && newLine[cur - 1] == ' ') {
        newLine[cur - 1] = '\0';
    }
    char * parse = malloc(50 * sizeof(char));
    strcpy(parse, newLine);
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
            execvp(args[0], args);
            if(errno != 0) {
                printf("Error: %s\n", strerror(errno));
                kill(getpid(), SIGTERM);
            }
        }
        else {
            wait(&status);
        }
    }
}

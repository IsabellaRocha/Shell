#include "headers.h"

/*      char** parse_args()
Inputs: char * line -> The input string which we are parsing over
char * delimiter -> The string of characters we are looking for in line

Every time a delimiter is found in line, a new token is created and added to the array of arguments

This function returns an arry of arguments
*/
char ** parse_args( char * line, char * delimiter ){
    char * parse = removeSpace(line);
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

/*      char * removeSpace()
Inputs: char * line -> The input string in which we are removing the spaces from

First removes all leading spaces, then loops through line and removes any extra spaces

Returns a new string with all the extra spaces removed
*/
char * removeSpace(char * line) {
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

/*      void cd()
Inputs: char * path -> The path of the directory we are trying to reach

Passes path into chdir() to change directories
Does not return anything, simply changes directory
*/
void cd(char * path){
    int err = chdir(path);
    if (err == -1){
        printf("errno %d error: %s\n", errno, strerror(errno));
    }
    char * fullPath = getcwd(path, 50);
    printf("%s\n", fullPath);
}

/*      void redirect()
Inputs: char** args -> Array of arguments

If > < or >> is present in args, the stdout and stdin are moved in the file table
Does not return anything, only modifies the file table
*/

void redirect(char ** args) {
    int fd;
    int c = 0;
    char str1[50];
    char str2[50]; //In case there's > and < in the same line
    bool input = false;
    bool output = false;
    bool output2 = false;
    int backup = 0;
    for (; args[c] != NULL; c++){
        if (strcmp(args[c], ">") == 0){
            args[c] = NULL;
            strcpy(str2, args[c + 1]);
            output = true;
        }
        else if (strcmp(args[c], "<") == 0){ //Need else or else you're checking against null
            args[c] = NULL;
            strcpy(str1, args[c + 1]);
            input = true;
        }
        else if (strcmp(args[c], ">>") == 0){
            args[c] = NULL;
            strcpy(str2, args[c + 1]);
            output2 = true;
        }
    }
    if (input) {
        fd = open(str1, O_RDONLY, 0444);
        if (fd < 0){
            printf("errno %d error: %s\n", errno, strerror(errno));
        }
        backup = dup(STDIN_FILENO);
        dup2(fd, STDIN_FILENO);
        close(fd);
    }
    if (output2 || output) {
        if (output2) {
            fd = open(str2, O_WRONLY|O_APPEND, 0744);
            if (fd < 0){
                printf("errno %d error: %s\n", errno, strerror(errno));
            }
            backup = dup(STDOUT_FILENO);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
        else { //To make sure this only runs when >> isn't present because output will still be true if >> is present
            fd = open(str2, O_CREAT|O_WRONLY, 0744);
            if (fd < 0){
                printf("errno %d error: %s\n", errno, strerror(errno));
            }
            backup = dup(STDOUT_FILENO);
            dup2(fd, STDOUT_FILENO);
            close(fd);
        }
    }
}

/*      void pip()
Inputs: char** args -> Array of arguments

If | is present, uses popen() to read and write through a pipe
Does not return anything, simply connects the two arguments through a pipe
*/
void pip(char ** args) {
    FILE *in = popen(args[0], "r");
    FILE *out = popen(args[1], "w");
    char str[50];
    while(fgets(str, 50, in)) {
        fputs(str, out);
    }
    pclose(in); pclose(out);
}

/*      void execute()
Inputs: char** args -> Array of arguments

Checks if cd appears to call cd, then forks to a child process and calls redirect in case redirection is needed, and finally uses execvp to run the arguments in args
Does not return anything, simply executes the commands
*/
void execute(char** args){
    int status;
    if(strcmp(args[0], "cd") == 0) {
        cd(args[1]);
    }

    else {
        if(fork() == 0) {
            redirect(args);
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

#include "headers.h"

int main() {
    char line[50];
    while (strcmp(line, "exit") != 0) {
        printf("\n$ ");
        char** args;
        fgets(line, 50, stdin);
        char * checker;
        if ((checker = strchr(line, '\n')) != NULL) {
          *checker = '\0';
        }
        args = parse_args(line, ";"); //Take into account multple arguments at once
        int idx = 0;
        while (args[idx] != NULL && strcmp(args[idx], "exit") != 0) {
            char ** p = parse_args(args[idx], "|");
            if(p[1]) {
                pip(p);
            }
	    else {
                char **args2 = parse_args(args[idx], " ");
                execute(args2);
                free(args2);
            }
	    idx++;
	    free(p);
        }
        free(args);
    }
    return 0;
}

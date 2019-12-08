#include "headers.h"

int main() {
    char line[50];
    while (strcmp(args[0], "exit") != 0) {
        printf("$ ");
        char** args;
        fgets(line, 100, stdin);
        char * checker;
        if ((checker = strchr(line, '\n')) != NULL) {
          *checker = '\0';
        }
        args = parse_args(line, ";"); //Take into account multple arguments at once
        int idx = 0;
        while (strcmp(args[idx], "exit") != 0 && args[idx] != NULL) {
            char **args2 = parse_args(args[idx], " ");
            execute(args);
            idx++;
        }
    }
    return 0;
}

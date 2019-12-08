#include "headers.h"

int main() {
    char line[50];
    while (strcmp(line, "exit") != 0) {
        printf("$ ");
        char** args;
        fgets(line, 100, stdin);
        char * checker;
        line[strlen(line) - 1] = 0;
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

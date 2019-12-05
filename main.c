#include "headers.h"

int main() {
    bool input = false;
    char * line;
    while (true) {
        printf("$ ");
        char** args;
        if(strcmp(args[0], "exit") == 0) {
            exit(0);
        }
        if(strcmp(args[0], "cd") == 0){
            cd(args[1]);
        }
        fgets(line, 100, stdin);
        args = parse_args(line, 10);
        execute(args);
    }
    return 0;
}

#include "headers.h"

int main() {
    bool input = false;
    char * line;
    while (true) {
        printf("$ ");
        char** args;
        fgets(line, 100, stdin);
        args = parse_args(line, 10);
        if(strcmp(args[0], "exit") == 0){
            exit(0);
            break;
        }
        execute(args);
    }
    return 0;
}

#include "headers.h"

int main(int argc, char *argv[]) {
    bool running = true;
    bool input = false;
    printf("$ ");
    while (running) {
        char** args;
        if(sizeof(args) && input) {
            printf("$ ");
            input = false;
        }
    }
    return 0;
}

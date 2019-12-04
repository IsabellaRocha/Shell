#include "headers.h"

int main(int argc, char *argv[]) {
    bool running = true;
    bool input = false;
    printf("$ ");
    while (running) {
        char* args;
        if(strlen(args) == 0 && input) {
            printf("$ ");
            input = false;
        }
    }
    return 0;
}

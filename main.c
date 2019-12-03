#include "headers.h"

int main(int argc, char *argv[]) {
    boolean running = true;
    boolean input = false;
    printf("$ ");
    while (running) {
        char* args;
        if(strlen(args) == 0 && input) {
            printf("$ ");
            input = false;
        }
    }
}

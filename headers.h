#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <sys/stat.h>
#include <dirent.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

char ** parse_args( char * line, char * delimiter );
void cd(char * path);
void execute(char** args);
void redirect(char** args);
void pip(char ** args);
char * removeSpace(char * line);

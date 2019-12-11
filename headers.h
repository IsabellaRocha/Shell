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
char * extraSpace(char * line);
void cd(char * path);
void execute(char** args);
int redirect_stdout(char * filename);
int redirect_stdin(char * filename);
int redirect_stdout_append(char * filename);

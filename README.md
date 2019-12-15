# Shell assignment by Isabella Rocha and Claire Tempelman

Our shell implements:
- Basic commands using execvp
- Reading multiple lines separated by ;
- Basic redirection using < > and >>.
- Basic pipes using popen().

Features we were unsuccessful at implementing:
- Pressing up arrow for history.

Bugs:
- If one of the words in an input is over 50 characters, the shell throws an error (but it still runs).
- If you just input a blank command, the shell throws an error (but it still runs).
- Functions all work on linux, but may have different results in MacOS or Windows.

Files and function headers:
- main.c - handles taking in inputs using fgets() and executing commands.

- shell.c - handles execution.

    char** parse_args()
      Inputs: char * line -> The input string which we are parsing over\
      char * delimiter -> The string of characters we are looking for in line
      Every time a delimiter is found in line, a new token is created and added to the array of arguments
      This function returns an array of arguments

    char * removeSpace()
      Inputs: char * line -> The input string in which we are removing the spaces from
      First removes all leading spaces, then loops through line and removes any extra spaces
      Returns a new string with all the extra spaces removed

    void cd()
      Inputs: char * path -> The path of the directory we are trying to reach
      Passes path into chdir() to change directories
      Does not return anything, simply changes directory

    void redirect()
      Inputs: char** args -> Array of arguments
      If > < or >> is present in args, the stdout and stdin are moved in the file table
      Does not return anything, only modifies the file table

    void pip()
      Inputs: char** args -> Array of arguments
      If | is present, uses popen() to read and write through a pipe
      Does not return anything, simply connects the two arguments through a pipe

    void execute()
      Inputs: char** args -> Array of arguments
      Checks if cd appears to call cd, then forks to a child process and calls redirect in case redirection is needed, and finally uses execvp to run the arguments in args
      Does not return anything, simply executes the commands

Every function header:

    char ** parse_args( char * line, char * delimiter );
    void cd(char * path);
    void execute(char** args);
    void redirect(char** args);
    void pip(char ** args);
    char * removeSpace(char * line);

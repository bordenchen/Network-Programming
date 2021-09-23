// Design a shell in Linux using C
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>


#define MAXCOM 1000 // max number of letters to be supported
#define MAXLIST 100 // max number of commands to be supported

// Clear the shell using escape sequences
#define clear() printf("\033[H\033[J") 

// Greeting while initialize
void init_shell() 
{
    clear();
    printf("\n\n\n\n*****************************************");
    printf("\n\n\n\t***************SIMPLE SHELL**************");
    printf("\n\n\n\n*****************************************");
    char* username = getenv("USER");
    printf("\n\n\nUSER is: @%s" ,username);
    printf("\n");
    sleep(1);
    clear();
}

// Function to take input
int takeInput(char* str)
{
    char* buf;
    // readline(const char *prompt) - get a line from a user with editing
    buf = readline("\n>>> ");
    // size_t strlen (const char * str);
    if (strlen(buf) != 0) {
        // save the line in a history list
        add_history(buf);
        // char * strcpy (char * destination, const char * source);
        strcpy(str, buf);
        return 0;
    } else {
        return 1;
    }
}

// Function to print Current Directory.
void printDir()
{
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("\nDir: %s", cwd);
}
  

// Function where the system command is executed
void execArgs(char** parsed)
{
    // Forking a child
    // fork() return 0 when call by child process
    pid_t pid = fork(); 
  
    if (pid == -1) {
        // failed to fork a child
        printf("\nFailed forking child..");
        return;
    } else if (pid == 0) {
        // pid == 0 -- current process is a child process
        if (execvp(parsed[0], parsed) < 0) {
            printf("\nCould not execute command..");
        }
        exit(0);
    } else {
        // current process is a parent process
        // waiting for child to terminate
        wait(NULL); 
        return;
    }
}

int main() 
{
    init_shell();

    while (1) {
        // print shell line
        printDir();
    }

    return 0;
}
#include <stdio.h> 
#include <unistd.h>
#include <string.h> 
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>


int main()
{ 
    int pipefd[2];
    pipe(pipefd);
    int pid = fork();
    if (pid == 0)
    {
        close(pipefd[1]);
        dup2(pipefd[0],STDIN_FILENO);

        char *args[] = {"/bin/grep","pipex",NULL};
        char *env[] = {NULL};
        execve("/bin/grep", args,env);
        close(pipefd[0]);
    }
    if (pid > 0)
    {
        dup2(pipefd[1],STDOUT_FILENO);
        close(pipefd[0]);
        char *args[] = {"/bin/ls" ,NULL};
        char *env[] = {NULL};

        if (execve("/bin/ls",args,env) == -1)
            perror("execve hatasi");
        close(pipefd[1]);
    }
}


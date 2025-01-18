#include "pipex.h"

int main()
{ 
    int pipefd[2];
    int pid;
    int fd;
    int outfd;
    pipe(pipefd);
    fd = open("infile.txt", O_RDONLY,0644);
    pid = fork();

    if (pid == 0)
    {
        dup2(fd,STDIN_FILENO);
        dup2(pipefd[1],STDOUT_FILENO);
        close(pipefd[1]);
        close(pipefd[0]);
        close(fd);
        char    *argv[] = {"bin/ls",NULL};
        char    *env[] = {NULL};
        execve("/bin/ls",argv,env);
    }
    else
    {
        wait(NULL);
        outfd = open("outfile", O_WRONLY | O_CREAT | O_TRUNC, 0644);
        dup2(outfd,STDOUT_FILENO);
        dup2(pipefd[0],STDIN_FILENO);
        close(outfd);
        close(pipefd[0]);
        close(pipefd[1]);

        char    *argv[] = {"bin/grep","M",NULL};
        char    *env[] = {NULL};
        execve("/bin/grep",argv,env);
    }
}

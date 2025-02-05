/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 02:29:11 by mkulbak           #+#    #+#             */
/*   Updated: 2025/02/05 20:44:59 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_process(char *argv[], char *envp[], int pipefd[])
{
	char	**args;
	char	*path;
	int		fd;

	fd = open(argv[1], O_RDONLY, 0777);
	if (fd == -1)
		error("File opening error", errno, EXIT_FAILURE);
	dup2(fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	args = ft_split(argv[2], ' ');
	path = path_control(args[0], envp);
	if (path == NULL)
	{
		free_all(args);	
		error("Command not found", ENOENT, 127);
	}
	if (execve(path, args, NULL) == -1)
	{
		free_all(args);
		free(path);
		error("Execve Fail", errno, EXIT_FAILURE);
	}
}

static void	parent_process(char *argv[], char *envp[], int pipefd[])
{
	char	**args;
	char	*path;
	int		fd;

	fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
		error("File opening error", errno, EXIT_FAILURE);
	dup2(fd, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[1]);
	args = ft_split(argv[3], ' ');
	path = path_control(args[0], envp);
	if (path == NULL)
	{
		free_all(args);
		error("Command not found", ENOENT, 127);
	}
	if (execve(path, args, NULL) == -1)
	{
		free_all(args);
		free(path);
		error("Execve Fail", errno, EXIT_FAILURE);
	}
}

void wait_child(pid_t pid)
{
    int status;
    int exit_code;

    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
    {
        exit_code = WEXITSTATUS(status);
        if (exit_code != 0)
            exit(exit_code);
    }
}

int	main(int argc, char *argv[], char *envp[])
{
	int		pipefd[2];
	pid_t	pid;

	argc_check(argc, argv);
	if (pipe(pipefd) == -1)
		error("Pipe error", errno, EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		error("Fork error", errno, EXIT_FAILURE);
	if (pid == 0)
		child_process(argv, envp, pipefd);
	waitpid(pid, NULL, 0);
	parent_process(argv, envp, pipefd);
}

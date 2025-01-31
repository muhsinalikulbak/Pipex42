/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 02:29:11 by mkulbak           #+#    #+#             */
/*   Updated: 2025/01/31 17:56:58 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_process(char *argv[], char *envp[], int pipefd[])
{
	char	**args;
	char	*path;
	int		fd;

	fd = open(argv[1], O_RDONLY, 0444);
	if (fd == -1)
		error("File opening error", errno);
	dup2(fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	args = ft_split(argv[2], ' ');
	path = path_control(argv[2], envp);
	if (path == NULL)
	{
		free_all(args);
		error("Command not found", ENOENT);
	}
}

static void	parent_process(char *argv[], char *envp[], int pipefd[])
{
	char	**args;
	char	*path;
	int		fd;

	fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
		error("File opening error", errno);
	dup2(fd, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[1]);
	args = ft_split(argv[3], ' ');
	path = path_control(args[3], envp);
	if (path == NULL)
	{
		free_all(args);
		error("Command not found", ENOENT);
	}
	if (execve(path, args, NULL) == -1)
	{
		free_all(args);
		free(path);
		error("Execve fail", errno);
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	int		pipefd[2];
	pid_t	pid;

	if (pipe(pipefd) == -1)
		error("Pipe error", errno);
	pid = fork();
	if (pid == -1)
		error("Fork error", errno);
	if (pid == 0)
		child_process(argv, envp, pipefd);
	waitpid(pid, NULL, 0);
	parent_process(argv, envp, pipefd);
}

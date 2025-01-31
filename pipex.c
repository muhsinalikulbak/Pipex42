/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 02:29:11 by mkulbak           #+#    #+#             */
/*   Updated: 2025/01/31 11:10:04 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_process(char *argv[], char *envp[], int pipefd[])
{
	int		fd;

	fd = open(argv[1], O_RDONLY, 0777);
	if (fd == -1)
		error("File opening error");
	dup2(fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	close(pipefd[1]);
	close(fd);
	execute(argv[2], envp);
}

static void	parent_process(char *argv[], char *envp[], int pipefd[])
{
	int		fd;

	fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd == -1)
		error("File opening error");
	dup2(fd, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[1]);
	close(pipefd[0]);
	close(fd);
	execute(argv[3], envp);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		pipefd[2];
	pid_t	pid;

	if (argc != 5 || *argv[2] == '\0' || *argv[3] == '\0')
	{
		errno = EINVAL;
		error("Usage: ./pipex file1 cmd1 cmd2 file2\nError");
	}
	if (pipe(pipefd) == -1)
		error("Pipe error");
	pid = fork();
	if (pid == -1)
		error("Fork error");
	if (pid == 0)
		child_process(argv, envp, pipefd);
	waitpid(pid, NULL, 0);
	parent_process(argv, envp, pipefd);
	return (0);
}

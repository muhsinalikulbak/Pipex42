/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 02:29:11 by mkulbak           #+#    #+#             */
/*   Updated: 2025/01/22 15:09:22 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_process(char *argv, char *infile, char *path, int pipefd[])
{
	char	**args;
	int		fd;

	args = ft_split(argv, ' ');
	fd = open(infile, O_RDONLY, 0644);
	if (fd == -1)
	{
		free_all(args);
		error("File could not be opened");
	}
	dup2(fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(fd);
	close(pipefd[0]);
	close(pipefd[1]);
	if (execve(path, args, NULL) == -1)
	{
		free_all(args);
		error("Execve Failed");
	}
}

static void	parent_process(char *argv, char *outfile, char *path, int pipefd[])
{
	char	**args;
	int		fd;

	args = ft_split(argv, ' ');
	fd = open(outfile, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd == -1)
	{
		free_all(args);
		error("File could not be opened");
	}
	dup2(fd, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(fd);
	close(pipefd[0]);
	close(pipefd[1]);
	if (execve(path, args, NULL) == -1)
	{
		free_all(args);
		error("Execve Failed");
	}
}

static int	execute(char *argv[], char **paths, int pipefd[])
{
	int	pid;

	pid = fork();
	if (pid == 0)
		child_process(argv[2], argv[1], paths[0], pipefd);
	else if (pid > 0)
		parent_process(argv[3], argv[4], paths[1], pipefd);
	else
		error("Fork failed");
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		pipefd[2];
	char	**paths;
	int		status;

	if (argc != 5)
	{
		errno = EINVAL;
		error("Incorrect use");
	}
	if (access(argv[1], F_OK | R_OK) == -1)
		error(argv[1]);
	if (pipe(pipefd) == -1)
		error("Pipe error");
	paths = (char **)malloc(sizeof(char *) * 3);
	paths[2] = NULL;
	paths[0] = path_control(argv[2], envp, paths);
	paths[1] = path_control(argv[3], envp, paths);
	status = execute(argv, paths, pipefd);
	return (status);
}

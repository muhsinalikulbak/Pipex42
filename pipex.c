/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 02:29:11 by mkulbak           #+#    #+#             */
/*   Updated: 2025/02/09 19:26:46 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	child_process(char *argv[], char *envp[], int pipefd[])
{
	char	**args;
	char	*path;
	int		fd;

	fd = open_file(argv[1], 2);
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

	fd = open_file(argv[4], 1);
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

void	argc_check(int argc, char *argv[])
{
	int	i;

	i = 2;
	if (argc != 5)
		error("Usage : ./pipex infile cmd1 cmd2 outfile", EINVAL, ENOENT);
	while (i < argc -1)
	{
		if (char_count(argv[i], ' ') == ft_strlen(argv[i]))
			error("Command not found", ENOENT, 127);
		if (char_count(argv[i], '.') > 0)
			error("Command not found", ENOENT, 127);
		if (char_count(argv[i], '/') == ft_strlen(argv[i]))
			error("Command not found", ENOENT, 127);
		i++;
	}
}

int	main(int argc, char *argv[], char *envp[])
{
	int		pipefd[2];
	pid_t	pid;

	argc_check(argc, argv);
	if (pipe(pipefd) == -1)
		error("Pipe error", errno, EXIT_FAILURE);
	if ((pid == fork()) == -1)
		error("Fork error", errno, EXIT_FAILURE);
	if (pid == 0)
		child_process(argv, envp, pipefd);
	wait_child(pid);
	parent_process(argv, envp, pipefd);
}

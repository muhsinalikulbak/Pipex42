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

static void	child_process(char *argv[], char *envp[], int pipefd[])
{
	char	**args;
	char	*cmd;
	char	*path;
	int		fd;

	fd = open(argv[1], O_RDONLY, 0444);
	if (fd == -1)
		error("File opening error");
	args = ft_split(argv[2], ' ');
	cmd = ft_strdup(args[0]);
	if (access(cmd, F_OK) == 0)
		path = ft_strdup(cmd);
	else
		path = path_control(cmd, envp);
	dup2(fd, STDIN_FILENO);
	dup2(pipefd[1], STDOUT_FILENO);
	close(pipefd[0]);
	execve(path, args, NULL);
	close(pipefd[1]);
	close(fd);
	free_all(args);
	free(path);
	free(cmd);
	error("Execve failed");
}

static void	parent_process(char *argv[], char *envp[], int pipefd[])
{
	char	**args;
	char	*cmd;
	char	*path;
	int		fd;

	fd = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0222);
	if (fd == -1)
		error("File opening error");
	args = ft_split(argv[3], ' ');
	cmd = ft_strdup(args[0]);
	if (access(cmd, F_OK) == 0)
		path = ft_strdup(cmd);
	else
		path = path_control(cmd, envp);
	dup2(fd, STDOUT_FILENO);
	dup2(pipefd[0], STDIN_FILENO);
	close(pipefd[1]);
	execve(path, args, NULL);
	close(pipefd[0]);
	close(fd);
	free_all(args);
	free(path);
	free(cmd);
	error("Execve failed");
}

static int	execute(char *argv[], char *envp[])
{
	int		pipefd[2];
	int		status;
	pid_t	pid;

	if (pipe(pipefd) == -1)
		error("Pipe error");
	pid = fork();
	if (pid == -1)
		error("Fork error");
	if (pid == 0)
		child_process(argv, envp, pipefd);
	waitpid(pid, &status, 0);
	parent_process(argv, envp, pipefd);
	return (status);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		status;

	if (argc != 5 || *argv[2] == '\0' || *argv[3] == '\0')
	{
		errno = EINVAL;
		error("Usage: ./pipex file1 cmd1 cmd2 file2\nError");
	}
	status = execute(argv, envp);
	return (status);
}

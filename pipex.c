/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 02:29:11 by mkulbak           #+#    #+#             */
/*   Updated: 2025/01/22 08:32:18 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	child_process(char *argv, char *path, int pipefd[])
{

}

static int	parent_process(char *argv, char *path, int pipefd[])
{

}

static int	exec(char *argv[], char **paths, int pipefd[])
{
	int	pid;

	pid = fork();
	if (pid == 0)
	{
		child_process(argv[2], paths[0], pipefd);
	}
	parent_process(argv[3], paths[1], pipefd);
}

int	main(int argc, char *argv[], char *envp[])
{
	int		pipefd[2];
	char	**paths;
	int		status;

	if (argc != 5)
	{
		errno = 22;
		error("Incorrect use");
	}
	if (access(argv[1], F_OK | R_OK) == -1)
		error(argv[1], 0);
	if (pipe(pipefd) == -1)
		error("Pipe error", 0);
	paths = (char **)malloc(sizeof(char *) * 3);
	paths[2] = NULL;
	paths[0] = path_control(argv[2], envp, paths);
	paths[1] = path_control(argv[3], envp, paths);
	status = exec(argv, paths, pipefd);
	return (status);
}

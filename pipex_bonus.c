/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:32:05 by mkulbak           #+#    #+#             */
/*   Updated: 2025/02/10 16:52:17 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execute(char *argv, char **envp)
{
	char	**args;
	char	*path;

	args = ft_split(argv, ' ');
	path = path_control(args[0], envp);
	if (!path)
	{
		free_all(args);
		error("Command not found", ENOENT, 127);
	}
	if (execve(path, args, envp) == -1)
	{
		free_all(args);
		free(path);
		error("Execve Fail", errno, EXIT_FAILURE);
	}
}

void	child_process(char *argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error("Pipe error", errno, EXIT_FAILURE);
	pid = fork();
	if (pid == -1)
		error("Fork error", errno, EXIT_FAILURE);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(argv, envp);
	}
	else
	{
		wait_child(pid);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	i;
	int	input;
	int	output;

	argc_check_bonus(argc, argv);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		i = 3;
		output = open_file(argv[argc - 1], 0);
		here_doc(argv[2]);
	}
	else
	{
		i = 2;
		output = open_file(argv[argc - 1], 1);
		input = open_file(argv[1], 2);
		dup2(input, STDIN_FILENO);
	}
	while (i < argc - 2)
		child_process(argv[i++], envp);
	dup2(output, STDOUT_FILENO);
	execute(argv[argc - 2], envp);
}

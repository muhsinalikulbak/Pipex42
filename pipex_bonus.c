/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:32:05 by mkulbak           #+#    #+#             */
/*   Updated: 2025/02/04 19:58:58 by mkulbak          ###   ########.fr       */
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
		error("Malloc error", EXIT_FAILURE);
	}
	if (execve(path, args, envp) == -1)
	{
		free_all(args);
		free(path);
		error("Execve Fail", errno);
	}
}

void	child_process(char *argv, char **envp)
{
	pid_t	pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error("Pipe error", errno);
	pid = fork();
	if (pid == -1)
		error("Fork error", errno);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		execute(argv, envp);
	}
	else
	{
		waitpid(pid, NULL, 0);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
}

int	get_next_line(char **line)
{
	char	*buffer;
	int		i;
	int		r;
	char	c;

	i = 0;
	r = 0;
	buffer = (char *)malloc(10000);
	if (!buffer)
		return (-1);
	r = read(0, &c, 1);
	while (r && c != '\n' && c != '\0')
	{
		if (c != '\n' && c != '\0')
			buffer[i] = c;
		i++;
		r = read(0, &c, 1);
	}
	buffer[i] = '\n';
	buffer[++i] = '\0';
	*line = buffer;
	free(buffer);
	return (r);
}

void	here_doc(char *limiter)
{
	pid_t	reader_pid;
	int		fd[2];
	char	*line;

	if (pipe(fd) == -1)
		error("Pipe error", errno);
	reader_pid = fork();
	if (reader_pid == 0)
	{
		close(fd[0]);
		while (get_next_line(&line))
		{
			if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
				exit(EXIT_SUCCESS);
			write(fd[1], line, ft_strlen(line));
		}
	}
	else
	{
		waitpid(reader_pid, NULL, 0);
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
		output = open_file(argv[argc - 1], 0);
		input = open_file(argv[1], 1);
		dup2(input, STDIN_FILENO);
	}
	while (i < argc - 2)
		child_process(argv[i++], envp);
	dup2(output, STDOUT_FILENO);
	execute(argv[argc - 2], envp);
}

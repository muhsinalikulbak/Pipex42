/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:32:09 by mkulbak           #+#    #+#             */
/*   Updated: 2025/02/10 16:57:21 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;
	int	len;

	len = ft_strlen(s);
	i = 0;
	while (i <= len)
	{
		if (s[i] == (char)c)
			return ((char *)s + i);
		i++;
	}
	return (NULL);
}

static void	console_read(char *limiter, int pipefd[])
{
	char	*line;

	line = get_next_line(STDIN_FILENO);
	close(pipefd[0]);
	while (line != NULL)
	{
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		{
			free(line);
			exit(EXIT_SUCCESS);
		}
		write(pipefd[1], line, ft_strlen(line));
		free(line);
		line = get_next_line(STDIN_FILENO);
	}
}

void	here_doc(char *limiter)
{
	pid_t	reader_pid;
	int		fd[2];

	if (pipe(fd) == -1)
		error("Pipe error", errno, EXIT_FAILURE);
	reader_pid = fork();
	if (reader_pid == -1)
		error("Fork error", errno, EXIT_FAILURE);
	if (reader_pid == 0)
		console_read(limiter, fd);
	else
	{
		wait_child(reader_pid);
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
	}
}

void	argc_check_bonus(int argc, char *argv[])
{
	int	i;

	i = 0;
	if (argc < 5)
		error("Usage: ./pipex infile cmd1 cmd2.. outfile\n", EINVAL, ENOENT);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		if (argc < 6)
			error ("Usage : ./pipex_bonus here_doc eof cmd1 cmd2.. outfile",
				EINVAL, ENOENT);
		i = 3;
	}
	else
		i = 2;
	while (i < argc - 1)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 18:31:23 by mkulbak           #+#    #+#             */
/*   Updated: 2025/02/10 16:52:07 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_file(char *file, int i)
{
	int	fd;

	fd = 0;
	if (i == 0)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		fd = open(file, O_RDONLY, 0777);
	if (fd == -1)
		error("File opening error", errno, EXIT_FAILURE);
	return (fd);
}

void	wait_child(pid_t pid)
{
	int	status;
	int	exit_code;

	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
	{
		exit_code = WEXITSTATUS(status);
		if (exit_code != 0)
			exit(exit_code);
	}
}

static char	*cmd_with_path(char *with_path)
{
	char	**directions;
	char	*cmd;
	char	*temp;
	int		i;

	i = 0;
	directions = ft_split(with_path, '/');
	while (directions[i])
		i++;
	temp = ft_strdup(directions[i - 1]);
	cmd = ft_strjoin("/", temp);
	free(temp);
	free_all(directions);
	return (cmd);
}

char	*path_control(char *cmd, char *envp[])
{
	char	**search_path;
	char	*slash_command;
	char	*path;
	int		i;

	if (access(cmd, F_OK) == 0)
		slash_command = cmd_with_path(cmd);
	else
		slash_command = ft_strjoin("/", cmd);
	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	search_path = ft_split(envp[i] + 5, ':');
	i = -1;
	while (search_path[++i])
	{
		path = ft_strjoin(search_path[i], slash_command);
		if (access(path, F_OK) == 0)
			return (free(slash_command), free_all(search_path), path);
		free(path);
	}
	return (free(slash_command), free_all(search_path), NULL);
}

void	error(char *message, int error_code, int exit_code)
{
	if (error_code == EACCES)
		exit_code = 126;
	errno = error_code;
	perror(message);
	exit(exit_code);
}

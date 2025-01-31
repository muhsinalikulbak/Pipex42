/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 05:12:21 by mkulbak           #+#    #+#             */
/*   Updated: 2025/01/31 18:00:29 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*path_control(char *cmd, char *envp[])
{
	char	**search_path;
	char	*slash_command;
	char	*path;
	int		i;

	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	i = 0;
	while (ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	search_path = ft_split(envp[i] + 5, ':');
	slash_command = ft_strjoin("/", cmd);
	i = -1;
	while (search_path[++i])
	{
		path = ft_strjoin(search_path[i], slash_command);
		if (access(path, F_OK | X_OK) == 0)
			return (free(slash_command), free(search_path), path);
		free(path);
	}
	return (free(slash_command), free_all(search_path), NULL);
}

void argc_check(int argc, char *argv[])
{
	int	i;

	if (argc != 5)
		error("Usage : ./pipex infile cmd1 cmd2 outfile", EINVAL);
	
}

void	error(char *message, int exit_code)
{
	errno = exit_code;
	perror(message);
	exit(EXIT_FAILURE);
}

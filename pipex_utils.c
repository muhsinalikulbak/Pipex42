/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 05:12:21 by mkulbak           #+#    #+#             */
/*   Updated: 2025/01/22 15:10:23 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*path_helper(char *ful_path, char *cmd, char **paths)
{
	char	**searched_path;
	char	*slash_cmd;
	char	*path;
	int		i;

	i = 0;
	searched_path = ft_split(ful_path, ':');
	while (searched_path[i])
	{
		slash_cmd = ft_strjoin("/", cmd);
		path = ft_strjoin(searched_path[i], slash_cmd);
		free(slash_cmd);
		if (access(path, F_OK) == 0)
			return (free(searched_path), path);
		free(path);
		i++;
	}
	free_all (paths);
	free_all (searched_path);
	write (2, cmd, ft_strlen(cmd));
	write (2, " : Command not found\n", 21);
	exit (127);
}

char	*path_control(char *argv, char *envp[], char **paths)
{
	char	*cmd;
	char	**args;
	int		i;

	i = 0;
	args = ft_split(argv, ' ');
	if (args == NULL)
		error("malloc");
	cmd = ft_strdup(args[0]);
	free_all(args);
	if (access(cmd, F_OK) == 0)
		return (cmd);
	while (ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	return (path_helper(envp[i], cmd, paths));
}

void	error(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

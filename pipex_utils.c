/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 05:12:21 by mkulbak           #+#    #+#             */
/*   Updated: 2025/01/31 11:38:31 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*path_control(char *cmd, char *envp[])
{
	char	**search_path;
	char	*slash_command;
	char	*path;
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (ft_strncmp(envp[i], "PATH", 4) != 0)
		i++;
	search_path = ft_split(envp[i], ':');
	slash_command = ft_strjoin("/", cmd);
	while (search_path[j])
	{
		path = ft_strjoin(search_path[j], slash_command);
		if (access(path, F_OK | X_OK) == 0)
			return (free(slash_command), free_all(search_path), path);
		free(path);
		j++;
	}
	free_all(search_path);
	return (free(slash_command), NULL);
}

void	execute(char *argv, char *envp[])
{
	char	**args;
	char	*path;

	args = ft_split(argv, ' ');
	if (access(args[0], F_OK | X_OK) == 0)
		path = ft_strdup(args[0]);
	else
		path = path_control(args[0], envp);
	if (path == NULL)
		error("Command not found");
	execve(path, args, NULL);
	free_all(args);
	free(path);
}

void	error(char *message)
{
	perror(message);
	exit(EXIT_FAILURE);
}

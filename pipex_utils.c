/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 05:12:21 by mkulbak           #+#    #+#             */
/*   Updated: 2025/01/31 19:55:14 by mkulbak          ###   ########.fr       */
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
			return (free(slash_command), free_all(search_path), path);
		free(path);
	}
	free_all(search_path);
	return (free(slash_command), NULL);
}

void	argc_check(int argc, char *argv[])
{
	int		i;
	size_t	count;

	if (argc != 5)
		error("Usage : ./pipex infile cmd1 cmd2 outfile", EINVAL);
	i = -1;
	count = 0;
	while(argv[2][++i])
		if (argv[2][i] == ' ')
			count++;
	if (count == ft_strlen(argv[2]))
		error("Command not found", ENOENT);
	i = -1;
	count = 0;
	while(argv[3][++i])
		if (argv[3][i] == ' ')
			count++;
	if (count == ft_strlen(argv[3]))
		error("Command not found", ENOENT);
}

void	error(char *message, int exit_code)
{
	errno = exit_code;
	perror(message);
	exit(EXIT_FAILURE);
}

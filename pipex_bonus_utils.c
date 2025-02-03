
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
static	size_t	char_count(char *str, char ch)
{
	int	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == ch)
			count++;
		i++;
	}
	return (count);
}

void	argc_check(int argc, char *argv[])
{
	if (argc != 5)
		error("Usage : ./pipex infile cmd1 cmd2 outfile", EINVAL);
	if (char_count(argv[2], ' ') == ft_strlen(argv[2]))
		error("Command not found", ENOENT);
	if (char_count(argv[3], ' ') == ft_strlen(argv[3]))
		error("Command not found", ENOENT);
	if (char_count(argv[2], '.') > 0)
		error("Command not found", ENOENT);
	if (char_count(argv[3], '.') > 0)
		error("Command not found", ENOENT);
}

void	error(char *message, int exit_code)
{
	errno = exit_code;
	perror(message);
	exit(EXIT_FAILURE);
}

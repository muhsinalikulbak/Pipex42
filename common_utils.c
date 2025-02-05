
#include "pipex.h"

int	open_file(char *file, int i)
{
	int	fd;

	fd = 0;
	if (i == 0)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if(i == 1)
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		fd = open(file, O_RDONLY, 0777);
	if (fd == -1)
		error("File opening error", errno, EXIT_FAILURE);
	return (fd);
}

void wait_child(pid_t pid)
{
    int status;
    int exit_code;

    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
    {
        exit_code = WEXITSTATUS(status);
        if (exit_code != 0)
            exit(exit_code);
    }
}

char	*path_control(char *cmd, char *envp[])
{
	char	**search_path;
	char	*slash_command;
	char	*path;
	int		i;

	if (access(cmd, F_OK) == 0)
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
		if (access(path, F_OK) == 0)
			return (free(slash_command), free_all(search_path), path);
		free(path);
	}
	free_all(search_path);
	return (free(slash_command), NULL);
}

size_t	char_count(char *str, char ch)
{
	int		i;
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

void	error(char *message, int error_code, int exit_code)
{
	errno = error_code;
	perror(message);
	exit(exit_code);
}

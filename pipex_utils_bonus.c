
#include "pipex.h"
int	open_file(char *argv, int i)
{
	int	file;

	file = 0;
	if (i == 0)
		file = open(argv, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else if (i == 1)
		file = open(argv, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else if (i == 2)
		file = open(argv, O_RDONLY, 0777);
	if (file == -1)
		error("File opening error", errno);
	return (file);
}

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

void	argc_check_bonus(int argc, char *argv[])
{
	int	i;

	i = 0;
	if (argc < 5)
		error("Usage : ./pipex_bonus infile cmd1 cmd2.. outfile\n-OR-\nUsage : ./pipex_bonus here_doc eof cmd1 cmd2.. outfile\n",
		EINVAL);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		if (argc < 6)
			error ("Usage : ./pipex_bonus here_doc eof cmd1 cmd2.. outfile", EINVAL);
		i = 3;
	}
	else
		i = 2;
	while (i < argc - 1)
	{
		if (char_count(argv[i], ' ') == ft_strlen(argv[i]))
			error("Command not found", ENOENT);
		if (char_count(argv[i], '.') > 0)
			error("Command not found", ENOENT);
		i++;
	}
}

void	error(char *message, int exit_code)
{
	errno = exit_code;
	perror(message);
	exit(EXIT_FAILURE);
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

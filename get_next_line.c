/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 17:50:48 by ktoraman          #+#    #+#             */
/*   Updated: 2025/02/10 16:52:10 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*ft_next(char	*buf)
{
	int		i;
	int		j;
	char	*new_buf;

	i = 0;
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	if (!buf[i])
	{
		free(buf);
		return (NULL);
	}
	new_buf = malloc((ft_strlen(buf) - i + 1) * sizeof(char));
	if (!new_buf)
		return (NULL);
	j = 0;
	while (buf[i])
		new_buf[j++] = buf[i++];
	new_buf[j] = '\0';
	free(buf);
	return (new_buf);
}

static char	*ft_line(char *buf)
{
	char	*line;
	int		i;

	i = 0;
	if (!buf)
		return (NULL);
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	line = ft_substr(buf, 0, i);
	return (line);
}

static char	*ft_free(char *buffer, char *buf)
{
	char	*temp;

	temp = ft_strjoin(buffer, buf);
	free(buffer);
	return (temp);
}

static char	*read_file(int fd, char *res)
{
	int		byte_read;
	char	*buf;

	if (!res)
		res = ft_strdup("");
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buf, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(res);
			free(buf);
			return (NULL);
		}
		buf[byte_read] = '\0';
		res = ft_free(res, buf);
		if (ft_strchr(buf, '\n'))
			break ;
	}
	free(buf);
	return (res);
}

char	*get_next_line(int fd)
{
	static char		*buf;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = read_file(fd, buf);
	if (!buf)
	{
		return (NULL);
	}
	line = ft_line(buf);
	buf = ft_next(buf);
	if (!*line)
	{
		if (!*line)
			free(line);
		return (NULL);
	}
	return (line);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 05:01:49 by mkulbak           #+#    #+#             */
/*   Updated: 2025/01/22 14:15:04 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < n && (s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	char	*concat;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	concat = (char *)malloc(sizeof(char) * (len1 + len2) + 1);
	if (!concat)
		return (NULL);
	len1 = 0;
	len2 = 0;
	while (s1[len1])
	{
		concat[len1] = s1[len1];
		len1++;
	}
	while (s2[len2])
	{
		concat[len1 + len2] = s2[len2];
		len2++;
	}
	concat[len1 + len2] = '\0';
	return (concat);
}

char	*ft_strdup(const char	*s1)
{
	int		i;
	int		len;
	char	*heap_str;

	i = 0;
	len = ft_strlen(s1) + 1;
	heap_str = (char *)malloc(sizeof(char) * len);
	if (!heap_str)
		return (NULL);
	while (s1[i])
	{
		*(heap_str + i) = s1[i];
		i++;
	}
	heap_str[i] = '\0';
	return (heap_str);
}

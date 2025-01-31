/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 05:12:26 by mkulbak           #+#    #+#             */
/*   Updated: 2025/01/31 17:58:43 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h> 
# include <unistd.h>
# include <string.h> 
# include <errno.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>

char	**ft_split(char const *s, char c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**free_all(char **result);
char	*ft_strdup(const char	*s1);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*path_control(char *cmd, char *envp[]);
void	error(char *message, int exit_code);
void argc_check(int agrc, char *argv[]);
#endif
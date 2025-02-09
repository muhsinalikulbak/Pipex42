/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:32:09 by mkulbak           #+#    #+#             */
/*   Updated: 2025/02/09 19:24:58 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	argc_check_bonus(int argc, char *argv[])
{
	int	i;

	i = 0;
	if (argc < 5)
		error("Usage: ./pipex infile cmd1 cmd2.. outfile\n", EINVAL, ENOENT);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
	{
		if (argc < 6)
			error ("Usage : ./pipex_bonus here_doc eof cmd1 cmd2.. outfile",
				EINVAL, ENOENT);
		i = 3;
	}
	else
		i = 2;
	while (i < argc - 1)
	{
		if (char_count(argv[i], ' ') == ft_strlen(argv[i]))
			error("Command not found", ENOENT, 127);
		if (char_count(argv[i], '.') > 0)
			error("Command not found", ENOENT, 127);
		if (char_count(argv[i], '/') == ft_strlen(argv[i]))
			error("Command not found", ENOENT, 127);
		i++;
	}
}

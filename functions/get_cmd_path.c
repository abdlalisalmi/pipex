/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 10:12:04 by aes-salm          #+#    #+#             */
/*   Updated: 2021/06/24 16:54:14 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*get_cmd_path(char *cmd)
{
	char	**paths;
	char	*full_path;
	char	*command;
	int		i;
	int		fd;

	paths = ft_split(g_args.path, ':');
	i = -1;
	while (paths[++i])
	{
		command = ft_strappend("/", cmd);
		full_path = ft_strappend(paths[i], command);
		fd = open(full_path, O_RDONLY);
		if (fd > -1)
		{
			close(fd);
			free(command);
			free_d_pointer(paths);
			return (full_path);
		}
		free(command);
		free(full_path);
	}
	free_d_pointer(paths);
	return (NULL);
}

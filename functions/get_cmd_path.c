/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 10:12:04 by aes-salm          #+#    #+#             */
/*   Updated: 2021/06/29 15:49:33 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*get_cmd_path(char *cmd)
{
	char	*full_path;
	char	*command;
	int		i;
	int		fd;

	if (ft_strchr(cmd, '/'))
		return (cmd);
	i = -1;
	while (g_args.paths[++i])
	{
		command = ft_strappend("/", cmd);
		full_path = ft_strappend(g_args.paths[i], command);
		fd = open(full_path, O_RDONLY);
		if (fd > -1)
		{
			close(fd);
			free(command);
			return (full_path);
		}
		free(command);
		free(full_path);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 19:49:13 by aes-salm          #+#    #+#             */
/*   Updated: 2021/06/23 13:23:03 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <errno.h>

# define PERMISSION S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

typedef struct s_args
{
	char		*inFile;
	char		*outFile;
	char		**cmd1;
	char		**cmd2;
	char		*path;
}				t_args;
t_args			g_args;

int		ft_strlen(char *s);
char	**ft_split(const char *ss, char c);
int		ft_strncmp(const char *str1, const char *str2, int n);
char	*ft_substr(char const *s, int start, int len);
char	*ft_strappend(char *s1, char *s2);

char	*get_cmd_path(char *cmd);

#endif
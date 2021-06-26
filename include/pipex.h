/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 19:49:13 by aes-salm          #+#    #+#             */
/*   Updated: 2021/06/26 09:36:36 by aes-salm         ###   ########.fr       */
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

typedef struct s_args
{
	char		*inFile;
	char		*outFile;
	char		**cmd1;
	char		**cmd2;
	char		**paths;
	int			in_fd;
	int			out_fd;
	int			fd[2];
	int			status;
}				t_args;
t_args			g_args;

int		ft_strlen(char *s);
char	**ft_split(const char *ss, char c);
int		ft_strncmp(const char *str1, const char *str2, int n);
char	*ft_substr(char const *s, int start, int len);
char	*ft_strappend(char *s1, char *s2);
char	*ft_strchr(const char *str, int c);

char	*get_cmd_path(char *cmd);
void	free_d_pointer(char **ptr);
void	exit_programme(char *msg, int code);
void	excute(char **envp);

#endif
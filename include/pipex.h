/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 19:49:13 by aes-salm          #+#    #+#             */
/*   Updated: 2021/06/22 21:39:28 by aes-salm         ###   ########.fr       */
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
}				t_args;
t_args			g_args;

int		ft_strlen(char *s);
char	**ft_split(const char *ss, char c);

#endif
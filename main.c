/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 19:48:11 by aes-salm          #+#    #+#             */
/*   Updated: 2021/06/26 09:38:47 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

void	exit_programme(char *msg, int code)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	exit(code);
}

void	free_leaks(void)
{
	free(g_args.inFile);
	free(g_args.outFile);
	free(g_args.paths);
	free_d_pointer(g_args.cmd1);
	free_d_pointer(g_args.cmd2);
}

void	fill_args_struct(char **args, char **envp)
{
	int	i;

	g_args.inFile = strdup(args[1]);
	g_args.outFile = strdup(args[4]);
	g_args.cmd1 = ft_split(args[2], ' ');
	g_args.cmd2 = ft_split(args[3], ' ');
	i = -1;
	while (envp[++i])
		if (!ft_strncmp(envp[i], "PATH=", 5))
			g_args.paths = ft_split(ft_substr(envp[i], 5,
						ft_strlen(envp[i])), ':');
}

int	main (int len, char **args, char **envp)
{
	if (len < 5)
		exit_programme("few arguments!", EXIT_FAILURE);
	else if (len > 5)
		exit_programme("too many arguments!", EXIT_FAILURE);
	fill_args_struct(args, envp);
	excute(envp);
	free_leaks();
	return (WEXITSTATUS(g_args.status));
}

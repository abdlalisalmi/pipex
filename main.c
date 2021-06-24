/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 19:48:11 by aes-salm          #+#    #+#             */
/*   Updated: 2021/06/24 16:05:58 by aes-salm         ###   ########.fr       */
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
	free(g_args.path);
	free_d_pointer(g_args.cmd1);
	free_d_pointer(g_args.cmd2);
}

void	fill_args_struct(char **args, char **envp)
{
	int i;

	g_args.inFile = strdup(args[1]);
	g_args.outFile = strdup(args[4]);
	g_args.cmd1 = ft_split(args[2], ' ');
	g_args.cmd2 = ft_split(args[3], ' ');
	i = -1;
	while (envp[++i])
		if (!ft_strncmp(envp[i], "PATH=", 5))
			g_args.path = ft_substr(envp[i], 5, ft_strlen(envp[i]));
}

void setupp_redirections()
{
	g_args.in_fd = open(g_args.inFile, O_RDONLY);
	if (g_args.in_fd == -1)
	{
		write(2, "pipex: ", 7);
		write(2, g_args.inFile, ft_strlen(g_args.inFile));
		write(2, ": No such file or directory\n", 28);
	}
	else
		dup2(g_args.in_fd, STDIN_FILENO);
	g_args.out_fd = open(g_args.outFile, O_WRONLY | O_CREAT | O_TRUNC, PERMISSION);
	dup2(g_args.out_fd, STDOUT_FILENO);
}

int	main (int len, char **args, char **envp)
{
	if (len < 5)
		exit_programme("few arguments!", EXIT_FAILURE);
	else if (len > 5)
		exit_programme("too many arguments!", EXIT_FAILURE);
	fill_args_struct(args, envp);
	setupp_redirections();
	excute(envp);
	free_leaks();
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 19:48:11 by aes-salm          #+#    #+#             */
/*   Updated: 2021/06/23 13:34:49 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

void	exit_programme(char *msg, int code)
{
	write(2, msg, ft_strlen(msg));
	exit(code);
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

	//printf("infile: %s\n", g_args.inFile);
	//printf("outfile: %s\n", g_args.outFile);

	//printf("PATH: %s\n", g_args.path);

	//printf("CMD1: ");
	//i = -1;
	//while (g_args.cmd1[++i])
	//{
	//	printf("%s ", g_args.cmd1[i]);
	//}

	//printf("\nCMD2: ");
	//i = -1;
	//while (g_args.cmd2[++i])
	//{
	//	printf("%s ", g_args.cmd2[i]);
	//}
}

void setupp_redirections()
{
	int	in_fd;
	int	out_fd;

	in_fd = open(g_args.inFile, O_RDONLY);
	if (in_fd == -1)
	{
		write(2, "pipex: ", 7);
		write(2, g_args.inFile, ft_strlen(g_args.inFile));
		write(2, ": No such file or directory\n", 28);
	}
	else
		dup2(in_fd, 0);
	out_fd = open(g_args.outFile, O_WRONLY | O_CREAT | O_TRUNC, PERMISSION);
	dup2(out_fd, 1);
}

void excute_commands(char **envp)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid < 0)
		exit_programme("Failed forking child..\n", EXIT_FAILURE);
	else if (pid == 0)
	{
		if (execve(get_cmd_path(g_args.cmd1[0]), g_args.cmd1, envp) == -1)
		{
			exit_programme(strerror(errno), EXIT_FAILURE);
			write(2, "\n", 1);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (execve(get_cmd_path(g_args.cmd2[0]), g_args.cmd2, envp) == -1)
		{
			exit_programme(strerror(errno), EXIT_FAILURE);
			write(2, "\n", 1);
		}
	}
}

int	main (int len, char **args, char **envp)
{
	if (len < 5)
		exit_programme("few arguments!\n", EXIT_FAILURE);
	else if (len > 5)
		exit_programme("too many arguments!\n", EXIT_FAILURE);
	fill_args_struct(args, envp);
	setupp_redirections();
	excute_commands(envp);

	return (0);
}

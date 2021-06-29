/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 15:33:48 by aes-salm          #+#    #+#             */
/*   Updated: 2021/06/29 13:01:54 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	execute_cmd_2(char **envp)
{
	g_args.out_fd = open(g_args.outFile, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR
			| S_IWUSR | S_IRGRP | S_IROTH);
	if (g_args.out_fd == -1)
	{
		write(2, "pipex: ", 7);
		write(2, g_args.outFile, ft_strlen(g_args.outFile));
		write(2, ": ", 2);
		exit_programme(strerror(errno), 1);
	}
	close(g_args.fd[1]);
	dup2(g_args.out_fd, STDOUT_FILENO);
	dup2(g_args.fd[0], STDIN_FILENO);
	close(g_args.fd[0]);
	if (execve(get_cmd_path(g_args.cmd2[0]), g_args.cmd2, envp) == -1)
	{
		write(2, "pipex: ", 7);
		write(2, g_args.cmd2[0], ft_strlen(g_args.cmd2[0]));
		exit_programme(": command not found", 127);
	}
	exit(EXIT_SUCCESS);
}

void	execute_cmd_1(char **envp)
{
	g_args.in_fd = open(g_args.inFile, O_RDONLY);
	if (g_args.in_fd == -1)
	{
		write(2, "pipex: ", 7);
		write(2, g_args.inFile, ft_strlen(g_args.inFile));
		exit_programme(": No such file or directory", EXIT_FAILURE);
	}
	else
	{
		close(g_args.fd[0]);
		dup2(g_args.in_fd, STDIN_FILENO);
		dup2(g_args.fd[1], STDOUT_FILENO);
		close(g_args.fd[1]);
		if (execve(get_cmd_path(g_args.cmd1[0]), g_args.cmd1, envp) == -1)
		{
			write(2, "pipex: ", 7);
			write(2, g_args.cmd1[0], ft_strlen(g_args.cmd1[0]));
			exit_programme(": command not found", 127);
		}
	}
}

void	excute(char **envp)
{
	pid_t	pid_1;
	pid_t	pid_2;

	if (pipe(g_args.fd) == -1)
		exit_programme("Failed opening the pipe..", EXIT_FAILURE);
	pid_1 = fork();
	if (pid_1 < 0)
		exit_programme("Failed forking child..", EXIT_FAILURE);
	else if (pid_1 == 0)
		execute_cmd_1(envp);
	pid_2 = fork();
	if (pid_2 < 0)
		exit_programme("Failed forking child..", EXIT_FAILURE);
	else if (pid_2 == 0)
		execute_cmd_2(envp);
	else
	{
		close(g_args.fd[0]);
		close(g_args.fd[1]);
		waitpid(pid_1, &g_args.status, 0);
		waitpid(pid_2, &g_args.status, 0);
	}
}

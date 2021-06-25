/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 15:33:48 by aes-salm          #+#    #+#             */
/*   Updated: 2021/06/25 13:24:11 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	execute_in_parrent(pid_t *pid_2, char **envp)
{
	// pid_t	pid_2;

	*pid_2 = fork();
	if (*pid_2 < 0)
		exit_programme("Failed forking child..", EXIT_FAILURE);
	else if (*pid_2 == 0)
	{
		close(g_args.fd[1]);
		dup2(g_args.fd[0], STDIN_FILENO);
		close(g_args.fd[0]);
		if (execve(get_cmd_path(g_args.cmd2[0]), g_args.cmd2, envp) == -1)
		{
			write(2, "pipex: ", 7);
			write(2, g_args.cmd2[0], ft_strlen(g_args.cmd2[0]));
			write(2, ": command not found\n", 20);
			// exit_programme(": command not found", 127);
		}
		close(g_args.out_fd);
		exit(0);
	}
	// else
	// {
	// 	waitpid(*pid_2, &g_args.status, 0);
	// 	exit(WIFEXITED(g_args.status));
	// }
}

void	execute_in_child(char **envp)
{
	close(g_args.fd[0]);
	dup2(g_args.fd[1], STDOUT_FILENO);
	close(g_args.fd[1]);
	if (execve(get_cmd_path(g_args.cmd1[0]), g_args.cmd1, envp) == -1)
	{
		write(2, "pipex: ", 7);
		write(2, g_args.cmd1[0], ft_strlen(g_args.cmd1[0]));
		exit_programme(": command not found", 127);
	}
	close(g_args.in_fd);
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
	{
		if (g_args.in_fd != -1)
			execute_in_child(envp);
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid_1, &g_args.status, 0);
		execute_in_parrent(&pid_2, envp);
		waitpid(pid_2, &g_args.status, 0);
		// dprintf(2, "%d\n", WIFEXITED(g_args.status));
	}
}

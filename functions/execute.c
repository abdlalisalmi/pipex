/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 15:33:48 by aes-salm          #+#    #+#             */
/*   Updated: 2021/06/24 17:08:51 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	execute_in_parrent(char **envp)
{
	pid_t	pid_2;

	pid_2 = fork();
	if (pid_2 < 0)
		exit_programme("Failed forking child..", EXIT_FAILURE);
	else if (pid_2 == 0)
	{
		close(g_args.fd[1]);
		dup2(g_args.fd[0], STDIN_FILENO);
		close(g_args.fd[0]);
		if (execve(get_cmd_path(g_args.cmd2[0]), g_args.cmd2, envp) == -1)
			exit_programme(strerror(errno), EXIT_FAILURE);
	}
	close(g_args.out_fd);
}

void	execute_in_child(char **envp)
{
	close(g_args.fd[0]);
	dup2(g_args.fd[1], STDOUT_FILENO);
	close(g_args.fd[1]);
	if (execve(get_cmd_path(g_args.cmd1[0]), g_args.cmd1, envp) == -1)
		exit_programme(strerror(errno), EXIT_FAILURE);
	close(g_args.in_fd);
}

void	excute(char **envp)
{
	pid_t	pid_1;
	int		status;

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
		waitpid(pid_1, &status, 0);
		execute_in_parrent(envp);
	}
}

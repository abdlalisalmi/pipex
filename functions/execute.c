/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/24 15:33:48 by aes-salm          #+#    #+#             */
/*   Updated: 2021/06/24 15:41:30 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void    excute(char **envp)
{
	int		fd[2];
	pid_t	pid_1;
	pid_t	pid_2;
	int		status;

	if (pipe(fd) == -1)
		exit_programme("Failed opening the pipe..", EXIT_FAILURE);
	pid_1 = fork();
	if (pid_1 < 0)
		exit_programme("Failed forking child..", EXIT_FAILURE);
	else if (pid_1 == 0)
	{
		if(g_args.in_fd != -1)
		{
			close(fd[0]);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			if (execve(get_cmd_path(g_args.cmd1[0]), g_args.cmd1, envp) == -1)
				exit_programme(strerror(errno), EXIT_FAILURE);
			close(g_args.in_fd);
		}
		exit(EXIT_FAILURE);
	}
	else
	{
		waitpid(pid_1, &status, 0);
		pid_2 = fork();
		if (pid_2 < 0)
			exit_programme("Failed forking child..", EXIT_FAILURE);
		else if (pid_2 == 0)
		{
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			if (execve(get_cmd_path(g_args.cmd2[0]), g_args.cmd2, envp) == -1)
				exit_programme(strerror(errno), EXIT_FAILURE);
		}
		close(g_args.out_fd);
	}
}

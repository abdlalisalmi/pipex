/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 19:48:11 by aes-salm          #+#    #+#             */
/*   Updated: 2021/06/22 21:44:35 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/pipex.h"

void	exit_programme(char *msg, int code)
{
	write(1, msg, ft_strlen(msg));
	exit(code);
}

void	fill_args_struct(char **args)
{

	g_args.inFile = strdup(args[1]);
	g_args.outFile = strdup(args[4]);

	printf("%s\n", g_args.inFile);
	printf("%s\n", g_args.outFile);
}

int	main (int len, char **args)
{
	if (len < 5)
		exit_programme("few arguments!\n", EXIT_FAILURE);
	else if (len > 5)
		exit_programme("too many arguments!\n", EXIT_FAILURE);
	fill_args_struct(args);
	return (0);
}

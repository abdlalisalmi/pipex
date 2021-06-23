/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 10:15:49 by aes-salm          #+#    #+#             */
/*   Updated: 2021/06/23 10:21:58 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	ft_strncmp(const char *str1, const char *str2, int n)
{
	unsigned char	*pstr1;
	unsigned char	*pstr2;
	int				i;

	i = 0;
	if (n == 0)
		return (0);
	pstr1 = (unsigned char *)str1;
	pstr2 = (unsigned char *)str2;
	while ((pstr1[i] != '\0' || pstr2[i] != '\0') && i < n)
	{
		if (pstr1[i] != pstr2[i])
			return (pstr1[i] - pstr2[i]);
		i++;
	}
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/26 11:03:01 by aes-salm          #+#    #+#             */
/*   Updated: 2021/06/29 13:04:45 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*ft_strchr(const char *str, int c)
{
	char	*pstr;
	int		i;

	if (!str)
		return (NULL);
	pstr = (char *)str;
	i = 0;
	while (i <= ft_strlen(pstr))
	{
		if (str[i] == c)
			return ((char *)(str + i));
		i++;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aes-salm <aes-salm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/23 10:19:13 by aes-salm          #+#    #+#             */
/*   Updated: 2021/06/24 17:07:17 by aes-salm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

char	*ft_substr(char const *s, int start, int len)
{
	char	*sub;
	int		i;

	if (!s)
		return (NULL);
	sub = malloc(len + 1);
	i = 0;
	while (s[i] != '\0' && i < len && start < ft_strlen((char *)s))
	{
		sub[i] = s[start];
		start++;
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_tools2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamali <mamali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 19:05:20 by mamali            #+#    #+#             */
/*   Updated: 2021/07/18 19:06:18 by mamali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == (char)c)
		return ((char *)s);
	return (NULL);
}

char	*ft_strdup(const char *s1)
{
	int		i;
	int		len;
	char	*s;

	i = 0;
	len = 0;
	while (s1[len])
		len++;
	s = malloc((len + 1) * sizeof(char));
	if (s == 0)
		return (NULL);
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

void	*ft_calloc(size_t count, size_t size)
{
	char	*p;
	long	i;

	i = count * size;
	p = malloc(i);
	if (!p)
		return (0);
	while (i--)
		p[i] = 0;
	return (p);
}

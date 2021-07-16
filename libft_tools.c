/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamali <mamali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 13:32:45 by mamali            #+#    #+#             */
/*   Updated: 2021/07/16 13:39:32 by mamali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

size_t  ft_strlen(const char  *str)
{
    int i = 0;
    while (str[i])
        i++;
    return (i);
}

static	size_t	ft_countw(char *s, char c)
{
	size_t	i;
	size_t	mm;
	size_t	cpt;

	mm = 1;
	cpt = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			mm = 1;
		else if (mm == 1)
		{
			mm = 0;
			cpt++;
		}
		i++;
	}
	return (cpt);
}

static	size_t	ft_wlen(char *s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (s[i] != c && s[i])
	{
		i++;
		len++;
	}
	return (len);
}

static	char	**ft_free(char **f, size_t j)
{
	size_t	i;

	i = 0;
	while (i < j)
		free(f[i++]);
	free(f);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	size_t		i;
	size_t		countw;
	size_t		l_count;
	size_t		j;
	char		**p;

	i = -1;
	j = 0;
	l_count = 0;
	countw = ft_countw((char *)s, c);
	p = (char **) malloc(sizeof(char *) * (countw + 1));
	if (!p)
		return (NULL);
	while (++i < countw)
	{
		while (s[j] == c)
			j++;
		l_count = ft_wlen((char *)s + j, c);
		p[i] = ft_substr(s, j, l_count);
		if (!p)
			return (ft_free(p, i));
		j += l_count + 1;
	}
	p[countw] = NULL;
	return (p);
}
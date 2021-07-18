/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_tools2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aez-zaou <aez-zaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 13:34:39 by mamali            #+#    #+#             */
/*   Updated: 2021/07/18 20:01:04 by aez-zaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*p;
	unsigned char	*o;

	o = (unsigned char *)s1;
	p = (unsigned char *)s2;
	while ((*o || *p))
	{
		if (*o != *p)
			return (*o - *p);
		else
		{
			o++;
			p++;
		}
	}
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*p;
	unsigned char	*o;

	i = 0;
	o = (unsigned char *)s1;
	p = (unsigned char *)s2;
	while ((*o || *p) && i++ < n)
	{
		if (*o != *p)
			return (*o - *p);
		else
		{
			o++;
			p++;
		}
	}
	return (0);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*p;
	int		i;
	int		j;

	i = ft_strlen((char *)s1);
	j = ft_strlen((char *)s2);
	p = malloc(i + j + 2);
	if (!(p))
		return (0);
	strcpy(p, (char *)s1);
	strcpy(&p[i], "/");
	strcpy(&p[i + 1], (char *)s2);
	return (p);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*p;
	int				i;
	unsigned int	bigg;

	i = 0;
	bigg = start;
	if (!s || start > ft_strlen(s))
	{
		p = malloc(1 * sizeof(char));
		p[0] = '\0';
		return (p);
	}
	p = malloc((len + 1) * sizeof(char));
	if (p == 0)
		return (NULL);
	while (start < (unsigned int)len + bigg && s[start])
	{
		p[i] = s[start];
		start++;
		i++;
	}
	p[i] = '\0';
	return (p);
}

int	ret(char **str)
{
	free(*str);
	return (1);
}

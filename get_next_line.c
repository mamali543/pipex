/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamali <mamali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 17:35:16 by mamali            #+#    #+#             */
/*   Updated: 2021/07/18 18:55:44 by mamali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "pipex.h"

static char	*ft_strcpy(char *dest, char *src)
{
	int		i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	*help(char *save, char **line)
{
	char	*str;

	str = NULL;
	if (save)
	{
		str = ft_strchr(save, '\n');
		if (str)
		{
			*str = '\0';
			*line = ft_strdup(save);
			++str;
			ft_strcpy(save, str);
		}
		else
		{
			*line = ft_strdup(save);
			save = NULL;
		}
	}
	else
		*line = ft_calloc(1, 1);
	return (str);
}

void	help3(char *buff, char **line)
{
	char	*tmp;

	tmp = *line;
	*line = ft_strjoin(tmp, buff);
	free(tmp);
}

int	help2(char **save, char *buff, int fd, char **line)
{
	int			size_read;
	char		*str;

	str = help(*save, line);
	while (!str)
	{
		size_read = read(fd, buff, BUFFER_SIZE);
		if (!size_read)
		{
			free(buff);
			free(*save);
			save = NULL;
			return (0);
		}
		*(buff + size_read) = '\0';
		str = ft_strchr(buff, '\n');
		if (str)
		{
			*str++ = '\0';
			free(*save);
			*save = ft_strdup(str);
		}
		help3(buff, line);
	}
	return (ret(&buff));
}

int	get_next_line(int fd, char **line)
{
	static char	*save;
	char		*buff;

	buff = malloc(BUFFER_SIZE + 1);
	return (help2(&save, buff, fd, line));
}

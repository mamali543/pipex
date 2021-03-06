/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamali <mamali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 17:33:49 by mamali            #+#    #+#             */
/*   Updated: 2021/07/19 16:21:47 by mamali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	execdup(int	i, int *fds, int x, int fd)
{
	if (x != 0)
	{
		dup2(fd, 0);
		close(fd);
	}
	if (i - 1 != x)
		dup2(fds[1], 1);
	close(fds[0]);
}


int	execmlpipe(char **argv1, int i, char **env)
{
	int		fds[2];
	pid_t	pid;
	int		x;
	int		fd;

	x = -1;
	while (++x < i)
	{
		pipe(fds);
		pid = fork();
		if (pid == -1)
			log_error("error : fork failed", 1);
		if (pid == 0)
		{
			execdup(i, fds, x, fd);
			executecmd(argv1[x], env);
		}
		else
		{
			wait(NULL);
			close(fds[1]);
			fd = fds[0];
		}
	}
	return (0);
}

int	ft_getfd1(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd == -1)
		return (0);
	dup2(fd, 0);
	close(fd);
	return (1);
}

int	ft_getfd2(char *str)
{
	int	fd;

	fd = open(str, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (fd == -1)
		return (9);
	dup2(fd, 1);
	close(fd);
	return (1);
}

int	ft_getfd3(char *str)
{
	int	fd;

	fd = open(str, O_RDWR | O_CREAT | O_APPEND, 0666);
	if (fd == -1)
		return (0);
	dup2(fd, 1);
	close(fd);
	return (1);
}

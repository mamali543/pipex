/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executionb.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamali <mamali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 17:33:49 by mamali            #+#    #+#             */
/*   Updated: 2021/07/18 18:59:51 by mamali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    execdup(int i, int *fd, int j, int tfd)
{
    if (j != 0)
    {
        dup2(tfd, 0);
        close(tfd);
    }
    if (i - 1 != j)
        dup2(fd[1], 1);
    close (fd[0]);
}

int     mltpipeexec(char    **argv, int     i, char     **env)
{
    int     fd[2];
    pid_t   pid1;
    int     j;
    int     tfd;

    j = -1;
    while (++j < i)
    {
		if (pipe(fd) == -1)
			log_error("Error: An error occured with opening the pipe", 1);
        pid1 = fork();
        if (pid1 == -1)
            log_error("Error: An error occured with the fork", 1);
        if (pid1 == 0)
        {
            execdup(i, fd, j, tfd);
            executecmd(argv[j], env);
        }
        else
        {
			wait(NULL);
			close(fd[1]);
			tfd = fd[0];
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

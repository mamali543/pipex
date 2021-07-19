/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamali <mamali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 13:30:01 by mamali            #+#    #+#             */
/*   Updated: 2021/07/19 16:21:44 by mamali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


char	*ft_getabsolutepath(char **path, char **tmp)
{
	int		i;
	char	*cmd;
	int		fd;

	i = -1;
	cmd = NULL;
	while (path[++i])
	{
		cmd = ft_strjoin(path[i], tmp[0]);
		fd = open(cmd, O_RDONLY);
		if (fd > 0)
			break ;
		close(fd);
		free(cmd);
	}
	close(fd);
	return (cmd);
}

char	*ft_getpath(char **env, char *cmd)
{
	char	**tmp;
	char	**path;
	int		i;

	tmp = ft_split(cmd, ' ');
	i = -1;
	while (env[++i])
		if (!(ft_strncmp(env[i], "PATH", 4)))
			cmd = *(env + i) + 5;
	path = ft_split(cmd, ':');
	cmd = ft_getabsolutepath(path, tmp);
	free_dpointer(path);
	free_dpointer(tmp);
	return (cmd);
}

void	executecmd(char *cmd, char **env)
{
	char	**p;
	char	*ncmd;

	p = ft_split(cmd, ' ');
	ncmd = ft_getpath(env, cmd);
	execve(ncmd, p, env);
	if (p)
		free_dpointer(p);
	log_error("Error : command not found", 127);
}

void	piipe(int *fd, char *s, char **env, int i)
{
	if (i == 1)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		executecmd(s, env);
	}
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		close(fd[0]);
		executecmd(s, env);
	}
}

int	pipe_execution(char **argv, char **env, int i)
{
	pid_t	pid1;
	pid_t	pid2;
	int		fd[2];

	pid1 = fork();
	if (pid1 == -1)
		log_error("Error: An error occured with the fork", 1);
	if (pid1 == 0)
	{
		if (pipe(fd) == -1)
			log_error("Error: An error occured with opening the pipe", 1);
		pid2 = fork();
		if (pid2 == -1)
			log_error("Error: An error occured with the fork", 1);
		if (pid2 == 0)
			piipe(fd, argv[0], env, 1);
		else
			piipe(fd, argv[1], env, 0);
	}
	else
		waitpid(pid1, &i, 0);
	if (i == 0)
		return (0);
	return (127);
}

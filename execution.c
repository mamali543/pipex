/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamali <mamali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 13:30:01 by mamali            #+#    #+#             */
/*   Updated: 2021/07/16 13:45:37 by mamali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_dpointer(char **tokens)
{
	int		i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
}

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
		if (!(strncmp(env[i], "PATH", 4)))
			cmd = *(env + i) + 5;
	path = ft_split(cmd, ':');
	if (!tmp[0])
		return (NULL);
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

int	pipe_execution(char **argv, char **env)
{
	pid_t	pid1;
	pid_t	pid2;
	int		fd[2];
	int		i;

	i = 0;
	pid1 = fork();
	if (pid1 == -1)
		log_error("Error: An error occured with the fork", 1);
	if (pid1 == 0)
	{
		if (pipe(fd) == -1)
			log_error("Error: An error occured with opening the pipe", 4);
		pid2 = fork();
		if (pid2 == -1)
			log_error("Error: An error occured with the fork", 1);
		if (pid2 == 0)
		{
			close(fd[0]);
			dup2(fd[1], 1);
			close(fd[1]);
			executecmd(argv[0], env);
		}
		else
		{
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);
			executecmd(argv[1], env);
		}
	}
	else
		waitpid(pid1, &i, 0);
	if (i == 0)
		return 0;
	return (127);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamali <mamali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 19:03:35 by mamali            #+#    #+#             */
/*   Updated: 2021/07/18 19:04:43 by mamali           ###   ########.fr       */
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

void	log_error(char *str, int i)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(i);
}

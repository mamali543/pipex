/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mamali <mamali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/16 13:31:45 by mamali            #+#    #+#             */
/*   Updated: 2021/07/19 16:19:04 by mamali           ###   ########.fr       */
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

void	log_error(char *str, int i)
{
	write(2, str, ft_strlen(str));
	write(2, "\n", 1);
	exit(i);
}

void	set_output(char *p)
{
	int	fd;

	fd = open(p, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		log_error("Error: No such file or directory", 1);
	dup2(fd, 1);
	close(fd);
}

void	set_input(char *s)
{
	int	fd;

	fd = open(s, O_RDONLY);
	if (fd == -1)
		log_error("Error: No such file or directory", 0);
	dup2(fd, 0);
	close(fd);
}

int	main(int argc, char **argv, char **env)
{
	if (argc != 5)
		log_error("Error: Invalid Args", 1);
	if (!argv[2][0] || !argv[3][0])
		log_error("Error: Invalid Args", 1);
	set_input(argv[1]);
	set_output(argv[4]);
	return (pipe_execution(&argv[2], env, 0));
}

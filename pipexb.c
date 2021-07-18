/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexb.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aez-zaou <aez-zaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/18 17:33:11 by mamali            #+#    #+#             */
/*   Updated: 2021/07/18 20:04:07 by aez-zaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_getfd4(char *str)
{
	int		fd[2];
	char	*line;
	int		x;

	x = 1;
	if (pipe(fd) == -1)
		log_error("Error: An error occured with opening the pipe", 1);
	while (x)
	{
		get_next_line(0, &line);
		x = ft_strcmp(line, str);
		if (!x)
			break ;
		else
			write(fd[1], line, strlen(line));
		free(line);
		write(fd[1], "\n", 1);
	}
	if (line)
		free(line);
	dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);
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

void	ft_pars(char **argv, int y, int x, int z)
{
	if (z == 0 && ft_getfd1(argv[y]) == 0)
		log_error("error : no such file or directory", 0);
	if (z == 0 && ft_getfd2(argv[x]) == 0 && z == 0)
		log_error("error : no such file or directory", 0);
	if (z == 1)
	{
		if (ft_getfd3(argv[x]) == 0)
			log_error("error : no such file or directory", 0);
		ft_getfd4(argv[y]);
	}
}

int	main(int argc, char **argv, char **env)
{
	if (argc < 5)
		log_error("error : Invalid arguments", 1);
	if (!argv[2][0] || !argv[3][0])
		log_error("error : Invalid arguments", 1);
	if (!ft_strcmp(argv[1], "here_doc"))
	{
		ft_pars(argv, 2, argc - 1, 1);
		return (mltpipeexec(&argv[3], argc - 4, env, -1));
	}
	else if (argc >= 5)
	{
		ft_pars(argv, 1, argc - 1, 0);
		return (mltpipeexec(&argv[2], argc - 3, env, -1));
	}
	return (0);
}

# include <stdio.h>$
# include <unistd.h>$
# include <stdlib.h>$
# include <string.h>$
# include <math.h>$
# include <fcntl.h>$
# include <dirent.h>$
# include <stdio.h>$
# include <libgen.h>$
# include <signal.h>$
# include <sys/types.h>$
# include <sys/wait.h>$
$
size_t  ft_strlen(const char  *str)$
{$
    int i = 0;$
    while (str[i])$
        i++;$
    return (i);$
}$
$
$
char	*ft_substr(char const *s, unsigned int start, size_t len)$
{$
	char			*p;$
	int				i;$
	unsigned int	bigg;$
$
	i = 0;$
	bigg = start;$
	if (!s || start > ft_strlen(s))$
	{$
		p = malloc(1 * sizeof(char));$
		p[0] = '\0';$
		return (p);$
	}$
	p = malloc((len + 1) * sizeof(char));$
	if (p == 0)$
		return (NULL);$
	while (start < (unsigned int)len + bigg && s[start])$
	{$
		p[i] = s[start];$
		start++;$
		i++;$
	}$
	p[i] = '\0';$
	return (p);$
}$
$
static	size_t	ft_countw(char *s, char c)$
{$
	size_t	i;$
	size_t	mm;$
	size_t	cpt;$
$
	mm = 1;$
	cpt = 0;$
	i = 0;$
	while (s[i])$
	{$
		if (s[i] == c)$
			mm = 1;$
		else if (mm == 1)$
		{$
			mm = 0;$
			cpt++;$
		}$
		i++;$
	}$
	return (cpt);$
}$
$
static	size_t	ft_wlen(char *s, char c)$
{$
	size_t	i;$
	size_t	len;$
$
	i = 0;$
	len = 0;$
	while (s[i] != c && s[i])$
	{$
		i++;$
		len++;$
	}$
	return (len);$
}$
$
static	char	**ft_free(char **f, size_t j)$
{$
	size_t	i;$
$
	i = 0;$
	while (i < j)$
		free(f[i++]);$
	free(f);$
	return (NULL);$
}$
$
char	**ft_split(char const *s, char c)$
{$
	size_t		i;$
	size_t		countw;$
	size_t		l_count;$
	size_t		j;$
	char		**p;$
$
	i = -1;$
	j = 0;$
	l_count = 0;$
	countw = ft_countw((char *)s, c);$
	p = (char **) malloc(sizeof(char *) * (countw + 1));$
	if (!p)$
		return (NULL);$
	while (++i < countw)$
	{$
		while (s[j] == c)$
			j++;$
		l_count = ft_wlen((char *)s + j, c);$
		p[i] = ft_substr(s, j, l_count);$
		if (!p)$
			return (ft_free(p, i));$
		j += l_count + 1;$
	}$
	p[countw] = NULL;$
	return (p);$
}$
$
char	*ft_strjoin(char const *s1, char const *s2)$
{$
	char	*p;$
	int		i;$
	int		j;$
$
	i = strlen((char *)s1);$
	j = strlen((char *)s2);$
	p = malloc(i + j + 2);$
	if (!(p))$
		return (0);$
	strcpy(p, (char *)s1);$
	strcpy(&p[i], "/");$
	strcpy(&p[i + 1], (char *)s2);$
	return (p);$
}$
$
char	*ft_getabspath(char **path, char **tmp)$
{$
	int		i;$
	char	*cmd;$
	int		fd;$
$
	i = -1;$
	cmd = NULL;$
	while (path[++i])$
	{$
		cmd = ft_strjoin(path[i], tmp[0]);$
		fd = open(cmd, O_RDONLY);$
		if (fd > 0)$
			break ;$
		close(fd);$
		free(cmd);$
	}$
	close(fd);$
	return (cmd);$
}$
$
char	*ft_getpath(char **env, char *cmd)$
{$
	char	**tmp;$
	char	**path;$
	int		i;$
$
	i = -1;$
	tmp = ft_split(cmd, ' ');$
	while (env[++i])$
		if (!strncmp(env[i], "PATH", 4))$
			cmd = *(env + i) + 5;$
	path = ft_split(cmd, ':');$
	if (!tmp[0])$
		return (NULL);$
	cmd = ft_getabspath(path, tmp);$
	//ft_free_split(path);$
	//ft_free_split(tmp);$
	return (cmd);$
}$
$
$
$
int     function(char   *s)$
{$
    int     fd;$
    fd = open(s, O_RDONLY);$
    dup2(fd, 0);$
    close(fd);$
    return (0);$
}$
$
int     function2(char  *p)$
{$
    int fd;$
$
    fd = open(p, O_WRONLY | O_CREAT | O_TRUNC , 0777);$
    dup2(fd, 1);$
    close(fd);$
    return (0);$
}$
$
void        executecmd(char *str, char  **env)$
{$
    char    **p;$
    char	*cmd;$
$
	cmd = ft_getpath(env, str);$
    p = ft_split(str, ' ');$
$
    execve(cmd, p, env);$
   // write(2, "hey\n", 4);$
}$
$
int     pipefunc(char   **argv, char    **env)$
{$
    pid_t   pid1;$
    int fd[2];$
    int     i;$
    pid_t   pid2;$
$
    pid1 = fork();$
    if (pid1 == 0)$
    {$
        pipe(fd);$
        pid2 = fork();$
        if (pid2 == 0)$
        {$
            dup2(fd[1], 1);$
			close(fd[0]);$
            executecmd(argv[0], env);$
            exit(-1);$
        }$
        else$
        {$
            dup2(fd[0], 0);$
			close(fd[1]);$
			close(fd[0]);$
            executecmd(argv[1], env);$
            exit(-1);$
        }$
    }$
    else$
        waitpid(pid1, &i, 0);$
    return (0);$
}$
int     main(int    argc, char  **argv, char    **env)$
{$
    function(argv[1]);$
    function2(argv[4]);$
$
    pipefunc(&argv[2], env);$
}
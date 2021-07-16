#ifndef PIPEX_H

# define PIPEX_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <dirent.h>
# include <stdio.h>
# include <libgen.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>

void	log_error(char *str, int i);
size_t	ft_strlen(const char  *str);
int		pipe_execution(char **argv, char **env);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif
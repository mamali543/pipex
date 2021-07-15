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

int     main(int    argc, char  **argv, char   **env)
{
    int i = -1;
    char    *cmd = argv[2];
    char    **tmp;

    tmp = ft_split(cmd, ' ');
	while (env[++i])
		if (!(strncmp(env[i], "PATH", 4)))
			cmd = *(env + i) + 5;
    if (!tmp[0])
        printf("%s\n", cmd);
    return 0;
}
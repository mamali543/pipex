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

int     function(char   *s)
{
    int     fd;
    fd = open(s, O_RDONLY);
    dup2(fd, 0);
    close(fd);
}

int     function2(char  *p)
{
    int fd;

    fd = open(p, O_WRONLY | O_CREAT | O_TRUNC , 0777);
    dup2(fd, 1);
    close(fd);
}

int     pipefunc(char   **argv, char    **env)
{
    pid_t   pid1;
    int fd[2];
    int     i;
    pid_t   pid2;

    pid1 = fork();
    if (pid1 == 0)
    {
        pipe(fd);
        pid2 = fork();
        if (pid2 == 0)
        {
            dup2(fd[1], 1);
            
            execvp();
            printf("he\n");
            exit(-1);
        }
        else
        {
            dup2(fd[0], 0);
            printf("HHHHHHHH\n");
            exit(-1);
        }
    }
    else
        waitpid(pid1, &i, 0);
}
int     main(int    argc, char  **argv, char    **env)
{
    function(argv[1]);
    function2(argv[4]);
    pipefunc(&argv[2], env);
    printf("jgbuybuhbusdfghjk");
}
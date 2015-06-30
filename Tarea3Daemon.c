#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

int main(int argc, char* argv[])
{
	time_t now = time(NULL);

    pid_t pid = 0;
    pid_t sid = 0;
    FILE *fp= NULL;
    int i = 0;
    pid = fork();

    if (pid < 0)
    {
        printf("Fallo en la creacion del proceso hijo!\n");
        exit(1);
    }

    if (pid > 0)// its the parent process
    {
       printf("pid del proceso hijo %d \n", pid);
        exit(0); //terminate the parent process succesfully
    }

    umask(0);//unmasking the file mode

    sid = setsid();//set new session
    if(sid < 0)
    {
        exit(1);
    }

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    fp = fopen ("/archivodaemon.txt", "w+");
    while (1)
    {
        sleep(5);
        now = time(NULL);
        if(i == 1) 
        {
			fprintf(fp, "Hora de Inicio: %s  Eliab Lemus Barrios 200413090 \n", ctime(&now));	
		}
        fprintf(fp, "Log de la tarea: %d %s  \n ",i, ctime(&now));	
		fflush(fp);  
        i++;
    }
  
    return (0);
}

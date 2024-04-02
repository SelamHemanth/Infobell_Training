#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void waitstatus(int status)
{
	if(WIFEXITED(status))
		printf("Child terminated normally\n");
	else
		printf("Child terminated abnormally\n");
	printf("Status of child process -> %d\n",WEXITSTATUS(status));
	if(WIFSIGNALED(status))
	{
		printf("Child terminated by using signal\nNumber of signals are %d\n",WTERMSIG(status));
		if(WCOREDUMP(status))
			printf("Child process produces core dump\n");
	}
}

void shell(char *args[])
{
    if (execvp(args[0], args) == -1)
    {
        perror("execvp");
        exit(1);
    }
}

int main() 
{
	int status;
    char command[1024];
    char *args[6 + 1];
    while (1) 
    {
        int i = 0;
        printf(">>> ");
        if (fgets(command,1024, stdin) == NULL) {
            perror("fgets");
            exit(1);
        }
        command[strcspn(command, "\n")] = '\0';
        if (strcmp(command, "q") == 0) {
            break;
        }
        args[i] = strtok(command, " "); 
        while (args[i] != NULL && i < 6)
       	{
            i++;
            args[i] = strtok(NULL, " ");
        }
        args[i] = NULL;
        pid_t pid = fork();
        if (pid == 0)
       	{
            shell(args);
            exit(1);
        }
       	else if (pid == -1)
       	{
            perror("fork");
            exit(1);
        }
       	else
       	{
            wait(&status);
        }
	waitstatus(status);
    }

    return 0;
}


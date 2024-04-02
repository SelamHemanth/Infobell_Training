#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

void signal_handler(int sig) 
{
    printf("Received signal %d\n", sig);
}

int main() 
{
    pid_t pid;
    struct sigaction act;
    act.sa_handler = signal_handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    if (sigaction(SIGINT, &act, NULL) < 0)
    {
        perror("sigaction");
        exit(1);
    }
    if ((pid = fork()) < 0)
    {
        perror("fork failed\n");
        exit(1);
    } 
    else if (pid == 0)
    {
        printf("Child process created, PID: %d\n", getpid());
        pause();
    } 
    else
    {
        printf("Parent process created, PID: %d\n", getpid());
        sleep(2); 
        printf("Sending SIGINT signal to child process\n");
        if (kill(pid, SIGINT) < 0)
       	{
            perror("kill failed");
            exit(1);
        }
        wait(NULL);
        printf("Parent process exiting\n");
    }

    return 0;
}


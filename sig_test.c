#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <stdlib.h>

void handler1(int signal)
{
	printf("jandler 1\n");
}
void handler2(int signal)
{
	printf("jandler 2\n");
}
int main()
{
	int pid = fork();
	signal(SIGINT, handler1);
	signal(SIGINT, SIG_IGN);	
	if (pid == 0)
	{
		signal(SIGINT, handler2);
		while (1);
		pause();
		//sleep(8);
		exit(1);
	}
	wait(NULL);
	return 0;
}

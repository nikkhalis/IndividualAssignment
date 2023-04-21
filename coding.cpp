#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
 
#define ID_LENGTH 4
#define ID_WAIT_INTERVAL 2
 
void getID(char id[ID_LENGTH + 1]) 
{
  srand(getpid() + getppid());
 
  id[0] = 49 + rand() % 7;
 
  for(int i = 1; i < ID_LENGTH; i++) 
  {
    id[i] = 48 + rand() % 7;
  }
 
  id[ID_LENGTH] = '\0';
}
 
 
int main(void) 
{
  while(1) 
  {
    int pipefds[2];
    char id[ID_LENGTH + 1];
    char buffer[ID_LENGTH + 1];
    void sigint_handler(int sig);
	char s[50];
	char name[50];
	
	if(signal(SIGINT,sigint_handler)==SIG_ERR)
	{
		perror("signal");
		exit(0);
	}

	pipe(pipefds);
 
    pid_t pid = fork();
 
    if(pid == 0) 
	{
      getID(id); 
      close(pipefds[0]);
      write(pipefds[1], id, ID_LENGTH + 1);	
     
	printf ("WELCOME TO NEKLEONG BANK");
	printf ("\nPlease enter your name: ");
	fgets (name, 50, stdin);
	printf("This is your number>");


	sleep (ID_WAIT_INTERVAL);
	exit (EXIT_SUCCESS);
	}
	
	if(pid > 0) 
	{
      wait(NULL); 
 
      close(pipefds[1]); 
      read(pipefds[0], buffer, ID_LENGTH + 1); 
      close(pipefds[0]); 
      printf("%s\n\n", buffer);
    }
}
    return EXIT_SUCCESS;

}


void sigint_handler (int sig)
{
	printf("\nThe counter already is closed\n");
	exit(1);
}
    

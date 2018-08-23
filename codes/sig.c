/*filename:sig.c   515111910078 yangjunchen*/
/*Purpose: print “sleep\n” per second. When the progress receive the SIGINT signal, it start to print “hello\n” every two seconds, while it still print “sleep\n” at the original frequency. The progress will exit after 10s. */
/*Usage: ./Sig */
#include<stdio.h>
#include<sys/signal.h>
#include <unistd.h>
void sig_handler(int sig)
{
	printf("hello\n");
	sleep(2000);
}

void alrm_handler(int sig)
{
	exit(0);
}


int main()
{
  signal(SIGINT,sig_handler);/*use my own handler to print hello*/
  signal(SIGALRM,alrm_handler); /*use alarm to count 20s then signal to exit*/
	alarm(20);
	while(1)
	{
		printf("sleep\n");;
		sleep(1000);
	}
}


/*filename:MyShell.c   515111910078   yangjunchen*/
/*Purpose: shell-like program that illustrates how Linux spawns processes.sufficient to handle just ``argument-less'' commands, such as ls and date.*/
/*Usage: ./MyShell */

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_LINE 100
#define MAX_ARG 100

void eval(char *cmd);

int main()
{
	char cmd[MAX_LINE];
	while(1)
	{
		printf(">");
		/*read in*/
		fgets(cmd,MAX_LINE,stdin);
		if(feof(stdin)) exit(0);
		/*evaluate the command*/
		eval(cmd);
	}
}

void eval(char * cmd)
{
        char * argv[2];
        argv[0] = NULL;
        argv[1] = NULL;
	/*copy the cmd to argv[0](leave out the final \n)*/
	argv[0] = (char*)malloc((strlen(cmd)-1)*sizeof(char));
	strncpy(argv[0],cmd,strlen(cmd)-1);
      	if(argv[0]==NULL) return;
	/*execute the command*/
	if(execvp(argv[0],argv)<0)
	{
		printf("%s:Command not found.\n",argv[0]);
		exit(0);
	}
	return;
}

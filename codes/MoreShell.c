 /*filename:MoreShell.c   515111910078   yangjunchen*/
/*Purpose:allowing arguments to the commands. For example, it should be able to execute commands such as more filename and ls –l ~/tmp etc.*/
/*Usage: ./MoreShell*/
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_LINE 100
#define MAX_ARG 100

void eval(char *cmd);
void split(char *cmd,char *argv[]);

int main()
{
	char cmd[MAX_LINE];
	while(1)
	{
		printf(">");
		fgets(cmd,MAX_LINE,stdin);
		if(feof(stdin)) exit(0);
		/*evaluate the command*/
		eval(cmd);
	}
}

void eval(char * cmd)
{
  char * argv[MAX_ARG];
  char buf[MAX_LINE];
  strcpy(buf,cmd);
  /*split the command to argv by space*/
	split(buf,argv);
	
       
      	if(argv[0]==NULL) return;
	/*execute*/
	if(execvp(argv[0],argv)<0)
	{
		printf("%s:Command not found.\n",argv[0]);
		exit(0);
	}
}

void split(char * cmd, char *argv[])
{
  char *p;
  int i = 0;
  /*use strtok to split*/
  p = strtok(cmd," ");
  argv[i] = (char*)malloc((strlen(p))*sizeof(char));
  strncpy(argv[i++],p,strlen(p));
  while(p = strtok(NULL," \n"))
    {
      argv[i] = (char*)malloc((strlen(p))*sizeof(char));
      strncpy(argv[i++],p,strlen(p));
     }
  /*set the last argv to NULL*/
  argv[i] = NULL;
}

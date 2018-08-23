/*filename:DupShell.c   515111910078   yangjunchen*/
/*Purpose:8.	Add to the mini-shell ability to execute command lines with commands connected by pipes. Use dup system call to redirect IO. Example: ls -l | wc. */
/*Usage: ./DupShell*/
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#define MAX_LINE 100
#define MAX_ARG 100

void eval(char * cmd);
void split(char * cmd, char *argv[]);



int main()
{
	char cmd[MAX_LINE];
	while(1)
	{
		printf(">");
		fgets(cmd,MAX_LINE,stdin);
		if(feof(stdin)) exit(0);

		eval(cmd);
	}
}

void eval(char * cmd)
{
	char * argv[MAX_ARG];
  	char buf[MAX_LINE];
  	char *buf1;
  	char *buf2;
  	strcpy(buf,cmd);
  	int flag;
  	int child_status;
  	int pfds[2];
     
       	char *p;
	int gap1;

	/*judge if this is a command with a pipe*/
	if((p = strchr(buf,'|'))==NULL) flag = 0;
	else
	{
	  /*split the command to 2 parts ,buf1,buf2, by '|' if it's a pipe*/
	  buf1 = (char*)malloc((gap1 = p-buf)*sizeof(char));
	  strncpy(buf1,buf,gap1);
	  
	  
	  buf2 = (char*)malloc((strlen(buf)-gap1-2)*sizeof(char));
	  strncpy(buf2,p+1,strlen(buf)-gap1-2);
	 
	  
	  flag = 1;
	}


       
  	switch(flag)
  	{
	           case 0:/*if there is no pipe, use the previous program*/
  			split(buf,argv);
  		  	if(argv[0]==NULL) return;
			if(execvp(argv[0],argv)<0)
			{
				printf("%s:Command not found.\n",argv[0]);
				exit(0);
			}
			break;
		case 1:
		  /*create a pipe*/
		  if(pipe(pfds)==0)
		    {
		        if(fork() == 0) 
			{
     				split(buf1,argv);
				
				if(argv[0]==NULL) return;
				/*son process close the stdout file descriptor 1 and assign it to pipe's write end, then close the pipe's read end*/
					close(1);
				       	dup2(pfds[1],1);
				close(pfds[0]);
				/*execute the 1st command and write it to pipe*/
				if(execvp(argv[0],argv)<0)
				{
					printf("%s:Command not found.\n",argv[0]);
					exit(0);
				}
				exit(0);
			}				//split new_argv[2], use dup, exe
 			else
 			{
 				split(buf2,argv);
			       
 				if(argv[0]==NULL) return;
 			     	/*father process close the stdin file descriptor 0 and assign it to pipe's read end, then close the pipe's write end*/
				close(0);
				dup2(pfds[0],0);
 				close(pfds[1]);
				/*use pipe's data to execute*/
 				if(execvp(argv[0],argv)<0)
				{
					printf("%s:Command not found.\n",argv[0]);
					exit(0);
				}
				wait(&child_status);
				return ;

 			}
		    }
  	}
}







void split(char * cmd, char *argv[])
{
  char *p;
  int i = 0;
  p = strtok(cmd," ");
  argv[i] = (char*)malloc((strlen(p))*sizeof(char));
  strncpy(argv[i++],p,strlen(p));
  while(p = strtok(NULL," \n"))
    {
      argv[i] = (char*)malloc((strlen(p))*sizeof(char));
      strncpy(argv[i++],p,strlen(p));
     }
  argv[i] = NULL;
}


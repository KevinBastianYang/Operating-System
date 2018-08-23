/*filename:PipeCopy.c   515111910078   yangjunchen*/
/*Purpose:fork two processes one for reading from a file (source file) and the ather for writing (destination file) into. These two programs communicate using pipe system call. Once again the program accomplishes copying files, the names of which are specified as command-line arguments.*/
/*Usage: ./PipeCopy srcfile destfile */
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<sys/types.h>
#define MAX_LINE 1000
#define BUFFER_SIZE 1000000
#define syserr(str) {perror(str);exit(1);}

int main(int argc,char const *argv[])
{
	int pfd[2];
	int child_status;
	char tmpline[MAX_LINE];
	char *strline=(char*)malloc((MAX_LINE+1)*sizeof(char)),*readline = (char*)malloc((BUFFER_SIZE)*sizeof(char));
	long int leng;
	char num_tmp[25];
	char num_str[25];
	FILE *fpr, *fpw;
	/*create a pipe*/
	if(pipe(pfd) == -1) syserr("Create pipe"); 
	/*parameter process*/
	if(argc == 1)
	{
		printf("Usage: ./PipeCopy srcFile desFile\n");
		return 0;
	}

	else if(argc != 3) 
	{
		printf("Error: Wrong Parameters\n");
		printf("Usage: ./PipeCopy srcFile desFile\n");
		return 1;
	}

		
	else
	{
		switch(fork())
		{
			case -1:
				syserr("fork");
			
		
			case 0:
			  close(pfd[1]);/*close write*/

				fpw=fopen(argv[2],"rb+");
				if(fpw == NULL)
				{
					printf("Error: Wrong write file name, please check! \n");
					return 3;	
				}
					/*son read data from pipe*/
				read(pfd[0],readline,BUFFER_SIZE);
				fputs(readline,fpw);
				fclose(fpw);
				exit(0);

			default:
			  /*father sends data through pipe*/
			  close(pfd[0]);/*close read*/
				fpr=fopen(argv[1],"r");
				if(fpr == NULL)
				{
					printf("Error: Wrong read file name, please check! \n");
					return 3;	
				}
				/*read files line by line and add it to strline, which reallocate space if in need*/
				while(fgets(tmpline,MAX_LINE,fpr)!=NULL)
				{	
					strcat(strline,tmpline);
					strline = (char*)realloc(strline,(MAX_LINE+1)*sizeof(char));
					
				}
				/*send strline to pipe*/
				if(write(pfd[1],strline,strlen(strline)+1) == -1) perror("Write pipe");
				wait(&child_status);
				fclose(fpr);
				break;


		}
	}	
	

	
	
	
}

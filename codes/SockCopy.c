/*filename:SockCopy.c   515111910078  yangjunchen */
/*Purpose: fork two processes one for reading from a file (source file) and the other for writing (destination file) into. These two programs communicate using Socket. Once again the program accomplishes copying files, the names of which are specified as command-line arguments.*/
/*Usage:./SockCopy srcfile desfile*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sstream>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define MAX_LINE 1000
#define BUFFER_SIZE 1000000

int main(int argc, char const *argv[])
{
  /*parameter process*/
	if(argc == 1)
	{
		printf("Usage: ./SocketCopy srcFile desFile\n");
		return 0;
	}

	else if(argc != 3) 
	{
		printf("Error: Wrong Parameters\n");
		printf("Usage: ./SocketCopy srcFile desFile\n");
		return 1;
	}
	else
	{
		int child_status;
		
		if(fork() == 0)
		{
		  /*create a client socket*/
			int sockfd;
			sockfd = socket(AF_INET,SOCK_STREAM,0);
			struct sockaddr_in serv_addr;
			struct hostent *host;
			serv_addr.sin_family = AF_INET;
			host = htonl(INADDR_ANY);
			
			memcpy(&serv_addr.sin_addr.s_addr,host->h_addr,host->h_length);
			serv_addr.sin_port=htons(BASIC_SERVER_PORT);
			/*connect to server*/
			connect(sockfd,(sockaddr*)&serv_addr,sizeof(serv_addr));

			File *fpw;
			fpw=fopen(argv[2],"rb+");
			if(fpw == NULL)
			{
				printf("Error: Wrong write file name, please check! \n");
				return 3;	
			}
			char *readline = (char*)malloc((BUFFER_SIZE)*sizeof(char));
			/*read line into readline from server*/
			read(sockfd,readline,BUFFER_SIZE);
			fputs(readline,fpw);
			fclose(fpw);
			close(sockfd);
			exit(0);
		}
		else
		  {
		    /*create a socket*/
			int sockfd;
			sockfd = socket(AF_INET,SOCK_STREAM,0);
			if(sockfd<0){ perror("ERROR opening socket"); exit(2);}

			/*bind the socket*/
			struct sockaddr_in serv_addr;
			serv_addr.sin_family = AF_INET;
			serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
			serv_addr.sin_port = htons(BASIC_SERVER_PORT);
			bind(sockfd,(sockaddr*)&serv_addr,sizeof(serv_addr));

			/*listen*/
			listen(sockfd,5);

			/*accept client*/
			int client_sockfd;
			struct  sockaddr_in client_addr;
			int len = sizeof(client_addr);
			client_sockfd = accept(sockfd,(sockaddr*)&client_addr,&len);

			File * fpr;
			char *strline=(char*)malloc((MAX_LINE+1)*sizeof(char));
			char tmpline[MAX_LINE];
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
			/*send strline to client*/
			if(write(client_sockfd,strline,strlen(strline)+1) == -1) perror("Write socket");
			wait(&child_status);
			close(client_sockfd);
			close(sockfd);
			fclose(fpr);
			return 0;
		}
	}
	
}

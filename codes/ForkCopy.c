/*filename:ForkCopy.c   515111910078  yangjunchen*/
/*Purpose:create a new process to copy the files using the MyCopy. This program spawns a new process using fork system call. Then use execl to execute MyCopy program. The source and destination file names presented as command-line arguments are  passed to execl as system call arguments. The main process waits for completion of copy operation using wait system call. */
/*Usage: ./ForkCopy   then   ./MyCopy srcFile desFile */
#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
int main(int argc, char const *argv[])
{
	int child_status;
	if(fork() == 0) /*son to execute MyCopy file*/
	{
		execl("MyCopy",argv[0],argv[1],argv[2],NULL);
		return 0;
	}
	else  /*father waits to clean the corpse*/
	{
		wait(&child_status);
		return 0;
	}
}

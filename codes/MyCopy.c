/*filename:MyCopy.c 515111910078 yangjunchen*/
/*Purpose:Open the source file in read only mode and destination file in read/write mode. While the main function will carry out file opening and closing, a separate copy function needs to be written to do the actual copying. Copying can be done in blocks of suitable size.*/
/*Usage:./MyCopy srcFile desFile*/
#include<stdio.h>
#define MAX_LINE 1000
void copy(FILE *file_r, FILE *file_w)
{
	char strline[MAX_LINE];
	/*copy line by line*/
	while(fgets(strline,MAX_LINE,file_r)!=NULL)
	{
		fputs(strline,file_w);
	}
}



int main(int argc,char *argv[])
{
  FILE *fpr, *fpw;
  /*paramters process*/
	if(argc == 1)
	{
		printf("Usage: ./MyCopy srcFile desFile\n");
		return 0;
	}

	else if(argc != 3) 
	{
		printf("Error: Wrong Parameters\n");
		printf("Usage: ./MyCopy srcFile desFile\n");
		return 1;
	}
	/*copy process*/
	else if((fpr=fopen(argv[1],"r"))!=NULL && (fpw=fopen(argv[2],"rt+"))!=NULL) 
	{
	        copy(fpr,fpw);
		fclose(fpr);
		fclose(fpw);
		return 0;
	}

	else
	{
		printf("Error: Wrong file name, please check! \n");
		return 3;
	}
}

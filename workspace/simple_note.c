#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "headerfile/hacking.h"

void fatal(char *);
void *ec_malloc(unsigned int);

main(int argc,char *argv[])
{
	int userid,fd;
	char *buffer,*datafile;
	buffer=(char *)ec_malloc(100);
	datafile=(char *)ec_malloc(20);

	if((argc>3)||(argc==1)){
                fatal("while creating main elements,");
                printf("use: %s <file name> <data>\n",argv[0]);
        }
        strcpy(datafile,argv[1]);
        if(argc==2)
               buffer[0]=0;
        else
               strcpy(buffer,argv[2]);

	printf("[debug] buffer %p:\'%s\'\n",buffer,buffer);
	printf("[debug] data file %p:\'%s\'\n",datafile,datafile);
	
	strncat(buffer, "\n",1);

	
	fd=open(datafile,O_WRONLY|O_CREAT|O_APPEND,S_IRUSR|S_IWUSR);
	if(fd==-1)
	{
		fatal("while openig the file,");
		printf("your path worng or internal error");
	}
	printf("[debug] file_writer is %d\n",fd);
	userid=getuid();

	if(write(fd,&userid,4)==-1)
		fatal("while writing uid in main()");
	write(fd,"\n",1);

	if(write(fd,buffer,strlen(buffer))==-1)
	{
		fatal("while writing the file,");
	}
	write(fd,"\n",1);
	
	if(close(fd)==-1)
	{
		fatal("while closing the file,");
	}
	
	printf("complete!\n");
	free(buffer);
	free(datafile);
}


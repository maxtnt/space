#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
main()
{	
	FILE *fd;
	char *buffer;
	long temp;
	fd=fopen("a.txt","wt");
	system("find -perm 600>a.txt");
	fseek(fd,0l,SEEK_END);
	temp=ftell(fd);
	printf("%d",temp);
	fclose(fd);
	fd=fopen("a.txt","rt");
	buffer=(char *)malloc((int)temp);
	fread(buffer,sizeof(char),(int)temp,fd);
	system("rm -f a.txt");
	printf("%s",buffer);
}//END MAIN

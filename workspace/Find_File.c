#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
void Find_File(long *temp,char *buffer)
{
        FILE *fd;
        fd=fopen("a.txt","wt");
        system("find -perm 600>a.txt");
        fseek(fd,0l,SEEK_END);
        *temp=ftell(fd);
        fclose(fd);
        fd=fopen("a.txt","rt");
        fread(buffer,sizeof(char),(int)(*temp),fd);
}//END FUNCTION
main()
{
	long count;
	char buffer[(int)count];
	Find_File(&count,buffer);
	printf("%s",buffer);
}//END MAIN

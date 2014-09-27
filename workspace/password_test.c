#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_identity(char *password)
{
	int auth_flag=0;
	char password_buffer[16];

	strcpy(password_buffer,password);

	if((strcmp(password_buffer,"brilling")==0)||(strcmp(password_buffer,"outgrabe"))==0)
	{
		auth_flag=1;
	}
	return auth_flag;
}
main(int argc,char *argv[])
{
	if(argc<2)
	{
		printf("to use %s <password>",argv[0]);
		exit(0);
	}
	printf("=======================result===================\n");
	if(check_identity(argv[1]))
		printf("access permit\n");
	else
		printf("access denied\n");
	printf("=======================result===================\n");
}

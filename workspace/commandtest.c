#include <stdio.h>
void usage(char *program_name)
{
	printf("how to use:%s <message> <count>\n",program_name);
exit(1);
}
int main(int argc,char *argv[])
{
	int i,count;
	//if(argc<3)
	//{
	//usage(argv[0]);
	//}
	count=atoi(argv[2]);
	printf("%d replay\n",count);
	for(i=0;i<count;i++)
	printf("%3d -%s\n",i,argv[1]);
}

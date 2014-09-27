#include <stdio.h>
#include <string.h>

main(int argc,char *argv[])
{
	int value=5;
	char buffer_one[8],buffer_two[8];
	strcpy(buffer_one,"one");
	strcpy(buffer_two,"two");

	printf("[before] buffer_one is located in %p,buffer_one have \'%s\' \n",buffer_one,buffer_one);
	printf("[before] buffer_two is located in %p,buffer_two have \'%s\' \n",buffer_two,buffer_two);
	printf("[before] value is located in %p,value have %d(0x%08x)\n",&value,value,value);
	
	printf("\n[strcpy] %d byte is copied to buffer_two\n\n",strlen(argv[1]));
	strcpy(buffer_two,argv[1]);

	printf("[after] buffer_one is located in %p,buffer_one have \'%s\' \n",buffer_one,buffer_one);
        printf("[after] buffer_two is located in %p,buffer_two have \'%s\' \n",buffer_two,buffer_two);
        printf("[after] value is located in %p,value have %d(0x%08x)\n",&value,value,value);

}

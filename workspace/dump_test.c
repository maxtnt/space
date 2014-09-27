#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "headerfile/hacking.h"

main(int argc,char *argv[])
{
	FILE *Search_bot;
	char *search_area;
	long count;
	long count_buffer;
	char *file_list;
	int temp_start,temp_end;
	int many=0,max=0;
	int temp;
	int *temp_buffer;
	char *buffer;
	if(argc>3)
	{
		printf("HOW TO USE:%s <file to see>",argv[0]);
		exit(-1);
	}//END IF
	printf("file dumper is on\n");
	if(argc==2)
	{	
		search_area=malloc(sizeof(char)*strlen(argv[1]));
		strcpy(search_area,argv[1]);
		Search_bot=fopen(search_area,"rt");
		if(Search_bot==NULL)
		{
			printf("wrong file");
			exit(-1);
		}//END IF
		fread(buffer,sizeof(char),100,Search_bot);
		dump(buffer,100);
		printf("\n");
	}//END IF
	else
	{	
		printf("current directory%n%s%n\n",&temp_start,getenv("PWD"),&temp_end);
		printf("\n");
		Search_bot=fopen("a.txt","wt");
       		system("find -perm 600>a.txt");
       		fseek(Search_bot,0l,SEEK_END);
       		count=ftell(Search_bot);
		if(count==0)
		{
			printf("no found");
			exit(-1);
		}//END IF
       		fclose(Search_bot);
		search_area=(char *)malloc((int)count+(temp_end-temp_start)+1);
		search_area[(int)count+(temp_end-temp_start)]='\0';
		strcpy(search_area,getenv("PWD"));

		file_list=(char *)malloc((int)count+1);
		Search_bot=fopen("a.txt","rt");
		fread(file_list,sizeof(char),(int)count,Search_bot);
		strcat(file_list,"\0");
		fclose(Search_bot);
		system("rm -f a.txt");

		temp_buffer=(int *)malloc((int)count);
		buffer=(char *)malloc((int)count);	
                for(temp=0;temp<=count;temp++)
                {       
                	if(file_list[temp]=='/')
                        {       
                        	temp_buffer[max]=temp;
                               	max++;
                        }//END IF
                }//END FOR

		while(many<max)
		{
        		if((many<0)||(many>max))
       			{
                		printf("error");
                		exit(-1);
        		}//END IF
      			search_area[temp_end-temp_start]='/';
       			for(temp=temp_buffer[many];temp<temp_buffer[many+1]-3;temp++)
        		{
               			search_area[temp_end-temp_start+(temp+1-temp_buffer[many])]=file_list[temp+1];
			}//END FOR
			
			printf("%s\n",search_area);
			Search_bot=fopen(search_area,"rt");
			fseek(Search_bot,0l,SEEK_END);
			count_buffer=ftell(Search_bot);

			fseek(Search_bot,0l,SEEK_SET);
			buffer=(char *)realloc(buffer,(int)count_buffer+1);
			fread(buffer,sizeof(char),(int)count_buffer,Search_bot);
			buffer[(int)count_buffer]='\0';
			dump(buffer,(int)count_buffer);
			for(temp=1;temp<=count;temp++)
			{
				search_area[temp_end-temp_start+temp]='\0';
			}//END FOR
			printf("\n");
			many++;	
		}//END WHILE
	}//END ELSE
}//END MAIN


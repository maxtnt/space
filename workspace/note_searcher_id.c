#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "headerfile/hacking.h"

int print_note(int,int,char *);
int find_user_note(int,int);
int search_note(char *,char *);


main(int argc,char *argv[])
{
	int userid,printing=1,fd;
	char searchstring[100];
	char FILE_NAME[100];
	strcpy(FILE_NAME,"/root/workspace/note_for_you");
	
	if((argc>3)||(argc==1)){
		fatal(" while creating main elements");
		printf("use: %s <file name> <to search>(option)\n",argv[0]);
	}
	strcpy(FILE_NAME,argv[1]);
	if(argc==2)
		searchstring[0]=0;
	else
		strcpy(searchstring,argv[2]);
	userid=getuid();

	fd=open(FILE_NAME,O_RDONLY);
	if(fd==-1)
	{
		fatal("while opening file,");
		printf("your path is wrong or system error\n");
	}
	
	while(printing)
		printing=print_notes(fd,userid,searchstring);
	printf("--------end of the data--------\n");
	close(fd);
}

int print_notes(int fd,int uid,char *searchstring)
{
	int note_length;
	char byte=0,note_buffer[100];

	note_length=find_user_note(fd,uid);
	if(note_length==-1)
		return 0;

	read(fd,note_buffer,note_length);
	note_buffer[note_length]=0;
	
	if(search_note(note_buffer,searchstring))
		printf(note_buffer);
	return 1;
}

int find_user_note(int fd,int user_uid)
{
	int note_uid=-1;
	unsigned char byte;
	int length;

	while(note_uid!=user_uid)
	{
		if(read(fd,&note_uid,4)!=4)
			return -1;
		if(read(fd,&byte,1)!=1)
			return -1;

		byte=length=0;
		while(byte!='\n')
		{
			if(read(fd,&byte,1)!=1)
				return -1;
			length++;
		}
	}
	lseek(fd,length *-1,SEEK_CUR);

	printf("[debug] userid:%d byte:%d\n",note_uid,length);
	return length;
}

int search_note(char *note,char *keyword)
{
	int i,keyword_length,match=0;
	
	keyword_length=strlen(keyword);
	if(keyword_length==0);
		return 1;

	for(i=0;i<strlen(note);i++)
	{
		if(note[i]==keyword[match])
			match++;
		else
		{
			if(note[i]==keyword[0])
			match=1;
			else
			match=0;
		}
		if(match==keyword_length)
			return 1;
	}
	return 0;
}

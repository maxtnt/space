void fatal(char *message)
{
	char error_message[100];
	
	strcpy(error_message,"critical error");
	strncat(error_message,message,83);
	perror(error_message);
	exit(-1);
}//END FUNCTION

void *ec_malloc(unsigned int size)
{
	void *ptr;
	ptr=malloc(size);
	if(ptr==NULL)
		fatal("while running the 'ec_malloc()'");
	return ptr;
}//END FUNCTION

void dump(const unsigned char *data_buffer,const unsigned int length)
{
	unsigned char byte;
	unsigned int ci,cj;
	for(ci=0;ci<length;ci++)
	{
		byte=data_buffer[ci];
		printf("%02x",data_buffer[ci]);
	if(((ci%16)==15)||(ci==length-1))
	{
		for(cj=0;cj<15-(ci%16);cj++)
			printf(" ");
		printf("| ");
		for(cj=(ci-(ci%16));cj<=ci;cj++)
		{
			byte=data_buffer[cj];
			if((byte>31)&&(byte<127))
				printf("%c",byte);
			else
				printf(".");
		}//END FOR
		printf("\n");
	}//END IF
	}//END FOR
}//END FUNCTION

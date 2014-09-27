//Hello here is the network headerfile

#define ETHER_ADDR_LEN 6
#define ETHER_HDR_LEN 14

struct ether_hdr
{
	unsigned char ether_dest_addr[ETHER_ADDR_LEN];//START
	unsigned char ether_src_addr[ETHER_ADDR_LEN];//DESTINATION
	unsigned short ether_type;//ETHTNET PACKET TYPE
};//END STRUCT

struct ip_hdr
{
	unsigned char ip_version_and_header_length;
	unsigned char ip_tos;
	unsigned short ip_len;
	unsigned short ip_id;
	unsigned short ip_frag_offset;
	unsigned char ip_ttl;
	unsigned char ip_type;
	unsigned short ip_checksum;
	unsigned int ip_src_addr;
	unsigned int ip_dest_addr;
};//END STRUCT 

struct tcp_hdr
{
	unsigned short tcp_src_port;
	unsigned short tcp_dest_port;
	unsigned int tcp_seq;
	unsigned int tcp_ack;
	unsigned char reserved:4;
	unsigned char tcp_offset:4;
	unsigned char tcp_flags;
#define TCP_FIN 0X01
#define TCP_SYN 0x02
#define TCP_RST 0x04
#define TCP_PUSH 0x08
#define TCP_ACK 0x10
#define TCP_URG 0x20
	unsigned short tcp_window;
	unsigned short tcp_checksum;
	unsigned short tcp_urgent;
};//END STRUCT

int send_string(int socketfd,unsigned char *buffer)
{
	int sent_bytes,bytes_to_send;
	bytes_to_send=strlen(buffer);
	
	while(bytes_to_send>0)
	{
		sent_bytes=send(socketfd,buffer,bytes_to_send,0);
		if(sent_bytes==-1)
		{
			return 0;
		}//END IF
		bytes_to_send-=sent_bytes;
		buffer+=sent_bytes;
	}//END WHILE
	return 1;
}//END FUNCTION

int recv_line(int socketfd,unsigned char *dest_buffer)
{
#define EOL "\r\n"
#define EOL_SIZE 2
	unsigned char *ptr;
	int eol_matched=0;
	
	ptr=dest_buffer;
	while(recv(socketfd,ptr,1,0)==1)
	{
		if(ptr==EOL[eol_matched])
		{
			eol_matched++;
		}//END IF
		if(eol_matched==EOL_SIZE)
		{
			*(ptr+1-EOL_SIZE)='\0';
			return strlen(dest_buffer);
		}//END IF
		else
		{
			eol_matched=0;
		}//END ELSE
		ptr++;
	}//END WHILE
	return 0;	
}//END FUNCTION

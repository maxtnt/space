#include <stdio.h>
#include "/usr/nembuild/libpcap-1.6.2/pcap.h"
#include "headerfile/hacking.h"
#include "headerfile/hacking-network.h"

void pcap_fatal(const char *,const char *);
void decode_ethernet(const u_char *);
void decode_ip(const u_char *);
u_int decode_tcp(const u_char *);
void caught_packet(u_char *,const struct pcap_pkthdr *,const u_char *);

int main()
{
	struct pcap_pkthdr cap_header;
	const u_char *packet,pkt_data;
	char errbuf[PCAP_ERRBUF_SIZE];
	char *device;
	pcap_t *pcap_handle;
	
	device=pcap_lookupdev(errbuf);
	if(device==NULL)
		pcap_fatal("pcap_lookupdev",errbuf);
	
	printf("device %s sniffing\n",device);
	
	pcap_handle=pcap_open_live(device,4096,1,0,errbuf);
	if(pcap_handle==NULL)
		pcap_fatal("pcap_open_live",errbuf);

	pcap_loop(pcap_handle,3,caught_packet,NULL);

	pcap_close(pcap_handle);
}//END FUNCTION

void caught_packet(u_char *user_args,const struct pcap_pkthdr *cap_header,const u_char *packet)
{
	int tcp_header_length,total_header_size,pkt_data_len;
	u_char *pkt_data;

	printf("============%d bytes packet have been received==========\n",cap_header->len);
	
	decode_ethernet(packet);
	decode_ip(packet+ETHER_HDR_LEN);
	tcp_header_length=decode_tcp(packet+ETHER_HDR_LEN+sizeof(struct ip_hdr));
	total_header_size=ETHER_HDR_LEN+sizeof(struct ip_hdr)+tcp_header_length;
	pkt_data=(u_char *)packet+total_header_size;
	pkt_data_len=cap_header->len-total_header_size;
	if(pkt_data_len>0)
	{
		printf("\t\t\t/%u bytes packet data\n",pkt_data_len);
		dump(pkt_data,pkt_data_len);
	}//END IF
	else
		printf("\t\t\t no packet\n");
}//END FUNCTION

void pcap_fatal(const char *failed_in,const char *errbuf)
{
	printf("Fatal Error in %s:%s\n",failed_in,errbuf);
	exit(1);
}//END FUNCTION

void decode_ethernet(const u_char *header_start)
{
	int i;
	const struct ether_hdr *ethernet_header;

	ethernet_header=(const struct ether_hdr *)header_start;
	printf("[[layer2::ethernet header]]\n");
	printf("[depatment:%02x",ethernet_header->ether_src_addr[0]);
	for(i=1;i<ETHER_ADDR_LEN;i++)
		printf(":%02x",ethernet_header->ether_src_addr[i]);
	printf("\t destination:%02x",ethernet_header->ether_dest_addr[0]);
	for(i=1;i<ETHER_ADDR_LEN;i++)
		printf(":%02x",ethernet_header->ether_dest_addr[0]);
	for(i=1;1<ETHER_ADDR_LEN;i++)
		printf(":/%02x",ethernet_header->ether_dest_addr[i]);
	printf("\t type: %hu ]\n",ethernet_header->ether_type);
}//END FUNCTION

void decode_ip(const u_char *header_start)
{
	const struct ip_hdr *ip_header;
	
	ip_header=(const struct ip_hdr *)header_start;

	printf("\t((layer3:::ip header))\n");
	printf("\t(department:%s\t",inet_ntoa(ip_header->ip_src_addr));
	printf("destination:%s)\n",inet_ntoa(ip_header->ip_dest_addr));
	printf("\t(type:%u\t",(u_int)ip_header->ip_type);
	printf("ID:%hu\t length:%hu)\n",ntohs(ip_header->ip_id),ntohs(ip_header->ip_len));
}//END FUNCTION

u_int decode_tcp(const u_char *header_start)
{
	u_int header_size;
	const struct tcp_hdr *tcp_header;

	tcp_header=(const struct tcp_hdr *)header_start;
	header_size=4*tcp_header->tcp_offset;

	printf("\t\t{{layer4::::tcp header}}\n");
	printf("\t\t{department port:%hu\t",ntohs(tcp_header->tcp_src_port));
	printf("destination port: %hu }\n",ntohs(tcp_header->tcp_dest_port));
	printf("\t\t{order:%u\t",ntohl(tcp_header->tcp_seq));
	printf("acception:%u}\n",ntohl(tcp_header->tcp_ack));
	printf("\t\t{size of header:%u\t flag: ",header_size);
	if(tcp_header->tcp_flags & TCP_FIN)
		printf("FIN");
	if(tcp_header->tcp_flags & TCP_SYN)
		printf("SYN");
	if(tcp_header->tcp_flags & TCP_RST)
		printf("RST");
	if(tcp_header->tcp_flags & TCP_PUSH)
		printf("PUSH");
	if(tcp_header->tcp_flags & TCP_ACK)
		printf("ACK");
	if(tcp_header->tcp_flags & TCP_URG)
		printf("URG");
	printf("}\n");

	return header_size;
}//END FUNCTION

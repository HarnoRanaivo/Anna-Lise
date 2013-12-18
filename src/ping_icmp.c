#include "ping_icmp.h"

void init (icmp4_packet * p, echo_reply * er, connexion * c, info_addr * ia, char * dest, compteur * cpt)
{	
	er->paquet = q_malloc(sizeof(iphdr) + sizeof(icmphdr));
    er->buffer = q_malloc(sizeof(iphdr) + sizeof(icmphdr));
    
    ia->src = get_source_ipv4(IPPROTO_ICMP);
    ia->dest = get_ipv4(dest,IPPROTO_ICMP);
    ia->addr_dest = char_to_ip(dest);
    
    cpt->paquets_transmis = 0;
    cpt->paquets_recus = 0;
    
    c->addr.sin_family = AF_INET;
    c->addr.sin_addr.s_addr = inet_addr(ia->addr_dest);
    
    icmp4_packet_init(p,ia->dest);
}

void init_socket (connexion * c, int optval)
{
	if ((c->sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == -1)
    {
		perror("socket");
		exit(EXIT_FAILURE);
    }
    setsockopt(c->sockfd, IPPROTO_IP, IP_HDRINCL, &optval, sizeof(int));
}

char * char_to_ip (char * dest)
{
    struct hostent* h;
	h = gethostbyname(dest);
    return inet_ntoa(*(struct in_addr *)h->h_addr);
}

void send_paquet (connexion * c, echo_reply * er, icmp4_packet * p, compteur * cpt)
{
	sendto(c->sockfd, er->paquet, p->ip_header.tot_len, 0, (struct sockaddr *)&c->addr, sizeof(struct sockaddr));
	cpt->paquets_transmis++;
}

void answer_send (connexion * c, echo_reply * er, iphdr* ip_reply, info_addr * ia, compteur * cpt)
{
	int size_paquet;
	unsigned int size_addr;
	
	size_addr = sizeof(c->addr);
	
    if (( size_paquet = recvfrom(c->sockfd, er->buffer, sizeof(iphdr) + sizeof(icmphdr), 0, (struct sockaddr *)&c->addr, &size_addr)) == -1)
    {
		perror("recv");
    }
    else
    {
		cpt->paquets_recus++;
		ip_reply = (iphdr*) er->buffer;
		printf("%d bytes from %s: icmp_req=%d ttl=%d\n", size_paquet, ia->addr_dest, cpt->paquets_transmis, ip_reply->ttl);
		sleep(1);
    }
}

void freedom (echo_reply * er, connexion * c)
{
	free(er->paquet);
	free(er->buffer);
	close(c->sockfd);
}

void affichage_fin (char* dest, compteur * cpt)
{
	printf("--- %s ping statistics ---\n",dest);
	printf("%d packets transmitted, %d received, %d%% paquet loss\n",cpt->paquets_transmis, cpt->paquets_recus, cpt->paquets_recus/cpt->paquets_transmis);
	printf("rtt min/avg/max = //\n");
}

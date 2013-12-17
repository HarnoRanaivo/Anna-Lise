#include "ping_icmp.h"

void init (icmp4_packet * p, echo_reply * er, connexion * c, info_addr * ia, char * dest, compteur * cpt)
{
	p = q_malloc(sizeof (icmp4_packet));
	
	er = q_malloc(sizeof (echo_reply));
	
	c = q_malloc(sizeof (connexion));
	
	ia = q_malloc(sizeof (info_addr));
	
	cpt = q_malloc(sizeof (compteur));
	
	
	er->paquet = q_malloc(sizeof(struct iphdr) + sizeof(struct icmphdr));
	
    er->buffer = q_malloc(sizeof(struct iphdr) + sizeof(struct icmphdr));
    
    strncpy(ia->src,get_source_ipv4(IPPROTO_ICMP),20);
    strncpy(ia->dest,get_ipv4(dest,IPPROTO_ICMP),20);
    
    cpt->paquets_transmis = 0;
    cpt->paquets_recus = 0;
    
    icmp4_packet_init(p,(u_int32_t) ia->dest);
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

void send_paquet (connexion * c, echo_reply * er, icmp4_packet * p, compteur * cpt)
{
	sendto(c->sockfd, er->paquet, p->ip->tot_len, 0, (struct sockaddr *)&c->addr, sizeof(struct sockaddr));
	cpt->paquets_transmis++;
}

void answer_send (connexion * c, echo_reply * er, iphdr* ip_reply, info_addr * ia, compteur * cpt)
{
	int size_paquet;
	int size_addr;
	
	size_addr = sizeof(c->addr);
	
    if (( size_paquet = recvfrom(c->sockfd, er->buffer, sizeof(struct iphdr) + sizeof(struct icmphdr), 0, (struct sockaddr *)&c->addr, &size_addr)) == -1)
    {
		perror("recv");
    }
    else
    {
		cpt->paquets_recus++;
		ip_reply = (struct iphdr*) er->buffer;
		printf("%d bytes from %s: icmp_req=%d ttl=%d\n", size_paquet, ia->dest, cpt->paquets_transmis, ip_reply->ttl);
		sleep(1);
    }
}

void freedom (icmp4_packet * p, echo_reply * er, connexion * c, info_addr * ia, compteur * cpt)
{
	free(er->paquet);
	free(er->buffer);
	free(p);
	free(er);
	close(c->sockfd);
	free(c);
	free(ia);
	free(cpt);
}

void affichage_fin (char* dest, compteur * cpt)
{
	printf("--- %s ping statistics ---\n",dest);
	printf("%d packets transmitted, %d received, %d%% paquet loss\n",cpt->paquets_transmis, cpt->paquets_recus, cpt->paquets_recus/cpt->paquets_transmis);
	printf("rtt min/avg/max = //\n");
}

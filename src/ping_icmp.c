#include "ping_icmp.h"

void init (icmp4_packet * p, connexion * c, info_addr * ia, char * dest, compteur * cpt)
{	
    get_ipv4(dest,IPPROTO_ICMP,&c->addr);
    ia->addr_dest = char_to_ip(dest);
    ia->dest = extract_ipv4(&c->addr);
    
    cpt->paquets_transmis = 0;
    cpt->paquets_recus = 0;
    
    icmp4_packet_init(p,ia->dest);
}

char * char_to_ip (char * dest)
{
    struct hostent* h;
	h = gethostbyname(dest);
    return inet_ntoa(*(struct in_addr *)h->h_addr);
}

void send_paquet (connexion * c, icmp4_packet * p, compteur * cpt)
{
	sendto(c->sockfd, p, sizeof(icmp4_packet), 0, (struct sockaddr *)&c->addr, sizeof(struct sockaddr));
	cpt->paquets_transmis++;
}

void answer_send (connexion * c, info_addr * ia, compteur * cpt)
{
	int succes;
	icmp4_packet paquet;
	
    if (( succes = receive_icmp_v4(c->sockfd,&c->addr,&paquet)) == -1)
    {
    }
    else
    {
		cpt->paquets_recus++;
		printf("%lu bytes from %s: icmp_seq=%d ttl=%d\n", sizeof(paquet), ia->addr_dest, paquet.icmp_header.un.echo.sequence, paquet.ip_header.ttl);
		sleep(1);
    }
}

void freedom (connexion * c)
{
	close(c->sockfd);
}

void affichage_fin (char* dest, compteur * cpt)
{
	printf("--- %s ping statistics ---\n",dest);
	printf("%d packets transmitted, %d received, %d%% paquet loss\n",cpt->paquets_transmis, cpt->paquets_recus, (cpt->paquets_transmis - cpt->paquets_recus)/cpt->paquets_transmis*100);
	printf("rtt min/avg/max = //\n");
}

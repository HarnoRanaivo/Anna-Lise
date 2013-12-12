#include "ping_icmp.h"

void init (paquets * p, echo_reply * er, connexion * c, info_addr * ia, char * dest, compteur cpt)
{
	p = malloc(sizeof (paquets));
	if (p == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	
	er = malloc(sizeof (echo_reply));
	if (er == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	
	c = malloc(sizeof (connexion));
	if (c == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	
	ia = malloc(sizeof (info_addr));
	if (ia == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	
	
	er->paquet = malloc(sizeof(struct iphdr) + sizeof(struct icmphdr));
	if (er->paquet == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	
    er->buffer = malloc(sizeof(struct iphdr) + sizeof(struct icmphdr));
    if (er->buffer == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
 
    
	p->ip = (struct iphdr*) er->paquet;
    p->icmp = (struct icmphdr*) (er->paquet + sizeof(struct iphdr));
    
    strncpy(ia->src,get_ip_src(),15);
    strncpy(ia->dest,dest,15);
    
    strncpy(ia->src,char_to_ip(ia->src),20);
    strncpy(ia->dest,char_to_ip(ia->dest),20);
    
    
    c->addr.sin_family = AF_INET;
    c->addr.sin_addr.s_addr = inet_addr(ia->dest);
    
    cpt.paquets_transmis = 0;
    cpt.paquets_recus = 0;
}

void set_up_IP_paquet (paquets * p, info_addr * ia)
{
	p->ip->ihl          = 5;
    p->ip->version      = 4;
    p->ip->tos          = 0;
    p->ip->tot_len      = sizeof(struct iphdr) + sizeof(struct icmphdr);
    p->ip->id           = htons(0);
    p->ip->frag_off     = 0;
    p->ip->ttl          = 64;
    p->ip->protocol     = IPPROTO_ICMP;
    p->ip->saddr        = inet_addr(ia->src);
    p->ip->daddr        = inet_addr(ia->dest);
    p->ip->check        = in_cksum((unsigned short *)p->ip, sizeof(struct iphdr));
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

void set_ICMP_ECHO (paquets * p)
{
	p->icmp->type               = ICMP_ECHO;
    p->icmp->code               = 0;
    p->icmp->un.echo.id         = random();
    p->icmp->un.echo.sequence   = 0;
    p->icmp-> checksum          = in_cksum((unsigned short *)p->icmp, sizeof(struct icmphdr));
}

char * get_ip_src()
{
    char buffer[256];
    struct hostent* h;
     
    gethostname(buffer, 256);
    h = gethostbyname(buffer);
     
    return inet_ntoa(*(struct in_addr *)h->h_addr);
}

char * char_to_ip (char* addr)
{
    struct hostent* h;
    
    h = gethostbyname(addr);
    
    return inet_ntoa(*(struct in_addr *)h->h_addr);
}

/*
 * in_cksum --
 * Checksum routine for Internet Protocol
 * family headers (C Version)
 */
unsigned short in_cksum(unsigned short *addr, int len)
{
    register int sum = 0;
    u_short answer = 0;
    register u_short *w = addr;
    register int nleft = len;
    /*
     * Our algorithm is simple, using a 32 bit accumulator (sum), we add
     * sequential 16 bit words to it, and at the end, fold back all the
     * carry bits from the top 16 bits into the lower 16 bits.
     */
    while (nleft > 1)
    {
      sum += *w++;
      nleft -= 2;
    }
    /* mop up an odd byte, if necessary */
    if (nleft == 1)
    {
      *(u_char *) (&answer) = *(u_char *) w;
      sum += answer;
    }
    /* add back carry outs from top 16 bits to low 16 bits */
    sum = (sum >> 16) + (sum & 0xffff);       /* add hi 16 to low 16 */
    sum += (sum >> 16);               /* add carry */
    answer = ~sum;              /* truncate to 16 bits */
    return (answer);
}

void send_paquet (connexion * c, echo_reply * er, paquets * p, compteur cpt)
{
	sendto(c->sockfd, er->paquet, p->ip->tot_len, 0, (struct sockaddr *)&c->addr, sizeof(struct sockaddr));
	cpt.paquets_transmis++;
}

void answer_send (connexion * c, echo_reply * er, struct iphdr* ip_reply, info_addr * ia, compteur cpt)
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
		cpt.paquets_recus++;
		ip_reply = (struct iphdr*) er->buffer;
		printf("%d bytes from %s: icmp_req=%d ttl=%d\n", size_paquet, ia->dest, cpt.paquets_transmis, ip_reply->ttl);
		sleep(1);
    }
}

void freedom (paquets * p, echo_reply * er, connexion * c, info_addr * ia)
{
	free(er->paquet);
	free(er->buffer);
	free(p);
	free(er);
	close(c->sockfd);
	free(c);
	free(ia);
}

void handler_int (int signum)
{
	fin_des_temps=0;
}

void affichage_fin (char* dest, compteur cpt)
{
	printf("--- %s ping statistics ---\n",dest);
	printf("%d packets transmitted, %d received, %d%% paquet loss\n",cpt.paquets_transmis, cpt.paquets_recus, cpt.paquets_recus/cpt.paquets_transmis);
	printf("rtt min/avg/max = //\n");
}
 
int main(int argc, char* argv[])
{
    echo_reply * er;
    paquets * p;
    connexion * c;
    info_addr * ia;
    compteur cpt;
    int optval;
    struct iphdr * ip_reply;
    struct sigaction sa;
    
    sa.sa_handler = handler_int;
    sa.sa_flags = 0;
    sigaction(SIGINT,&sa,NULL);
    
    
    init(p,er,c,ia,argv[1],cpt);
    set_up_IP_paquet(p,ia);
    init_socket(c,optval);
    set_ICMP_ECHO(p);
    
    while(fin_des_temps)
    {
		send_paquet(c,er,p,cpt);
		answer_send(c,er,ip_reply,ia,cpt);
	}

	affichage_fin(argv[1],cpt);
	
	freedom(p,er,c,ia);
	
    return 0;
}

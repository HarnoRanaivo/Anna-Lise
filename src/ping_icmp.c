/**
 * \file ping_icmp.c
 * \brief Implémentation de la fonction Ping. (implémentation)
 * \author MEYER Jérémy
 * \author RAZANAJATO Harenome
 * \date 2013
 * \copyright WTFPL version 2
 */
/* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details.
 */

#include "ping_icmp.h"

void init_domaine_IPv4 (icmp4_packet * p, connexion * c, info_addr * ia, char * dest, compteur * cpt)
{	
    get_ipv4(dest,IPPROTO_ICMP,&c->addr);
    reverse_dns_v4(ia->dom_dest,HOST_NAME_MAX+1,c->addr.sin_addr);
    ia->addr_dest = char_to_ip(ia->dom_dest);
    ia->dest = extract_ipv4(&c->addr);
    ia->dest_de_base = dest;
    
    cpt->paquets_transmis = 0;
    cpt->paquets_recus = 0;
    
    icmp4_packet_init(p,ia->dest);
    create_raw_socket(AF_INET,SOCK_RAW,IPPROTO_ICMP,&c->sockfd);
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

void answer_send (connexion * c, compteur * cpt, struct timeval * tv)
{
	icmp4_packet paquet;
    if (receive_icmp_v4(c->sockfd,&c->addr, tv, &paquet) != -1)
    {
		cpt->paquets_recus++;
		printf("%lu bytes from ",sizeof(paquet));
		print_host_v4(c->addr.sin_addr);
		printf(": icmp_req=%d ttl=%d ", paquet.icmp_header.un.echo.sequence+1, paquet.ip_header.ttl);
    }
}

void rtt(struct timeval timev, compteur * c)
{
	long double temps_aller_retour = extract_time(timev);
	c->sum += temps_aller_retour;
	if(temps_aller_retour<c->min)
		c->min = temps_aller_retour;
	if(temps_aller_retour>c->max)
		c->max = temps_aller_retour;
}

void freedom (connexion * c)
{
	close(c->sockfd);
}

void affichage_fin (info_addr * ia, compteur * cpt, struct timeval total)
{
	printf("--- %s ping statistics ---\n",ia->dest_de_base);
	printf("%d packets transmitted, %d received, %d%% paquet loss, time %.0Lfms\n",cpt->paquets_transmis, cpt->paquets_recus, (cpt->paquets_transmis - cpt->paquets_recus)/cpt->paquets_transmis*100,extract_time(total));
	printf("rtt min/avg/max = %.3Lf/%.3Lf/%.3Lf\n",cpt->min,cpt->sum/cpt->paquets_recus,cpt->max);
}

void pi_ng(icmp4_packet * p, connexion * c, compteur * cpt, struct timespec * req, struct timeval * tv)
{
	struct timeval debut, fin, diff;
	int avant = cpt->paquets_recus;
	gettimeofday(&debut,NULL);
	send_paquet(c,p,cpt);
	answer_send(c,cpt,tv);
	gettimeofday(&fin,NULL);
	diff = diff_timeval(debut,fin);
	if((avant == 0) &&(cpt->paquets_recus == 1))
	{
	    cpt->sum = .0;
		cpt->min = extract_time(diff);
		cpt->max = extract_time(diff);
	}
	rtt(diff,cpt);
	printf("time=%.2Lf ms\n",extract_time(diff));
	icmp4_packet_set_echo_seq(p,p->icmp_header.un.echo.sequence+1);
    nanosleep(req,NULL);
}

void pi_ng_choix_sleep_et_attente_reception(icmp4_packet * p, connexion * c, compteur * cpt, time_t secondes_sleep, long nanosecondes_sleep, int secondes_rec, int microsecondes_rec)
{
	struct timespec req = {secondes_sleep,nanosecondes_sleep};
	struct timeval tv = {secondes_rec,microsecondes_rec};
	pi_ng(p,c,cpt,&req,&tv);
}

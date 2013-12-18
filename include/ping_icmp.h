#ifndef __PING_ICMP_H
#define __PING_ICMP_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

#include "base.h"
#include "icmp_util.h"
#include "ip_util.h"
#include "address.h"
#include "packet.h"
#include "time_util.h"

typedef struct compteur
{
	unsigned int paquets_transmis;
	unsigned int paquets_recus;
	long double min, max, sum;
} compteur;

typedef struct connexion
{
	int sockfd;
	struct sockaddr_in addr;
} connexion;

typedef struct info_addr
{
	u_int32_t src;
	u_int32_t dest;
	char * addr_dest;
} info_addr;


void init (icmp4_packet * p, connexion * c, info_addr * ia, char * dest, compteur * cpt);

char * char_to_ip (char * dest);

void send_paquet (connexion * c, icmp4_packet * p, compteur * cpt);

void answer_send (connexion * c, compteur * cpt);

void freedom (connexion * c);

void affichage_fin (char* dest, compteur * cpt);

#endif /* __PING_ICMP_H */

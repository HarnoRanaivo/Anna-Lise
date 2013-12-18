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

typedef struct compteur
{
	unsigned int paquets_transmis;
	unsigned int paquets_recus;
} compteur;

typedef struct echo_reply
{
	char * paquet;
	char * buffer;
} echo_reply;

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


void init (icmp4_packet * p, echo_reply * er, connexion * c, info_addr * ia, char * dest, compteur * cpt);

void init_socket (connexion * c, int optval);

char * char_to_ip (char * dest);

void send_paquet (connexion * c, echo_reply * er, icmp4_packet * p, compteur * cpt);

void answer_send (connexion * c, echo_reply * er, struct iphdr* ip_reply, info_addr * ia, compteur * cpt);

void freedom (echo_reply * er, connexion * c);

void affichage_fin (char* dest, compteur * cpt);

#endif /* __PING_ICMP_H */

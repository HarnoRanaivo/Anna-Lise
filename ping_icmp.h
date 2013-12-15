#ifndef __PING_ICMP_H
#define __PING_ICMP_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <linux/ip.h>
#include <linux/icmp.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>

int fin_des_temps = 1;

typedef struct compteur
{
	int paquets_transmis;
	int paquets_recus;
} compteur;

typedef struct paquets
{
	struct iphdr* ip;
	struct icmphdr* icmp;
} paquets;

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
	char src [20];
	char dest [20];
} info_addr;


void init (paquets * p, echo_reply * er, connexion * c, info_addr * ia, char * dest, compteur cpt);

void set_up_IP_paquet (paquets * p, info_addr * ia);

void set_ICMP_ECHO (paquets * p);

char* get_ip_src();

char* char_to_ip (char* addr);

unsigned short in_cksum(unsigned short *addr, int len);

void send_paquet (connexion * c, echo_reply * er, paquets * p, compteur cpt);

void answer_send (connexion * c, echo_reply * er, struct iphdr* ip_reply, info_addr * ia, compteur cpt);

void freedom (paquets * p, echo_reply * er, connexion * c, info_addr * ia);

void handler_int (int signum);

#endif /* __PING_ICMP_H */

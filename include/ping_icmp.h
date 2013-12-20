/**
 * \file ping_icmp.h
 * \brief Implémentation de la fonction Ping. (header)
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
#include <time.h>

#include "base.h"
#include "icmp_util.h"
#include "ip_util.h"
#include "address.h"
#include "packet.h"
#include "time_util.h"

/**
 * \brief Structure pour le décompte de RTT et de paquets transmis/reçus.
 */
typedef struct compteur
{
	unsigned int paquets_transmis;/**<- Nombre de paquets transmis.*/
	unsigned int paquets_recus;/**<- Nombre de paquets reçus.*/
	long double min;/**<- RTT minimal.*/
	long double max;/**<- RTT maximal.*/
	long double sum;/**<- Somme des RTTs.*/
} compteur;

/**
 * \brief Structure de connexion à une adresse.
 */
typedef struct connexion
{
	int sockfd;/**<- Socket de connexion.*/
	struct sockaddr_in addr;/**<- Adresse de connexion.*/
} connexion;

/**
 * \brief Structure d'informations sur le destinataire
 */
typedef struct info_addr
{
	char dom_dest [HOST_NAME_MAX+1];/**<- Domaine de destination.*/
	u_int32_t dest;/**<- Adresse de destination en u_int32_t.*/
	char * addr_dest;/**<- Adresse IP de destination.*/
	char * dest_de_base;/**<- Destination de base entrée dans le main*/
} info_addr;

/**
 * \brief Initialisation des différentes structures et création d'un paquet icmp4_packet.
 * \param[in,out] p Paquet ICMP 4.
 * \param[in,out] c Connexion à la destination.
 * \param[in,out] ia Informations sur la destination.
 * \param[in,out] dest Destination.
 * \param[in,out] cpt Compteur de RTT et nombre des paquets reçus/transmis.
 */
void init_domaine_IPv4 (icmp4_packet * p, connexion * c, info_addr * ia, char * dest, compteur * cpt);

/**
 * \brief Renvoie l'adresse IP d'un domaine.
 * \param[in,out] dest Destination.
 * \return dest de la forme A.B.C.D
 */
char * char_to_ip (char * dest);

/**
 * \brief Envoie d'un paquet ICMP_ECHO REQUEST.
 * \param[in,out] c Connexion à la destination.
 * \param[in,out] p Paquet ICMP 4.
 * \param[in,out] cpt Compteur de RTT et nombre des paquets reçus/transmis.
 */
void send_paquet (connexion * c, icmp4_packet * p, compteur * cpt);

/**
 * \brief Réponse du paquet par une réception d'un paquet ICMP_ECHO REPLY.
 * \param[in,out] c Connexion à la destination.
 * \param[in,out] cpt Compteur de RTT et nombre des paquets reçus/transmis.
 * \param[in,out] tv Temps d'attente de réception.
 */
void answer_send (connexion * c, compteur * cpt, struct timeval * tv);

/**
 * \brief Mise à jour des RTT de la structure compteur.
 * \param time Temps du RTT à comparer.
 * \param[in,out] c Compteur pour l'affiliation de min/max/avg des RTT.
 */
void rtt(struct timeval time, compteur * c);

/**
 * \brief Libération des ressources utilisées et fermeture de la connexion de la socket.
 * \param[in,out] c Connexion à la destination.
 */
void freedom (connexion * c);

/**
 * \brief Affichage des statistiques de la commande Ping traditionelle.
 * \param[in,out] ia Informations sur la destination.
 * \param[in,out] cpt Compteur de RTT et nombre des paquets reçus/transmis.
 * \param total Temps total d'utilisation de la commande Ping.
 */
void affichage_fin (info_addr * ia, compteur * cpt, struct timeval total);

/**
 * \brief Fonction réalisant l'affichage et l'application de Ping.
 * \param[in,out] p Paquet ICMP 4.
 * \param[in,out] c Connexion à la destination.
 * \param[in,out] cpt Compteur de RTT et nombre des paquets reçus/transmis.
 * \param[in,out] req Temps d'attente du sleep.
 * \param[in,out] tv Temps d'attente de la réception.
 */
void pi_ng(icmp4_packet * p, connexion * c, compteur * cpt, struct timespec * req, struct timeval * tv);

/**
 * \brief Fonction réalisant l'affichage et l'application de Ping avec le choix précis des attentes.
 * \param[in,out] p Paquet ICMP 4.
 * \param[in,out] c Connexion à la destination.
 * \param[in,out] cpt Compteur de RTT et nombre des paquets reçus/transmis.
 * \param secondes_sleep secondes d'attente du sleep.
 * \param nanosecondes_sleep nanosecondes d'attente du sleep.
 * \param secondes_rec secondes d'attente de réception.
 * \param nanosecondes_sleep microsecondes d'attente de réception.
 */
void pi_ng_choix_sleep_et_attente_reception(icmp4_packet * p, connexion * c, compteur * cpt, time_t secondes_sleep, long nanosecondes_sleep, int secondes_rec, int microsecondes_rec);

#endif /* __PING_ICMP_H */

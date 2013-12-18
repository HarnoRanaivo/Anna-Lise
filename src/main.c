/**
 * \file main.c
 * \brief Main. (implémentation)
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


int fin_des_temps = 1;

static void handler_int (int signum)
{
	if (signum == SIGINT)
		fin_des_temps=0;
}

/**
 * \brief Nom du programme.
 */
static const char * PROGRAM_NAME = "Anna-Lise";

/**
 * \brief Date.
 */
static const char * DATE = "2013";

/**
 * \brief Numéro de version.
 */
static const char * VERSION_NUMBER = "0.01";

/**
 * \brief Auteurs.
 */
static const char * AUTHORS = "MEYER Jérémy, RAZANAJATO Harenome";

/**
 * \brief URL.
 */
static const char * URL = "https://github.com/remove/Anna-Lise";

/**
 * \brief Afficher la version.
 */
static inline void print_version()
{
    printf("%s, version %s\n"
        "Copyright © %s, %s.\n"
        "<%s>\n",
        PROGRAM_NAME, VERSION_NUMBER, DATE, AUTHORS, URL
    );
}

static void rtt(struct timeval time, compteur * c)
{
	long double temps_aller_retour = extract_time(time);
	c->sum += temps_aller_retour;
	if(temps_aller_retour<c->min)
		c->min = temps_aller_retour;
	if(temps_aller_retour>c->max)
		c->max = temps_aller_retour;
}

/**
 * \brief Main.
 * \param argc Nombre d'arguments de la ligne de commande.
 * \param argv Arguments de la ligne de commande.
 * \retval 0
 */
int main(int argc, char ** argv)
{
    if (argc != 1 && (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0))
        print_version();
    else
    {
		icmp4_packet p;
		connexion c;
		info_addr ia;
		compteur cpt;
		struct sigaction sa;
		struct timeval debut_total, fin_total, diff_total;
		struct timeval debut, fin, diff;
		
		gettimeofday(&debut_total,NULL);
		
		char * dest = argv[1];
    
		sa.sa_handler = handler_int;
		sigfillset(&sa.sa_mask);
		sa.sa_flags = 0;
		sigaction(SIGINT,&sa,NULL);
    
		init(&p,&c,&ia,dest,&cpt);
		create_raw_socket(AF_INET,SOCK_RAW,IPPROTO_ICMP,&c.sockfd);
		
		while(fin_des_temps)
		{
			int avant = cpt.paquets_recus;
			gettimeofday(&debut,NULL);
			send_paquet(&c,&p,&cpt);
			answer_send(&c,&cpt);
			gettimeofday(&fin,NULL);
			diff = diff_timeval(debut,fin);
			if((avant == 0) &&(cpt.paquets_recus == 1))
			{
				cpt.min = extract_time(diff);
				cpt.max = extract_time(diff);
			}
			rtt(diff,&cpt);
			printf("time=%.2Lf\n",extract_time(diff));
			icmp4_packet_set_echo_seq(&p,p.icmp_header.un.echo.sequence+1);
            sleep(1);
		}

		gettimeofday(&fin_total,NULL);
		
		diff_total = diff_timeval(debut_total,fin_total);
		
		affichage_fin(dest,&cpt,diff_total);
	
		freedom(&c);
	
		return 0;
	}
}

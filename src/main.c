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

void handler_int (int signum)
{
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
		echo_reply * er;
		icmp4_packet * p;
		connexion * c;
		info_addr * ia;
		compteur * cpt;
		int optval;
		iphdr * ip_reply;
		struct sigaction sa;
    
		sa.sa_handler = handler_int;
		sigfillset(&sa.sa_mask);
		sa.sa_flags = 0;
		sigaction(SIGINT,&sa,NULL);
    
    
		init(p,er,c,ia,argv[1],cpt);
		init_socket(c,optval);
    
		while(fin_des_temps)
		{
			send_paquet(c,er,p,cpt);
			answer_send(c,er,ip_reply,ia,cpt);
		}

		affichage_fin(argv[1],cpt);
	
		freedom(p,er,c,ia,cpt);
	
		return 0;
	}
}

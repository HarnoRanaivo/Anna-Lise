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
    {
        fin_des_temps=0;
        printf("\n");
    }
}

int main(int argc, char ** argv)
{
    icmp4_packet p;
    connexion c;
    info_addr ia;
    compteur cpt;
    struct sigaction sa;
    struct timeval debut_total, fin_total, diff_total;

    gettimeofday(&debut_total,NULL);

    char * dest = argv[1];

    sa.sa_handler = handler_int;
    sigfillset(&sa.sa_mask);
    sa.sa_flags = 0;
    sigaction(SIGINT,&sa,NULL);

    init_domaine_IPv4(&p,&c,&ia,dest,&cpt);

    while(fin_des_temps)
    {
        pi_ng_choix_sleep_et_attente_reception(&p,&c,&cpt,1,0,1,0);
    }

    gettimeofday(&fin_total,NULL);

    diff_total = diff_timeval(debut_total,fin_total);

    affichage_fin(&ia,&cpt,diff_total);

    freedom(&c);

    return 0;
}

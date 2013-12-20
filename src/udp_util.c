/**
 * \file udp_util.c
 * \brief Utilitaires IP (implémentation)
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

#include "udp_util.h"

/* On n'inclut pas la data dans la checksum...le cas échéant, on la remplit à 0 ! */
int udp_checksum(iphdr * ip_header, udphdr * udp_header)
{
    int success = -1;
    udphdr u = *udp_header;
    u.check = 0;
    fake_iphdr f = (fake_iphdr) { 0, 0, 0, IPPROTO_UDP, ip_header->tot_len };
    fake_udp_packet fake = (fake_udp_packet) { f, u };

    fake.udp_header.check = checksum(&fake, sizeof fake / 2);
    int check = checksum(&fake, sizeof fake / 2);
    if (check == 0)
    {
        udp_header->check = fake.udp_header.check;
        success = 0;
    }

    return success;
}

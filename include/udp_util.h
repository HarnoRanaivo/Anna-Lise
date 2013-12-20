/**
 * \file udp_util.h
 * \brief Utilitaires IP (header)
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

#include <netinet/udp.h>
#include <netinet/ip.h>

#include "base.h"
#include "ip_util.h"
#include "address.h"

/**
 * \brief Header UDP.
 */
typedef struct udphdr udphdr;

typedef struct fake_udp_packet
{
    fake_iphdr ip_header;
    udphdr udp_header;
} fake_udp_packet;

int udp_checksum(iphdr * ip_header, udphdr * udp_header);

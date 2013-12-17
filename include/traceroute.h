/**
 * \file traceroute.h
 * \brief Traceroute (header)
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

#ifndef __TRACEROUTE_H
#define __TRACEROUTE_H

#include "base.h"
#include "address.h"
#include "packet.h"

int receive_icmp_v4(int sockfd, int ttl, struct sockaddr_in * address);

int traceroute_icmp_v4(const char * hostname);

#endif /* __TRACEROUTE_H */

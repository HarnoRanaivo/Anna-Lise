/**
 * \file icmp_util.h
 * \brief Utilitaires ICMP (header)
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

#ifndef __ICMP_UTIL_H
#define __ICMP_UTIL_H

#include <netinet/ip_icmp.h>
#include <netinet/icmp6.h>
#include <sys/types.h>
#include <errno.h>

#include "base.h"
#include "checksum.h"
#include "address.h"

/**
 * \brief ICMP4 Header.
 */
typedef struct icmphdr icmphdr;

/**
 * \brief ICMP6 Header.
 */
typedef struct icmp6_hdr icmp6_hdr;

/**
 * \brief Modifier le type.
 * \param[in,out] header Header ICMPv4 à modifier.
 * \param[in] type Type du header.
 * \retval 0 Pas d'erreur.
 * \retval -1 \p header pointe vers \c NULL.
 * \retval -2 \p type n'est pas un type valide.
 * \retval -3 \p header pointe vers \c NULL et \p type n'est pas un type valide.
 * \relatesalso icmphdr;
 *
 * En cas d'erreur, \c errno sera modifié et contiendra \c EINVAL.
 */
int icmp_set_type(icmphdr * header, u_int8_t type);

/**
 * \brief Modifier le code.
 * \param[in,out] header Header ICMPv4 à modifier.
 * \param[in] code Code.
 * \pre Le type doit avoir été modifié.
 * \retval 0 Pas d'erreur.
 * \retval -1 En cas d'erreur.
 * \retval -2 \p header n'est pas du type \c ICMP_ECHO
 * \warning Les vérifications du code ne sont faites que pour certains types...
 * \relatesalso icmphdr
 *
 * En cas d'erreur, \c errno sera modifié et contiendra \c EINVAL.
 */
int icmp_set_code(icmphdr * header, u_int8_t code);

/**
 * \brief Modifier les infos pour un ICMP_ECHO.
 * \param[in,out] header Header ICMPv4 à modifier.
 * \param[in] identifier ID.
 * \param[in] sequence Sequence.
 * \pre Le type doit avoir été modifié.
 * \retval 0 Pas d'erreur.
 * \retval -1 \p header pointe vers \c NULL.
 * \retval -2 \p header n'est pas du type \c ICMP_ECHO
 * \warning Les vérifications du code ne sont faites que pour certains types...
 * \relatesalso icmphdr
 *
 * En cas d'erreur, \c errno sera modifié et contiendra \c EINVAL.
 */
int icmp_set_echo(icmphdr * header, u_int16_t identifier, u_int16_t sequence);

/**
 * \brief Checksum.
 * \param[in,out] header Header ICMPv4.
 * \retval 0 Pas d'erreur.
 * \retval -1 \p header pointe vers \c NULL.
 * \retval -2 La checksum ne s'est pas bien déroulée.
 * \relatesalso icmphdr
 *
 * Si \p header pointe vers \c NULL, \c errno sera modifé à \c EINVAL. Si la checksum ne s'est pas déroulée correctement, \c errno contiendra \c ECANCELED.
 */
int icmp_checksum(icmphdr * header);

/**
 * \brief Afficher un header.
 * \param header Header.
 */
void icmp_print(const icmphdr * header);

#endif /* __ICMP_UTIL_H */

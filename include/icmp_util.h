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

/**
 * \brief Modifier le type.
 * \param header Header ICMPv4 à modifier.
 * \param type Type du header.
 * \retval 0 Pas d'erreur.
 * \retval -1 \p header pointe vers \c NULL.
 * \retval -2 \p type n'est pas un type valide.
 * \retval -3 \p header pointe vers \c NULL et \p type n'est pas un type valide.
 *
 * En cas d'erreur, \c errno sera modifié et contiendra \c EINVAL.
 */
int icmp_set_type(struct icmphdr * header, u_int8_t type);

/**
 * \brief Modifier le code.
 * \param header Header ICMPv4 à modifier.
 * \param type Type du header.
 * \pre Le type doit avoir été modifié.
 * \retval 0 Pas d'erreur.
 * \retval -1 En cas d'erreur.
 * \retval -2 \p header n'est pas du type \c ICMP_ECHO
 * \warning Les vérifications du code ne sont faites que pour certains types...
 *
 * Erreurs :
 * - \p header pointe vers \c NULL.
 * - \p code n'est pas un code valide.
 * Dans les deux cas, \c errno sera modifié et contiendra \c EINVAL.
 */
int icmp_set_code(struct icmphdr * header, u_int8_t code);

/**
 * \brief Modifier le code.
 * \param header Header ICMPv4 à modifier.
 * \param type Type du header.
 * \pre Le type doit avoir été modifié.
 * \retval 0 Pas d'erreur.
 * \retval -1 \p header pointe vers \c NULL.
 * \retval -2 \p header n'est pas du type \c ICMP_ECHO
 * \warning Les vérifications du code ne sont faites que pour certains types...
 *
 * En cas d'erreur, \c errno sera modifié et contiendra \c EINVAL.
 */
int icmp_set_echo(struct icmphdr * header, u_int16_t identifier, u_int16_t sequence);

#endif /* __ICMP_UTIL_H */

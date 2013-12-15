/**
 * \file checksum.h
 * \brief Internet Checksum. (header)
 * \author MEYER Jérémy
 * \author RAZANAJATO Harenome
 * \date 2013
 * \copyright WTFPL version 2
 */ /* This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar. See
 * http://www.wtfpl.net/ for more details.
 */

#ifndef __CHECKSUM_H
#define __CHECKSUM_H

#include <stdlib.h>
#include <stdio.h>

/**
 * \brief Calculer l'Internet Checksum (RFC 1071).
 * \param address Addresse.
 * \param length Longueur.
 * \return Checksum.
 */
unsigned short checksum(void * address, int length);

#endif /* __CHECKSUM_H */

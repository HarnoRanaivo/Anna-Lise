/**
 * \file checksum.c
 * \brief Internet Checksum. (implémentation)
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

#include "checksum.h"

/* Algorithme custom à partir des explications de Wikipedia.
 * https://en.wikipedia.org/wiki/IPv4_header_checksum
 */
unsigned short checksum(void * address, int length)
{
    int sum = 0;
    unsigned short * last_word = (unsigned short *)address + length;

    for (const unsigned short * word = address; word != last_word; word++)
        sum += *word;

    int carry = (sum >> 16);
    sum = sum & 0xffff;
    sum += carry;
    sum = ~sum;

    return sum;
}


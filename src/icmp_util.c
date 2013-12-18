/**
 * \file icmp_util.h
 * \brief Utilitaires ICMP (implémentation)
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

#include "icmp_util.h"

/* 1, 2, et 7 sont réservés.
 * 9 et 10 n'ont pas de macro dans "netinet/ip_icmp.h".
 * De toutes façons on n'utilisera que ICMP_ECHOREPLY...normalement ?
 */
static const int INVALID_ICMP_V4_TYPES[] = { 1, 2, 6, 7, 9, 10, -1 };

/*
 * Vérifier la validité d'un header.
 */
static inline int check_header(struct icmphdr * header, u_int8_t type)
{
    int success = 0;
    success = check_pointer(header);
    if (success == 0 && header->type != type)
    {
        errno = EINVAL;
        success = -2;
    }
    return success;
}

/*
 * Vérifier la validité d'un type.
 */
static inline int check_icmp_type(u_int8_t type)
{
    int success = 0;
    if (type > NR_ICMP_TYPES || uint_in_array(INVALID_ICMP_V4_TYPES, type) != -1)
    {
        errno = EINVAL;
        success = -2;
    }
    return success;
}

int icmp_set_type(struct icmphdr * header, u_int8_t type)
{
    int success = 0;

    success += check_pointer(header);
    success += check_icmp_type(type);

    if (success == 0)
        header->type = type;

    return success;
}

int icmp_set_code(struct icmphdr * header, u_int8_t code)
{
    int success = 0;

    success = check_pointer(header);
    if (success == 0 && header->type == ICMP_ECHO)
    {
        if (code != 0)
            code = 0;
        header->code = code;
    }

    return success;
}

int icmp_set_echo(struct icmphdr * header, u_int16_t identifier, u_int16_t sequence)
{
    int success = 0;

    success = check_header(header, ICMP_ECHO);
    if (success == 0)
    {
        header->un.echo.id = identifier;
        header->un.echo.sequence = sequence;
    }

    return success;
}

int icmp_checksum(icmphdr * header)
{
    int success = check_pointer(header);

    if (success == 0)
    {
        u_int16_t old_sum = header->checksum;
        header->checksum = 0;
        header->checksum = checksum(header, (sizeof *header) / 2);
        u_int16_t check = checksum(header, (sizeof *header) / 2);
        if (check != 0)
        {
            header->checksum = old_sum;
            errno = ECANCELED;
            success = -2;
        }
    }

    return success;
}

void icmp_print(const icmphdr * header)
{
    int ok = check_pointer(header);
    if (ok == 0)
    {
        printf("ICMP type: %d\n", header->type);
        printf("ICMP code: %d\n", header->code);
        printf("ICMP checksum: %d\n", header->checksum);
        if (header->type == ICMP_ECHO)
        {
            printf("ICMP id: %d\n", header->un.echo.id);
            printf("ICMP sequence: %d\n", header->un.echo.sequence);
        }

    }
}

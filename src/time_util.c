/**
 * \file time_util.c
 * \brief Utilitaires temps (implémentation)
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

#include "time_util.h"

/* Voir:
 * https://www.gnu.org/software/libc/manual/html_node/Elapsed-Time.html
 */
struct timeval diff_timeval(struct timeval start, struct timeval end)
{
    static const long int factor = 1000000;
    if (end.tv_usec < start.tv_usec)
    {
        int seconds = (start.tv_usec - end.tv_usec) / factor + 1;
        start.tv_usec -= factor * seconds;
        start.tv_sec += seconds;
    }
    if (end.tv_usec - start.tv_usec > factor)
    {
        int seconds = (end.tv_usec - start.tv_usec) / factor;
        start.tv_usec += factor * seconds;
        start.tv_sec -= seconds;
    }
    struct timeval result;
    result.tv_sec = end.tv_sec - start.tv_sec;
    result.tv_usec = end.tv_usec - start.tv_usec;

    return result;
}

long double extract_time(struct timeval time)
{
    return (time.tv_sec * 1000.0 + time.tv_usec / 1000.0);
}

void print_timeval(struct timeval time)
{
    long double ms = extract_time(time);
    printf("%.3Lf ms", ms);
}

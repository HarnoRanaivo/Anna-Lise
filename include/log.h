/**
 * \file log.h
 * \brief Utilitaires pour logger. (header)
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

#ifndef __LOG_H
#define __LOG_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

/**
 * \brief Fichier de log.
 */
FILE * LOG_FILE;

/**
 * \brief Logger l'output.
 */
#define log_output(args) \
    printf((args)); \
    fprintf(LOG_FILE, (args))

/**
 * \brief Initialiser le fichier de log.
 */
int init_log_file(void);

#endif /* __LOG_H */

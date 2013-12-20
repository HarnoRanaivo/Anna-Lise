/**
 * \file log.c
 * \brief Utilitaires pour logger. (implémentation)
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

#include "log.h"

int init_log_file(void)
{
    int success = -1;
    FILE * file;
    char path[256];

    int pid = getpid();
    if (snprintf(path, 256, "log_%d.txt", pid) > 0)
    {
        file = fopen(path, "w+");
        if (file != NULL)
        {
            LOG_FILE = file;
            success = 0;
        }
    }

    return success;
}

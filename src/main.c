/**
 * \file main.c
 * \brief Main. (implémentation)
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

#include <stdio.h>
#include <stdlib.h>
#include <sysexits.h>
#include <string.h>

#include "constants.h"
#include "base.h"
#include "anna.h"

/**
 * \brief Afficher la version.
 */
static inline void print_version()
{
    printf("%s, version %s\n"
        "Copyright © %s, %s.\n"
        "<%s>\n",
        PROGRAM_NAME, VERSION_NUMBER, DATE, AUTHORS, URL
    );
}

static inline int find_word(const char * word, int argc, char ** argv)
{
    int success = -1;

    for (int i = 0; success == -1 && i < argc; i++)
        if (strcmp(word, argv[i]) == 0)
            success = 0;

    return success;
}

/**
 * \brief Main.
 * \param argc Nombre d'arguments de la ligne de commande.
 * \param argv Arguments de la ligne de commande.
 */
int main(int argc, char ** argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <hostname | ip address>\n", argv[0]);
        exit(EX_USAGE);
    }

    if (find_word("-v", argc, argv) == 0 || find_word("--version", argc, argv) == 0)
    {
        print_version();
        return 0;
    }

    anna(argv[1]);

    return 0;
}

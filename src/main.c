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
#include "base.h"

/**
 * \brief Nom du programme.
 */
static const char * PROGRAM_NAME = "Anna-Lise";

/**
 * \brief Date.
 */
static const char * DATE = "2013";

/**
 * \brief Numéro de version.
 */
static const char * VERSION_NUMBER = "0.01";

/**
 * \brief Auteurs.
 */
static const char * AUTHORS = "MEYER Jérémy, RAZANAJATO Harenome";

/**
 * \brief URL.
 */
static const char * URL = "https://github.com/remove/Anna-Lise";

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

/**
 * \brief Main.
 * \param argc Nombre d'arguments de la ligne de commande.
 * \param argv Arguments de la ligne de commande.
 * \retval 0
 */
int main(int argc, char ** argv)
{
    if (argc != 1 && (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0))
        print_version();
    else
        printf("This program doesn't do anything yet. (Sorry)\n");

    return 0;
}

/**
 * \file base.h
 * \brief Fonctions et inclusions de base. (header)
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

#ifndef __BASE_H
#define __BASE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sysexits.h>
#include <errno.h>
#include <string.h>

/**
 * \brief Afficher un message d'erreur, puis quitter.
 * \param message Message d'erreur.
 * \param exit_code Code d'erreur.
 */
static inline void pq_error(const char * message, int exit_code)
{
    perror(message);
    exit(exit_code);
}

/**
 * \brief Allouer une zone mémoire de taille \p n * \p size.
 * \param n Facteur.
 * \param size Taille de base.
 * \retval pointeur vers la zone mémoire allouée.
 * \retval NULL en cas d'erreur ou si \p size \c == \c 0.
 *
 * Cette fonction ne vérifie pas le bon déroulement de l'allocation, et se
 * comporte de la même façon que la fonction malloc de stdlib.h.
 */
static inline void * malloc_n(size_t n, size_t size)
{
    return malloc(n * size);
}

/**
 * \brief Allouer une zone mémoire, et quitter en cas d'erreur.
 * \param size Taille de la zone mémoire souhaitée.
 * \retval pointeur vers la zone mémoire allouée.
 * \retval NULL si \p size \c == \c 0.
 *
 * En cas d'erreur d'allocation, cette fonction cause la fin du programme.
 * Comme le fait malloc, si \p size est égal à 0, cette fonction retourne \c NULL.
 */
static inline void * q_malloc(size_t size)
{
    void * memory = malloc(size);
    if (memory == NULL && size != 0)
        pq_error("malloc", EX_OSERR);
    return memory;
}

/**
 * \brief Allouer une zone mémoire de taille \p n * \p size, et quitter en cas d'erreur.
 * \param n Nombre d'éléments.
 * \param size Taille de la zone mémoire souhaitée.
 * \retval pointeur vers la zone mémoire allouée.
 * \retval NULL si \p size \c == \c 0 ou \p n \c == \c 0.
 *
 * En cas d'erreur d'allocation, cette fonction cause la fin du programme.
 * Comme le fait malloc, si \p n ou \p size sont égaux à 0, cette fonction retourne \c NULL.
 */
static inline void * q_malloc_n(size_t n, size_t size)
{
    void * memory = malloc_n(n, size);
    if (memory == NULL && n != 0 && size != 0)
        pq_error("malloc", EX_OSERR);
    return memory;
}

/**
 * \brief Allouer et initialiser à \c 0 une zone mémoire de taille \p n * \p size, et quitter en cas d'erreur.
 * \param size Taille de la zone mémoire souhaitée.
 * \retval pointeur vers la zone mémoire allouée.
 * \retval NULL si \p size \c == \c 0 ou \p n \c == \c 0.
 *
 * En cas d'erreur d'allocation, cette fonction cause la fin du programme.
 * Comme le fait calloc, si \p n ou \p size sont égaux à 0, cette fonction retourne \c NULL.
 */
static inline void * q_calloc(size_t n, size_t size)
{
    void * memory = calloc(n, size);
    if (memory == NULL && n != 0 && size != 0)
        pq_error("calloc", EX_OSERR);
    return memory;
}

#endif /* __BASE_H */

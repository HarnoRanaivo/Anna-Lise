/**
 * \file anna.h
 * \brief Anna. (implémentation)
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

#ifndef __ANNA_H
#define __ANNA_H

#include <signal.h>
#include <time.h>

#include "base.h"
#include "address.h"
#include "traceroute.h"

int anna(const char * hostname);

#endif /* __ANNA_H */

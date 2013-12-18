#ifndef __MANUAL_TESTS_H
#define __MANUAL_TESTS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

static inline void MT_print_char_n(char c, int n)
{
    for (int i = 0; i < n; i++)
        printf("%c", c);
}

static inline void MT_print_and_underline(const char * word, char underline_char)
{
    printf("%s\n", word);
    MT_print_char_n(underline_char, strlen(word));
    printf("\n");
}

static inline void MT_title(const char * title)
{
    MT_print_and_underline(title, '=');
}

static inline void MT_section(const char * section)
{
    printf("\n");
    MT_print_and_underline(section, '-');
}

#endif /* __MANUAL_TESTS_H */

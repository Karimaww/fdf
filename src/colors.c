#include "../include/fdf.h"

static int    htoi(char c)
{
    if (c >= '0' && c <= '9')
        return (c - '0');
    return (10 + c - 'A');
}

int    hex_to_trgb(char *value)
{
    int            r;
    int            g;
    int            b;
    size_t        len;

    len = ft_strlen(value);
    r = 0;
    g = 0;
    if (len == 6)
    {
        r = 16 * htoi(ft_toupper(value[0])) + htoi(ft_toupper(value[1]));
        value += 2;
    }
    if (len >= 4)
    {
        g = 16 * htoi(ft_toupper(value[0])) + htoi(ft_toupper(value[1]));
        value += 2;
    }
    b = 16 * htoi(ft_toupper(value[0])) + htoi(ft_toupper(value[1]));
    return (0 << 24 | r << 16 | g << 8 | b);
}
#ifndef EVENTS_H
# define EVENTS_H
# include "fdf.h"

enum {
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

// EVENTS
# define KEYPRESS 2
# define KEYRELEASE 3
# define BUTTONPRESS 4
# define BUTTONRELEASE 5

// EVENT MASKS
# define MKEYPRESS (1L<<0)
# define MKEYRELEASE (1L<<1)
# define MBUTTONPRESS (1L<<2)
# define MBUTTONRELEASE (1L<<3)
#endif
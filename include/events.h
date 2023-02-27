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

// KEYCODES ON MAC
#ifdef __APPLE__
# define ESC 53
# define SPACE 49
#else
# define ESC 65307
# define SPACE 32
# define ARROW_UP 65362
# define ARROW_DOWN 65364
# define ARROW_LEFT 65361
# define ARROW_RIGHT 65363
# define LEFT 97
# define RIGHT 100
# define DOWN 115
# define UP 119
# define HUP 49
# define HDOWN 50
#endif
#endif
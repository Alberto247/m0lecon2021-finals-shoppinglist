#ifndef THINGS
#define THINGS

#include <string.h>
#define clrscr() printf("\e[1;1H\e[2J")
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct _item{
  u_char id;
  u_char quantity;
} item;



#endif

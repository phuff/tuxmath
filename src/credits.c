/*
  credits.c
 
  For TuxMath
  Contains the text of the credits display, as well
  as the function which displays the credits in the game window.

  by Bill Kendrick
  bill@newbreedsoftware.com
  http://www.newbreedsoftware.com/


  Part of "Tux4Kids" Project
  http://www.tux4kids.org/
  
  August 26, 2001 - March 7, 2005
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <SDL.h>

#include "tuxmath.h"
#include "options.h"
#include "fileops.h"
#include "setup.h"


char * credit_text[] = {
  "-TUX, OF MATH COMMAND",  /* '-' at beginning makes highlighted: */
  "COPYRIGHT 2001-2006",
  "",
  "PART OF THE 'TUX4KIDS' PROJECT",
  "",
  "-DESIGNED BY",
  "SAM 'CRISWELL' HART",
  "",
  "-LEAD PROGRAMMERS",
  "BILL KENDRICK,",
  "NEW BREED SOFTWARE",
  "DAVID BRUCE",
  "",
  "-ADDITIONAL CODE",
  "GLEN DITCHFIELD",
  "MICHAEL BEHRISCH",
  "DONNY VISZNEKI",
  "YVES COMBE",
  "DAVID YODER",
  "TIM HOLY",
  "",
  "-LEAD ARTIST",
  "SAM HART",
  "",
  "-ADDITIONAL ART",
  "BILL KENDRICK",
  "",
  "-SOUND EFFECTS",
  "TBA",
  "",
  "-MUSIC",
  "BEYOND THE HORIZON",
  "BY MYSTRA OF STONE ARTS, 1994",
  "",
  "CCCP MAIN",
  "BY GROO OF CNCD, 1994",
  "",
  "SOFT BRILLIANCE",
  "TJOPPBASS, 1994",
  "",
  "-PACKAGERS",
  "JESSE ANDREWS",
  "HOLGER LEVSEN",
  "",
  "-'TUX' THE PENGUIN CREATED BY",
  "LARRY EWING",
  "",
  "-TESTERS",
  "PETE SALZMAN",
  "ST. CATHERINE ELEM., CINCINNATI, OH",
  "WESTWOOD ELEMENTARY, CINCINNATI, OH",
  "LAURA BRUCE",
  "ROOSEVELT ELEMENTARY, TAMPA, FL",
  "KENDRA SWANSON AND LINNEA HOLY",
  "OLD BONHOMME ELEMENTARY,",
  "ST. LOUIS, MO",
  "",
  "",
  "-WEBSITE",
  "TUX4KIDS.COM",
  "", /* The following blanks cause the screen to scroll to complete blank: */
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  "",
  NULL
};


/* Some simple pixel-based characters we can blit quickly: */

char chars[39][5][5] = {
  {".###.",
   "#..##",
   "#.#.#",
   "##..#",
   ".###."},

  {"..#..",
   ".##..",
   "..#..",
   "..#..",
   ".###."},

  {".###.",
   "....#",
   "..##.",
   ".#...",
   "#####"},

  {".###.",
   "....#",
   "..##.",
   "....#",
   ".###."},

  {"...#.",
   "..##.",
   ".#.#.",
   "#####",
   "...#."},

  {"#####",
   "#....",
   "####.",
   "....#",
   "####."},

  {".###.",
   "#....",
   "####.",
   "#...#",
   ".###."},

  {"#####",
   "....#",
   "...#.",
   "..#..",
   ".#..."},

  {".###.",
   "#...#",
   ".###.",
   "#...#",
   ".###."},

  {".###.",
   "#...#",
   ".####",
   "....#",
   ".###."},

  {".###.",
   "#...#",
   "#####",
   "#...#",
   "#...#"},

  {"####.",
   "#...#",
   "####.",
   "#...#",
   "####."},
  
  {".###.",
   "#....",
   "#....",
   "#....",
   ".###."},
  
  {"####.",
   "#...#",
   "#...#",
   "#...#",
   "####."},
  
  {"#####",
   "#....",
   "###..",
   "#....",
   "#####"},
  
  {"#####",
   "#....",
   "###..",
   "#....",
   "#...."},
  
  {".###.",
   "#....",
   "#.###",
   "#...#",
   ".###."},
  
  {"#...#",
   "#...#",
   "#####",
   "#...#",
   "#...#"},
  
  {".###.",
   "..#..",
   "..#..",
   "..#..",
   ".###."},
  
  {"....#",
   "....#",
   "....#",
   "#...#",
   ".###."},
  
  {"#..#.",
   "#.#..",
   "##...",
   "#.#..",
   "#..#."},
  
  {"#....",
   "#....",
   "#....",
   "#....",
   "#####"},
  
  {"#...#",
   "##.##",
   "#.#.#",
   "#...#",
   "#...#"},
  
  {"#...#",
   "##..#",
   "#.#.#",
   "#..##",
   "#...#"},
  
  {".###.",
   "#...#",
   "#...#",
   "#...#",
   ".###."},
  
  {"####.",
   "#...#",
   "####.",
   "#....",
   "#...."},
  
  {".###.",
   "#...#",
   "#.#.#",
   "#..#.",
   ".##.#"},
  
  {"####.",
   "#...#",
   "####.",
   "#...#",
   "#...#"},
  
  {".###.",
   "#....",
   ".###.",
   "....#",
   ".###."},
  
  {"#####",
   "..#..",
   "..#..",
   "..#..",
   "..#.."},
  
  {"#...#",
   "#...#",
   "#...#",
   "#...#",
   ".###."},
  
  {"#...#",
   "#...#",
   ".#.#.",
   ".#.#.",
   "..#.."},
  
  {"#...#",
   "#...#",
   "#.#.#",
   "##.##",
   "#...#"},
  
  {"#...#",
   ".#.#.",
   "..#..",
   ".#.#.",
   "#...#"},

  {"#...#",
   ".#.#.",
   "..#..",
   "..#..",
   "..#.."},
  
  {"#####",
   "...#.",
   "..#..",
   ".#...",
   "#####"},
  
  {".....",
   ".....",
   ".....",
   "..#..",
   ".#..."},

  {".....",
   ".....",
   ".....",
   "..#..",
   "..#.."},
  
  {"..#..",
   "..#..",
   ".....",
   ".....",
   "....."}
};


void draw_text(char * str, int offset);


int line;


int credits(void)
{
  int done, quit, scroll;
  SDL_Rect src, dest;
  SDL_Event event;
  Uint32 last_time, now_time;
  SDLKey key;
  
  
  /* Clear window: */
  
  SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0));
  
  
  /* Draw title: */
  
  dest.x = (screen->w - images[IMG_TITLE]->w) / 2;
  dest.y = 0;
  dest.w = images[IMG_TITLE]->w;
  dest.h = images[IMG_TITLE]->h;
  
  SDL_BlitSurface(images[IMG_TITLE], NULL, screen, &dest);
  
  
  /* --- MAIN OPTIONS SCREEN LOOP: --- */
  
  done = 0;
  quit = 0;
  scroll = 0;
  line = 0;
  
  do
    {
      last_time = SDL_GetTicks();
      
      
      /* Handle any incoming events: */
      while (SDL_PollEvent(&event) > 0)
	{
	  if (event.type == SDL_QUIT)
	    {
	      /* Window close event - quit! */
	      
	      quit = 1;
	      done = 1;
	    }
	  else if (event.type == SDL_KEYDOWN)
	    {
	      key = event.key.keysym.sym;
	      
	      if (key == SDLK_ESCAPE)
		{
		  /* Escape key - quit! */
		  
		  done = 1;
		}
	    }
	  else if (event.type == SDL_MOUSEBUTTONDOWN)
	    {
              done = 1;
	    }
	}

      
      /* Scroll: */

      src.x = 0;
      src.y = (images[IMG_TITLE]->h) + 2;
      src.w = screen->w;
      src.h = screen->h - (images[IMG_TITLE]->h);
      
      dest.x = 0;
      dest.y = (images[IMG_TITLE]->h);
      dest.w = src.w;
      dest.h = src.h;
      
      SDL_BlitSurface(screen, &src, screen, &dest);

      dest.x = 0;
      dest.y = (screen->h) - 2;
      dest.w = screen->w;
      dest.h = 2;

      SDL_FillRect(screen, &dest, SDL_MapRGB(screen->format, 0, 0, 0));
      
      
      scroll++;
      
      draw_text(credit_text[line], scroll);
      

      if (scroll >= 9)
	{
	  scroll = 0;
	  line++;
	  
	  if (credit_text[line] == NULL)
	    done = 1;
	}
      
      
      SDL_Flip(screen);
      
      
      /* Pause (keep frame-rate event) */
      
      now_time = SDL_GetTicks();
      if (now_time < last_time + (1000 / 20))
	{
	  SDL_Delay(last_time + (1000 / 20) - now_time);
	}
    }
  while (!done);
  
  
  /* Return the chosen command: */
  
  return quit;
}


void draw_text(char * str, int offset)
{
  int i, c, x, y, cur_x, start, hilite;
  SDL_Rect dest;
  Uint8 r, g, b;


  if (str[0] == '-')
  {
    start = 1;
    hilite = 1;
  }
  else
  {
    start = 0;
    hilite = 0;
  }
  
  
  cur_x = (screen->w - ((strlen(str) - start) * 18)) / 2;
  
  for (i = start; i < strlen(str); i++)
    {
      c = -1;
      
      if (str[i] >= '0' && str[i] <= '9')
	c = str[i] - '0';
      else if (str[i] >= 'A' && str[i] <= 'Z')
	c = str[i] - 'A' + 10;
      else if (str[i] == ',')
	c = 36;
      else if (str[i] == '.')
	c = 37;
      else if (str[i] == '\'')
	c = 38;
      
      
      if (c != -1)
	{
	  for (y = 0; y < 5; y++)
	    {
	      if (hilite == 0)
	      {
	        r = 255 - ((line * y) % 256);
	        g = 255 / (y + 2);
	        b = (line * line * 2) % 256;
	      }
	      else
	      {
		r = 128;
		g = 192;
		b = 255 - (y * 40);
	      }
	      
	      for (x = 0; x < 5; x++)
		{
		  if (chars[c][y][x] == '#')
		    {
		      dest.x = cur_x + (x * 3);
		      dest.y = ((screen->h - (5 * 3)) + (y * 3) +
				(18 - offset * 2));
		      dest.w = 3;
		      dest.h = 3;
		      
		      SDL_FillRect(screen, &dest,
				   SDL_MapRGB(screen->format, r, g, b));
		    }
		}
	    }
	}
      
      
      /* Move virtual cursor: */
      
      cur_x = cur_x + 18;
    }
}

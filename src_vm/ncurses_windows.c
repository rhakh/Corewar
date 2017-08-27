#include "vm.h"


WINDOW *create_newwin(int height, int width, int starty, int startx)
{	WINDOW *local_win;
	char 	border;

	border = 0;
	local_win = newwin(height, width, starty, startx);
	box(local_win, border , border);		/* 0, 0 gives default characters
					 * for the vertical and horizontal
					 * lines			*/
	wrefresh(local_win);		/* Show that box 		*/

	return local_win;
}
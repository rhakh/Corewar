#include "vm.h"

WINDOW		*create_memory_win(void)
{
	WINDOW *memory_win;

	refresh();
	memory_win = create_newwin(MEM_SIZE / 64 + 2, 128 + 100 + 2, 2, 0);
//	wborder(memory_win, '.', '.', '.', '.', '.', '.', '.', '.');
	return memory_win;
}

void		ft_init_ncurses(void)
{
	initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	start_color();
	init_color(COLOR_WHITE, 220, 220, 220);
	init_pair(0, COLOR_YELLOW, COLOR_BLACK);
	init_pair(1, COLOR_BLUE, COLOR_BLACK);
	init_pair(2, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(3, COLOR_CYAN, COLOR_BLACK);
	init_pair(4, COLOR_RED, COLOR_BLACK);
	init_pair(5, COLOR_GREEN, COLOR_BLACK);
	init_pair(6, COLOR_YELLOW, COLOR_BLACK);
	init_pair(7, COLOR_BLACK, COLOR_BLUE);
	init_pair(8, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(9, COLOR_BLACK, COLOR_CYAN);
	init_pair(10, COLOR_BLACK, COLOR_RED);
	init_pair(11, COLOR_BLACK, COLOR_GREEN);
	init_pair(12, COLOR_WHITE, COLOR_BLACK);
	init_pair(13, COLOR_BLACK, COLOR_GREEN);
	init_pair(14, COLOR_GREEN, COLOR_BLACK);
//	curs_set(FALSE);
}

void		display_memory(t_data *data, WINDOW *win)
{
	int 	i;

	wmove(win, 1, 1);
//	wprintw(win, "hello");
	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % 64 == 0){
			wprintw(win, "42\n");
		}
//		wprintw(win, "%0.2hhx ", data->map[i]);
		i++;
	}
	wrefresh(win);
}

void		ft_display_arena(t_data *data) {
	ft_init_ncurses();
	printw("CORE_WAR\n");
	printw("Memory dump:\n");
	refresh();
	display_memory(data, create_memory_win());
	getch();
	endwin();
}
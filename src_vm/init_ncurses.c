#include "vm.h"

WINDOW		*create_memory_win(void)
{
	WINDOW *memory_win;

	refresh();
	memory_win = create_newwin(ft_sqrt(MEM_SIZE) + 2, ft_sqrt(MEM_SIZE) * 2  + ft_sqrt(MEM_SIZE) + 2, 2, 0);
//	wborder(memory_win, '.', '.', '.', '.', '.', '.', '.', '.');
	return memory_win;
}

WINDOW		*create_stats_win(void)
{
	WINDOW *stats_win;

	refresh();
	stats_win = create_newwin(ft_sqrt(MEM_SIZE) + 2, 70, 2, ft_sqrt(MEM_SIZE) * 2  + ft_sqrt(MEM_SIZE) + 2);
	wbkgd(stats_win, COLOR_PAIR(9));
//	wborder(memory_win, '.', '.', '.', '.', '.', '.', '.', '.');
	wrefresh(stats_win);
	return stats_win;
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
	int 	x;
	int 	y;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (i % ft_sqrt(MEM_SIZE) == 0){
			getyx(win, y, x);
			wmove(win, y + 1, 1);
		}
		wattron(win, COLOR_PAIR(i % 14));
		wprintw(win, "%0.2hhx ", data->map[i]);
		wattroff(win, COLOR_PAIR(i % 2));
		i++;
	}
	wrefresh(win);
}

void		ft_display_arena(t_data *data) {
	WINDOW *memory_win;
	ft_init_ncurses();
	attron(A_BOLD);
	printw("CORE_WAR\n");
	printw("Memory dump:\n");
	attroff(A_BOLD);
	refresh();
	memory_win = create_memory_win();
	display_memory(data, memory_win);
	create_stats_win();
	move_to_byte(memory_win, 5);
	move_to_byte(memory_win, 42);
	move_to_byte(memory_win, 0);
	move_to_byte(memory_win, 64);
	move_to_byte(memory_win, 65);
	move_to_byte(memory_win, 63);
	move_to_byte(memory_win, 69);
	getch();
	endwin();
}
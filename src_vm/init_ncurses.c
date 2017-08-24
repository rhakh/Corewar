#include "vm.h"

int 			send_to_ncurses(int start, int len, t_bot *bot, t_data *data) {
	//move_to_byte();
}

void		ft_init_ncurses(void)
{
	initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	// scrollok( stdscr, true ); // skroll page
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
	curs_set(FALSE);
}

void		ft_display_arena(t_data *data)
{
	WINDOW *memory_win;
	WINDOW *stats_win;
	WINDOW *debug_win;

	ft_init_ncurses();
	attron(A_BOLD);
	printw("CORE_WAR\nMemory dump: %5d %240s\n", 55555, "Type q to exit");
	attroff(A_BOLD);
	refresh();

	memory_win = create_memory_win();
	display_memory(data, memory_win);
	stats_win = create_stats_win();
	display_stats(data, stats_win);
	debug_win = create_debug_win();
	display_debug(data, debug_win);

	data->memory_win = memory_win;
	data->stats_win = stats_win;
	data->debug_win = debug_win;
}
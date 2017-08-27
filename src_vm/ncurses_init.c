#include "vm.h"

void init_ncurses(void)
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
	init_pair(6, COLOR_WHITE, COLOR_BLUE);
	init_pair(7, COLOR_WHITE, COLOR_MAGENTA);
	init_pair(8, COLOR_WHITE, COLOR_CYAN);
	init_pair(9, COLOR_WHITE, COLOR_RED);
	init_pair(10, COLOR_BLACK, COLOR_RED);
	init_pair(11, COLOR_BLACK, COLOR_BLACK);
	init_pair(12, COLOR_WHITE, COLOR_BLACK);
	init_pair(13, COLOR_GREEN, COLOR_GREEN);
	init_pair(14, COLOR_GREEN, COLOR_BLACK);
	curs_set(FALSE);
}

void		nc_display_arena(t_data *data)
{
	WINDOW *memory_win;
	WINDOW *stats_win;
	WINDOW *debug_win;

	init_ncurses();
	attron(A_BOLD);
	ncurses_print_header();
	attroff(A_BOLD);
	refresh();

	data->one_command_mode = 1;
	data->ncurses_timeout = 64;
	memory_win = create_memory_win();
	display_memory(data, memory_win);

	data->pause = 1;
	stats_win = create_stats_win();
	display_stats(data, stats_win);

	debug_win = create_debug_win();
	display_debug(data, debug_win);

	data->memory_win = memory_win;
	data->stats_win = stats_win;
	data->debug_win = debug_win;
}

void		nc_terminate(t_data *data)
{
	t_bot	*bot;
	int 	i;
	int  	nb;
	int 	l_live_bigest;
	t_linked_list   *list;

	i = 0;
	l_live_bigest = data->bots_last_live[0];
	nb = 1;
	while (++i <= data->bots_count)
		if (data->bots_last_live[i] > l_live_bigest)
		{
			l_live_bigest = data->bots_last_live[i];
			nb = i;
		}
	list = data->bots;
	bot = (t_bot *)list->data;
	while (nb != bot->number)
	{
		list = list->next;
		list ? bot = list->data : 0;
		!list ? bot = NULL : 0;
	}
	display_winner(data, bot);
	while (getch() != 'q')
		;
	endwin();
}

void		ncurses_print_header(void)
{
	printw("%100s" ,"COREWAR");
	printw("%120s", "Type space - ");
	attron(COLOR_PAIR(4));
	printw("Pause ");
	attroff(COLOR_PAIR(4));
	printw("\\ ");
	attron(COLOR_PAIR(5));
	printw("Play\n");
	attroff(COLOR_PAIR(5));
	printw("%s", "Made by ");
	attron(COLOR_PAIR(1));
	printw("rhakh ");
	attroff(COLOR_PAIR(1));
	attron(COLOR_PAIR(2));
	printw("dtelega ");
	attroff(COLOR_PAIR(2));
	attron(COLOR_PAIR(3));
	printw("sbondar ");
	attroff(COLOR_PAIR(3));
	attron(COLOR_PAIR(4));
	printw("apalanic ");
	attroff(COLOR_PAIR(4));
	printw("%187s", "Type N - next cycle");
}

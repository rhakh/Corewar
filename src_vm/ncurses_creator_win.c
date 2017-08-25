#include "vm.h"

WINDOW	*create_memory_win(void)
{
	WINDOW *memory_win;

	refresh();
	memory_win = create_newwin(ft_sqrt(MEM_SIZE) + 2, ft_sqrt(MEM_SIZE) * 2  + ft_sqrt(MEM_SIZE) + 2, 2, 0);
	wbkgd(memory_win, COLOR_PAIR(5));
	wrefresh(memory_win);
	return memory_win;
}

WINDOW	*create_stats_win(void)
{
	WINDOW *stats_win;

	refresh();
	stats_win = create_newwin((ft_sqrt(MEM_SIZE) + 2) * 0.75, 70, 2, ft_sqrt(MEM_SIZE) * 2  + ft_sqrt(MEM_SIZE) + 2);
	wbkgd(stats_win, COLOR_PAIR(5));
	wrefresh(stats_win);
	return stats_win;
}

WINDOW	*create_debug_win(void)
{
	WINDOW *debug_win;

	refresh();
	debug_win = create_newwin((ft_sqrt(MEM_SIZE) + 2) * 0.25, 70, 6 + (ft_sqrt(MEM_SIZE) + 2) * 0.70, ft_sqrt(MEM_SIZE) * 2  + ft_sqrt(MEM_SIZE) + 2);
	wbkgd(debug_win, COLOR_PAIR(5));
	wrefresh(debug_win);
	return debug_win;
}

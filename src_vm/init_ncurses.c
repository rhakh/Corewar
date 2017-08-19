#include "vm.h"

int 			send_to_ncurses(int start, int len, t_bot *bot, t_data *data) {
	//move_to_byte();
}

void		ft_init_ncurses(void)
{
	initscr();
	noecho();
	curs_set(FALSE); // off ncurses cursor
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
//	curs_set(FALSE);
}

void		ft_display_arena(t_data *data) {
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
//	move_to_byte(memory_win, 5);

	/* switch RUNNING / PAUSE */
	int k=0; // del
	while (1)
	{
		int pause = wgetch(stats_win);

		if (pause == ' ')
		{
			if (data->pause == 0)
			{
				data->pause = 1;
			}
			else
			{

				data->pause = 0;
			}
			move_to_byte(memory_win, k++);
			display_stats(data, stats_win);
		}
		if (pause == 113)
		{
			endwin();
			return ;
		}
	}



// halfdelay(1);         //Устанавливаем ограничение по времени ожидания getch() в 10 сек
//     printw("Press F2 to exit.\n");
// 	bool ex = false;
//     while ( !ex )
//     {
//         int ch = getch();

//         switch ( ch )
//         {
//         case ERR:
//             move_to_byte(memory_win, k++); 
//             break;
//         case KEY_F(2): //Выходим из программы, если была нажата F2
//             ex = true;
//             break;
//         default:  //Если всё нормально, выводим код нажатой клавиши
//         	k++;
//             break;
//         }

//         refresh(); //Выводим на настоящий экран

//     }

//     printw("Thank you. Good buy!");

	getch();
	endwin();
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurses_vm.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtelega <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/29 16:05:25 by dtelega           #+#    #+#             */
/*   Updated: 2017/08/29 16:08:14 by dtelega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NCURSES_VM_H
# define NCURSES_VM_H

# define NC_PAUSE_1 ' '
# define NC_PAUSE_2 'p'
# define NC_ONE_COMM_MOD 'n'
# define NC_SPEED_UP 's'
# define NC_SPEED_DOWN 'a'
# include "vm.h"
# include <ncurses.h>

WINDOW			*create_newwin(int height, int width, int starty, int startx);
WINDOW			*create_memory_win(void);
WINDOW			*create_stats_win(void);
WINDOW			*create_debug_win(void);
void			display_memory(t_data *data, WINDOW *win);
void			display_stats(t_data *data, WINDOW *stats_win);
void			display_debug(WINDOW *debug_win);
int				ncurses_move_cursor(t_data *data, t_bot *bot, int prev);
void			nc_display_arena(t_data *data);
void			nc_terminate(t_data *data);
int				ncurses_change_memory(int start, t_bot *bot, t_data *data);
void			print_byte(WINDOW *win, char byte, int position, int attr);
WINDOW			*create_memory_win(void);
WINDOW			*create_stats_win(void);
WINDOW			*create_debug_win(void);
void			move_to_byte(WINDOW *win, int byte);
void			display_memory(t_data *data, WINDOW *win);
void			display_stats(t_data *data, WINDOW *stats_win);
int				read_bot(t_string *code, char *file_name);
int				validate_bots(t_data *data);
void			ncurses_live(t_data *data, t_bot *bot);
void			ncurses_aff(t_data *data, t_bot *bot, int nb_reg);
void			display_winner(t_data *data, t_bot *bot);
void			ncurses_speed(t_data *data, char key);
char			ncurses_one_cm_mode(t_data *data, char pause);
char			ncurses_cycle_pause(t_data *data);
char			ncurses_global_cycle(t_data *data, char pause);
void			ncurses_kill_bot_cursor(t_data *data, int position);
void			display_curr_speed_cycles(t_data *data, WINDOW *stats_win);
int				ncurses_convert_speed(t_data *data);
void			ncurses_print_header(void);
int				ncurses_print_bot_memory(t_data *data, t_bot *cur_bot, int i,
										WINDOW *w);
void			ncurses_new_line(WINDOW *win);
void			display_players(t_data *data, WINDOW *stats_win, t_bot *cur_bot,
								int n_bot);
void			display_defines(t_data *data, WINDOW *stats_win);
void			ncurses_visual(t_data *data);

#endif

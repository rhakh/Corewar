/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl_vm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtelega <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 18:05:58 by dtelega           #+#    #+#             */
/*   Updated: 2017/09/02 13:20:09 by dtelega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SDL_VM_H
# define SDL_VM_H

# include <SDL.h>
# include "vm.h"
# define MUS_WINNER "sounds/mus.wav"
# define MUS_BEEP "sounds/crow.wav"
# define MUS_SPEED "sounds/crow.wav"
# define MUS_DEAD "sound/dead.wav"

typedef struct	s_audio_data
{
	Uint8		*position;
	Uint32		length;
}				t_audio_data;

void			audio_callback(void *user_data, Uint8 *stream,
							int stream_length);
int				sdl_sound(char *file_name);
#endif

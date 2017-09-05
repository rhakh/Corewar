/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtelega <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 17:39:53 by dtelega           #+#    #+#             */
/*   Updated: 2017/09/02 13:03:15 by dtelega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "sdl_vm.h"

void	audio_callback(void *userdata, Uint8 *stream, int streamlength)
{
	t_audio_data		*audio;
	Uint32				length;

	audio = (t_audio_data*)userdata;
	if (audio->length == 0)
		return ;
	length = (Uint32)streamlength;
	length = (length > audio->length ? audio->length : length);
	SDL_memcpy(stream, audio->position, length);
	audio->position += length;
	audio->length -= length;
}

int		sdl_sound(char *mus_file)
{
	SDL_AudioSpec		wav_spec;
	Uint8				*wav_start;
	Uint32				wav_length;
	t_audio_data		audio;
	SDL_AudioDeviceID	audio_device;

	if (SDL_LoadWAV(mus_file, &wav_spec, &wav_start, &wav_length) == NULL)
		return (1);
	audio.position = wav_start;
	audio.length = wav_length;
	wav_spec.callback = audio_callback;
	wav_spec.userdata = &audio;
	audio_device = SDL_OpenAudioDevice(NULL, 0, &wav_spec, NULL,
									SDL_AUDIO_ALLOW_ANY_CHANGE);
	if (audio_device == 0)
		return (1);
	SDL_PauseAudioDevice(audio_device, 0);
	while (audio.length > 0)
		SDL_Delay(60);
	SDL_CloseAudioDevice(audio_device);
	SDL_FreeWAV(wav_start);
	return (0);
}

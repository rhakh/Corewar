/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dtelega <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/31 17:39:53 by dtelega           #+#    #+#             */
/*   Updated: 2017/08/31 17:40:00 by dtelega          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "sdl_vm.h"

void    audioCallback(void* userData, Uint8* stream, int streamLength)
{
    t_audio_data* audio = (t_audio_data*)userData;

    if (audio->length == 0)
    {
		return;
    }

    Uint32 length = (Uint32)streamLength;

    length = (length > audio->length ? audio->length : length);

    SDL_memcpy(stream, audio->position, length);

    audio->position += length;
    audio->length -= length;
}

int     sdl_winner()
{
    SDL_Init(SDL_INIT_AUDIO);

    SDL_AudioSpec   wav_spec;
    Uint8*          wav_start;
    Uint32          wav_length;

    if(SDL_LoadWAV(MUS_WINNER, &wav_spec, &wav_start, &wav_length) == NULL)
    {
		printf("Error1\n");
    }

    t_audio_data audio;

    audio.position = wav_start;
    audio.length = wav_length;

    wav_spec.callback = audioCallback;
    wav_spec.userdata = &audio;

    SDL_AudioDeviceID audioDevice;
    audioDevice = SDL_OpenAudioDevice(NULL, 0, &wav_spec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE);

    if (audioDevice == 0)
    {
		printf("Error2\n");
        return 1;
    }

    SDL_PauseAudioDevice(audioDevice, 0);

    while (audio.length > 0)
    {
        SDL_Delay(100);
    }

    SDL_CloseAudioDevice(audioDevice);
    SDL_FreeWAV(wav_start);
    SDL_Quit();

    return 0;
}


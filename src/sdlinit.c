/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sdlinit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalytvyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 17:25:40 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/02/25 17:25:42 by yalytvyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ft_sdl_init(t_wolf *wolf)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		ft_error(2);
	if ((Mix_OpenAudio(20250, MIX_DEFAULT_FORMAT, 2, 1096)) == -1)
		ft_error(2);
	ft_load_texture(wolf);
	ft_load_sound(wolf);
	wolf->win = SDL_CreateWindow(
		"Wolf3d",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH,
		HEIGHT,
		SDL_WINDOW_ALLOW_HIGHDPI);
	if (wolf->win == NULL)
		ft_error(2);
	wolf->surface = SDL_GetWindowSurface(wolf->win);
	if (wolf->surface == NULL)
		ft_error(2);
	wolf->vimap = SDL_CreateRGBSurface(0, 202, 202, 32, 0, 0, 0, 0);
	if (wolf->vimap == NULL)
		ft_error(2);
	wolf->rectmap.x = 20;
	wolf->rectmap.y = 20;
	wolf->rectmap.w = 200;
	wolf->rectmap.h = 200;
}

void	ft_fps(t_wolf *wolf)
{
	wolf->oldtime = wolf->time;
	wolf->time = SDL_GetTicks();
	wolf->frtime = (wolf->time - wolf->oldtime) / 1000.0;
	wolf->movspeed = wolf->frtime * wolf->speed;
	wolf->rotspeed = wolf->frtime * 3.0;
	ft_putnbr((int)(1.0 / wolf->frtime));
	ft_putstr("\n");
}

void	ft_sdl_loop(t_wolf *wolf)
{
	SDL_Event	event;
	int			run;

	run = 1;
	Mix_VolumeMusic(MIX_MAX_VOLUME / 30);
	Mix_PlayMusic(wolf->music, 10);
	while (run)
	{
		ft_raycast(wolf);
		ft_sdl_shoot(wolf);
		ft_draw_gun(wolf);
		ft_cr_vimap(wolf);
		SDL_BlitSurface(wolf->vimap, NULL, wolf->surface, &wolf->rectmap);
		ft_fps(wolf);
		ft_sdl_move(wolf);
		ft_move(wolf);
		SDL_UpdateWindowSurface(wolf->win);
		while (SDL_PollEvent(&event))
		{
			ft_sdl_quit(event, &run);
		}
	}
	Mix_CloseAudio();
	SDL_FreeSurface(wolf->surface);
	SDL_DestroyWindow(wolf->win);
}

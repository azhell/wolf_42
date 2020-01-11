/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalytvyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/04 15:39:24 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/03/04 15:39:25 by yalytvyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		ft_gun_get_pixel(t_wolf *wolf, int x, int y, int n)
{
	int	*pixel;

	pixel = wolf->gun[n]->pixels + x * wolf->gun[n]->pitch + y *
	wolf->gun[n]->format->BytesPerPixel;
	return (*pixel);
}

void	ft_add_texture(t_wolf *wolf)
{
	static int	fps = 0;

	if (fps == 6)
	{
		wolf->gun_num++;
		fps = 0;
	}
	if (wolf->gun_num == 4)
	{
		wolf->gun_num = 0;
		wolf->eventcall.shoot_event = 0;
	}
	fps++;
}

void	ft_draw_gun(t_wolf *wolf)
{
	int		x;
	int		y;
	int		x1;
	int		y1;
	int		color;

	x = HEIGHT - 236;
	x1 = 0;
	y1 = 0;
	if (wolf->eventcall.shoot_event == 1)
		ft_add_texture(wolf);
	while (++x < WIDTH && x1 < 256)
	{
		y = WIDTH / 3 + 250;
		y1 = 0;
		while (y < HEIGHT && y1 < 256)
		{
			color = ft_gun_get_pixel(wolf, x1, y1, wolf->gun_num);
			if (color < 0)
				ft_put_pixel(wolf, y, x, color);
			y++;
			y1++;
		}
		x1++;
	}
}

void	ft_sdl_shoot(t_wolf *wolf)
{
	Uint8	*keyc;

	keyc = (Uint8*)SDL_GetKeyboardState(NULL);
	if ((keyc[SDL_SCANCODE_SPACE] == 1 || keyc[SDL_SCANCODE_SPACE] == 1) &&
	wolf->eventcall.shoot_event == 0)
	{
		Mix_PlayChannel(5, wolf->shoot, 0);
		wolf->eventcall.shoot_event = 1;
	}
}

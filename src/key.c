/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalytvyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 18:34:25 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/02/25 18:34:29 by yalytvyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ft_m(t_wolf *wolf)
{
	double k;
	double l;

	k = wolf->dirx > 0 ? 0.5 : -0.5;
	l = wolf->diry > 0 ? 0.5 : -0.5;
	if (wolf->eventcall.move_up == 1)
	{
		if (wolf->map[(int)(wolf->posx + (k + wolf->dirx) *
		wolf->movspeed)][(int)wolf->posy] == '0')
			wolf->posx += wolf->dirx * wolf->movspeed;
		if (wolf->map[(int)wolf->posx][(int)(wolf->posy + (l + wolf->diry) *
		wolf->movspeed)] == '0')
			wolf->posy += wolf->diry * wolf->movspeed;
	}
	if (wolf->eventcall.move_down == 1)
	{
		if (wolf->map[(int)(wolf->posx - (k + wolf->dirx) *
		wolf->movspeed)][(int)wolf->posy] == '0')
			wolf->posx -= wolf->dirx * wolf->movspeed;
		if (wolf->map[(int)wolf->posx][(int)(wolf->posy -
		(l + wolf->diry) * wolf->movspeed)] == '0')
			wolf->posy -= wolf->diry * wolf->movspeed;
	}
}

void	ft_r(t_wolf *wolf)
{
	if (wolf->eventcall.rot_rigth == 1)
	{
		wolf->oldirx = wolf->dirx;
		wolf->dirx = wolf->dirx * cos(wolf->rotspeed) - wolf->diry *
		sin(wolf->rotspeed);
		wolf->diry = wolf->oldirx * sin(wolf->rotspeed) + wolf->diry *
		cos(wolf->rotspeed);
		wolf->olplanex = wolf->planex;
		wolf->planex = wolf->planex * cos(wolf->rotspeed) - wolf->planey *
		sin(wolf->rotspeed);
		wolf->planey = wolf->olplanex * sin(wolf->rotspeed) + wolf->planey *
		cos(wolf->rotspeed);
	}
}

void	ft_sdl_quit(SDL_Event event, int *run)
{
	if ((SDL_QUIT == event.type) ||
	(SDL_SCANCODE_ESCAPE == event.key.keysym.scancode))
		*run = 0;
}

void	ft_sdl_move(t_wolf *wolf)
{
	Uint8	*keyc;

	keyc = (Uint8*)SDL_GetKeyboardState(NULL);
	if (keyc[SDL_SCANCODE_UP] == 1 || keyc[SDL_SCANCODE_W] == 1)
		wolf->eventcall.move_up = 1;
	else
		wolf->eventcall.move_up = 0;
	if (keyc[SDL_SCANCODE_DOWN] == 1 || keyc[SDL_SCANCODE_S] == 1)
		wolf->eventcall.move_down = 1;
	else
		wolf->eventcall.move_down = 0;
	if (keyc[SDL_SCANCODE_LEFT] == 1 || keyc[SDL_SCANCODE_A] == 1)
		wolf->eventcall.rot_left = 1;
	else
		wolf->eventcall.rot_left = 0;
	if (keyc[SDL_SCANCODE_RIGHT] == 1 || keyc[SDL_SCANCODE_D] == 1)
		wolf->eventcall.rot_rigth = 1;
	else
		wolf->eventcall.rot_rigth = 0;
	if (keyc[SDL_SCANCODE_LSHIFT] == 1 || keyc[SDL_SCANCODE_RSHIFT] == 1)
		wolf->speed = 7.0;
	else
		wolf->speed = 3.0;
}

void	ft_move(t_wolf *wolf)
{
	ft_m(wolf);
	if (wolf->eventcall.rot_left == 1)
	{
		wolf->oldirx = wolf->dirx;
		wolf->dirx = wolf->dirx * cos(-wolf->rotspeed) - wolf->diry *
		sin(-wolf->rotspeed);
		wolf->diry = wolf->oldirx * sin(-wolf->rotspeed) + wolf->diry *
		cos(-wolf->rotspeed);
		wolf->olplanex = wolf->planex;
		wolf->planex = wolf->planex * cos(-wolf->rotspeed) - wolf->planey *
		sin(-wolf->rotspeed);
		wolf->planey = wolf->olplanex * sin(-wolf->rotspeed) + wolf->planey *
		cos(-wolf->rotspeed);
	}
	ft_r(wolf);
}

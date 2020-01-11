/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ress.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalytvyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 17:58:25 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/03/02 17:58:28 by yalytvyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ft_free_ress(t_wolf *wolf)
{
	int		i;

	i = -1;
	while (++i < TEXTURES)
		SDL_FreeSurface(wolf->texture[i]);
	i = -1;
	while (++i < 4)
		SDL_FreeSurface(wolf->gun[i]);
}

void	ft_ray_rot(t_ray *ray)
{
	if (ray->side == 0 && ray->raydirx > 0)
	{
		ray->fwallx = ray->mapx;
		ray->fwally = ray->mapy + ray->wall;
	}
	else if (ray->side == 0 && ray->raydirx < 0)
	{
		ray->fwallx = ray->mapx + 1.0;
		ray->fwally = ray->mapy + ray->wall;
	}
	else if (ray->side == 1 && ray->raydiry > 0)
	{
		ray->fwallx = ray->mapx + ray->wall;
		ray->fwally = ray->mapy;
	}
	else
	{
		ray->fwallx = ray->mapx + ray->wall;
		ray->fwally = ray->mapy + 1.0;
	}
}

void	ft_load_texture(t_wolf *wolf)
{
	int	i;

	wolf->texture[0] = SDL_LoadBMP("resourse/texture/1.bmp");
	wolf->texture[1] = SDL_LoadBMP("resourse/texture/2.bmp");
	wolf->texture[2] = SDL_LoadBMP("resourse/texture/3.bmp");
	wolf->texture[3] = SDL_LoadBMP("resourse/texture/4.bmp");
	wolf->texture[4] = SDL_LoadBMP("resourse/texture/ground.bmp");
	wolf->texture[5] = SDL_LoadBMP("resourse/texture/sky.bmp");
	wolf->gun[0] = SDL_LoadBMP("resourse/texture/gun/1.bmp");
	wolf->gun[1] = SDL_LoadBMP("resourse/texture/gun/2.bmp");
	wolf->gun[2] = SDL_LoadBMP("resourse/texture/gun/3.bmp");
	wolf->gun[3] = SDL_LoadBMP("resourse/texture/gun/4.bmp");
	i = -1;
	while (++i < TEXTURES)
		if (wolf->texture[i] == NULL)
			ft_error(3);
	i = -1;
	while (++i < 4)
		if (wolf->gun[i] == NULL)
			ft_error(3);
}

void	ft_load_sound(t_wolf *wolf)
{
	wolf->music = Mix_LoadMUS("resourse/sound/redcurtain.wav");
	wolf->shoot = Mix_LoadWAV("resourse/sound/pistol.wav");
	if (wolf->music == NULL || wolf->shoot == NULL)
		ft_error(3);
}

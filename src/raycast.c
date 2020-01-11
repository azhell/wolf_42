/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalytvyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 12:44:50 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/02/26 12:44:54 by yalytvyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ft_raydir(t_ray *ray, t_wolf *wolf)
{
	if (ray->raydirx < 0)
	{
		ray->stepx = -1;
		ray->sdistx = (wolf->posx - ray->mapx) * ray->ddistx;
	}
	else
	{
		ray->stepx = 1;
		ray->sdistx = (ray->mapx + 1.0 - wolf->posx) * ray->ddistx;
	}
	if (ray->raydiry < 0)
	{
		ray->stepy = -1;
		ray->sdisty = (wolf->posy - ray->mapy) * ray->ddisty;
	}
	else
	{
		ray->stepy = 1;
		ray->sdisty = (ray->mapy + 1.0 - wolf->posy) * ray->ddisty;
	}
}

void	ft_rayhit(t_ray *ray, t_wolf *wolf)
{
	while (ray->hit == 0)
	{
		if (ray->sdistx < ray->sdisty)
		{
			ray->sdistx += ray->ddistx;
			ray->mapx += ray->stepx;
			ray->side = 0;
		}
		else
		{
			ray->sdisty += ray->ddisty;
			ray->mapy += ray->stepy;
			ray->side = 1;
		}
		if (wolf->map[ray->mapx][ray->mapy] != '0')
			ray->hit = 1;
	}
}

void	ft_wallheight(t_ray *ray, t_wolf *wolf)
{
	if (ray->side == 0)
		ray->perwalld = (ray->mapx - wolf->posx + (1 - ray->stepx) / 2) /
		ray->raydirx;
	else
		ray->perwalld = (ray->mapy - wolf->posy + (1 - ray->stepy) / 2) /
		ray->raydiry;
	if (ray->perwalld == -0)
		ray->perwalld = 0;
	ray->lineh = HEIGHT / ray->perwalld;
	ray->draws = -ray->lineh / 2 + HEIGHT / 2;
	if (ray->draws < 0)
		ray->draws = 0;
	ray->drawe = ray->lineh / 2 + HEIGHT / 2;
	if (ray->drawe >= HEIGHT)
		ray->drawe = HEIGHT - 1;
}

void	ft_change_text(t_wolf *wolf, t_ray *ray)
{
	ray->texn = wolf->map[ray->mapx][ray->mapy] - '0' - 1;
	if (ray->side == 1 && wolf->posy > ray->mapy)
		ray->texn = 0;
	else if (ray->side == 1 && wolf->posy < ray->mapy)
		ray->texn = 1;
	else if (ray->side == 0 && wolf->posx > ray->mapx)
		ray->texn = 2;
	else
		ray->texn = 3;
	if (ray->side == 0)
		ray->wall = wolf->posy + ray->perwalld * ray->raydiry;
	else
		ray->wall = wolf->posx + ray->perwalld * ray->raydirx;
	ray->wall -= floor(ray->wall);
	ray->texx = ray->wall * TEXW;
	if (ray->side == 0 && ray->raydirx > 0)
		ray->texx = TEXW - ray->texx - 1;
	if (ray->side == 1 && ray->raydirx < 0)
		ray->texy = TEXW - ray->texy - 1;
}

void	ft_raycast(t_wolf *wolf)
{
	t_ray	ray;
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		ray.camx = 2 * x / (double)WIDTH - 1;
		ray.raydirx = wolf->dirx + wolf->planex * ray.camx;
		ray.raydiry = wolf->diry + wolf->planey * ray.camx;
		ray.mapx = (int)wolf->posx;
		ray.mapy = (int)wolf->posy;
		ray.ddisty = fabs(1 / ray.raydiry);
		ray.ddistx = fabs(1 / ray.raydirx);
		ray.hit = 0;
		ft_raydir(&ray, wolf);
		ft_rayhit(&ray, wolf);
		ft_wallheight(&ray, wolf);
		ft_change_text(wolf, &ray);
		ft_ray_rot(&ray);
		ray.distp = 0.0;
		ray.distw = ray.perwalld;
		ft_draw_line(&ray, x, wolf);
		x++;
	}
}

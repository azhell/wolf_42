/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalytvyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 13:51:43 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/02/26 13:51:46 by yalytvyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int		*ft_get_pixel(t_wolf *wolf, t_ray *ray, int x)
{
	int	*get_pixel;
	int	k;

	k = x * 256 - HEIGHT * 128 + ray->lineh * 128;
	ray->texy = ((k * TEXW) / ray->lineh) / 256;
	get_pixel = wolf->texture[ray->texn]->pixels + ray->texy *
	wolf->texture[ray->texn]->pitch + ray->texx *
	wolf->texture[ray->texn]->format->BytesPerPixel;
	return (get_pixel);
}

int		*ft_get_floor(t_wolf *wolf, t_ray *ray, int x)
{
	double	wq;
	int		*pixel;

	ray->distc = HEIGHT / (2.0 * x - HEIGHT);
	wq = (ray->distc - ray->distp) / (ray->distw - ray->distp);
	ray->texn = 4;
	ray->flx = (int)((wq * ray->fwallx + (1 - wq) * wolf->posx) * TEXW) % TEXW;
	ray->fly = (int)((wq * ray->fwally + (1 - wq) * wolf->posy) * TEXW) % TEXW;
	pixel = wolf->texture[ray->texn]->pixels + ray->fly *
	wolf->texture[ray->texn]->pitch + ray->flx *
	wolf->texture[ray->texn]->format->BytesPerPixel;
	return (pixel);
}

int		*ft_get_sky(t_wolf *wolf, t_ray *ray, int x)
{
	double	wq;
	int		*pixel;

	ray->distc = HEIGHT / (2.0 * x - HEIGHT);
	wq = -(ray->distc - ray->distp) / (ray->distw - ray->distp);
	ray->texn = 5;
	ray->flx = (int)((wq * ray->fwallx + (1 - wq) * wolf->posx) * TEXW) % TEXW;
	ray->fly = (int)((wq * ray->fwally + (1 - wq) * wolf->posy) * TEXW) % TEXW;
	pixel = wolf->texture[ray->texn]->pixels + ray->fly *
	wolf->texture[ray->texn]->pitch + ray->flx *
	wolf->texture[ray->texn]->format->BytesPerPixel;
	return (pixel);
}

void	ft_put_pixel(t_wolf *wolf, int x, int y, int pixel)
{
	int		*target_pixel;

	if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT - 1)
		return ;
	target_pixel = wolf->surface->pixels + y * wolf->surface->pitch + x *
	wolf->surface->format->BytesPerPixel;
	*target_pixel = pixel;
}

void	ft_draw_line(t_ray *ray, int y, t_wolf *wolf)
{
	int x;
	int	x2;
	int i;

	x = ray->draws - 1;
	x2 = ray->drawe - 1;
	i = -1;
	wolf->ray = *ray;
	while (++x < ray->drawe)
	{
		ray->color = (int*)ft_get_pixel(wolf, ray, x);
		ft_put_pixel(wolf, y, x, *ray->color);
	}
	while (++i < ray->draws)
	{
		ray->color = ft_get_sky(wolf, ray, i);
		ft_put_pixel(wolf, y, i, *ray->color);
	}
	while (++x2 < HEIGHT)
	{
		ray->color = ft_get_floor(wolf, ray, x2);
		ft_put_pixel(wolf, y, x2, *ray->color);
	}
}

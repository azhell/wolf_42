/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vismap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalytvyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/01 09:16:02 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/03/01 09:16:04 by yalytvyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ft_map_set_pix(t_wolf *wolf, int x, int y, int pixel)
{
	int		*target_pixel;

	if (x < 0 || x > WIDTH || y < 0 || y > HEIGHT)
		return ;
	target_pixel = wolf->vimap->pixels + y * wolf->vimap->pitch + x *
	wolf->vimap->format->BytesPerPixel;
	*target_pixel = pixel;
}

void	ft_map_border(t_wolf *wolf)
{
	int i;
	int j;

	i = -1;
	while (++i < MW)
	{
		j = -1;
		while (++j < MH)
		{
			if (i == 0 || i == MW - 1 || (i != MW && i != MW - 1 &&
			(j == 0 || j == MH - 1)))
				ft_map_set_pix(wolf, j, i, 0x15FF00);
		}
	}
}

void	ft_drawmap(int x, int y, t_wolf *wolf, int color)
{
	int		x1;
	int		y1;
	int		yy;

	x = x * 16 + 1;
	yy = y * 16 + 1;
	x1 = x + 16;
	y1 = yy + 16;
	while (x < x1)
	{
		y = yy;
		while (y < y1)
		{
			if (x < 200 && y < 200)
				ft_map_set_pix(wolf, x, y, color);
			y++;
		}
		x++;
	}
}

void	ft_color_map(t_wolf *wolf)
{
	int		posx;
	int		posy;
	int		i;
	int		j;

	i = -1;
	posx = (int)wolf->posx - 7;
	while (++i <= 12 && ++posx != 100000000 && (j = -1))
	{
		posy = (int)wolf->posy - 7;
		while (++j <= 12 && ++posy != 100000000)
		{
			if (posx >= 0 && posx < wolf->wid && posy >= 0 && posy < wolf->len)
			{
				if (wolf->map[posx][posy] != '0')
					ft_drawmap(i, j, wolf, 0xff0000);
				else
					ft_drawmap(i, j, wolf, 0x00ffff);
				if (posx == (int)wolf->posx && posy == (int)wolf->posy)
					ft_drawmap(i, j, wolf, 0x0000ff);
			}
			else
				ft_drawmap(i, j, wolf, 0x000000);
		}
	}
}

void	ft_cr_vimap(t_wolf *wolf)
{
	ft_color_map(wolf);
	ft_map_border(wolf);
}

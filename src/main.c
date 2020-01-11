/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalytvyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 15:16:04 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/02/21 15:16:05 by yalytvyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ft_init(t_wolf *wolf)
{
	wolf->speed = 5.0;
	wolf->dirx = 1;
	wolf->diry = 0;
	wolf->planex = 0;
	wolf->planey = 0.66;
	wolf->time = 0;
	wolf->oldtime = 0;
	wolf->eventcall.move_down = 0;
	wolf->eventcall.move_up = 0;
	wolf->eventcall.rot_left = 0;
	wolf->eventcall.rot_rigth = 0;
	wolf->eventcall.rot_rigth = 0;
	wolf->gun_num = 0;
}

int		main(int ac, char **av)
{
	t_wolf	*wolf;

	if (ac != 2)
		ft_error(0);
	wolf = (t_wolf*)malloc(sizeof(t_wolf));
	wolf->map = ft_read_file(av[1], wolf);
	ft_val_border(wolf->map, wolf);
	ft_init(wolf);
	ft_sdl_init(wolf);
	ft_sdl_loop(wolf);
	ft_free_ress(wolf);
	SDL_Quit();
	return (0);
}

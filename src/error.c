/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalytvyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:41:31 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/02/25 13:41:32 by yalytvyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ft_error(int i)
{
	if (i == 0)
	{
		ft_putstr("usage: ./wolf3d \"map_name\"\n");
		exit(0);
	}
	else if (i == 1)
	{
		ft_putstr("Not valid map :(\n");
		exit(-1);
	}
	else if (i == 2)
	{
		ft_putstr("Error init SDL :(\n");
		exit(2);
	}
	else if (i == 3)
	{
		ft_putstr("Error load resourse:(\n");
		exit(3);
	}
}

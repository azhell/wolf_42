/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalytvyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:35:55 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/02/25 13:35:57 by yalytvyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	ft_val_border(char **map, t_wolf *wolf)
{
	int i;
	int j;
	int	flag;

	i = -1;
	flag = 0;
	while (++i < wolf->wid && (j = -1))
	{
		while (map[i][++j])
		{
			if (i == 0 || i == wolf->wid - 1)
				if (map[i][j] != '1')
					ft_error(1);
			if (map[i][j] == '0' && flag == 0)
			{
				flag = 1;
				wolf->posx = (float)i + 0.5;
				wolf->posy = (float)j + 0.5;
			}
			if (map[i][0] != '1' || map[i][wolf->len - 1] != '1')
				ft_error(1);
		}
	}
	if (flag == 0)
		ft_error(1);
}

void	ft_valid_content(t_line *list)
{
	int	i;

	i = 0;
	while (list->content[i] != '\0')
	{
		if (list->content[i] < 0 && list->content[i] > 5)
			ft_error(1);
		i++;
	}
}

void	ft_valid_len(t_line *list, t_wolf *wolf, int count)
{
	t_line	*tmp;
	int		len;

	tmp = list;
	if (count <= 2)
		ft_error(1);
	len = ft_strlen(tmp->content);
	if (len <= 2)
		ft_error(1);
	while (tmp)
	{
		len = ft_strlen(tmp->content);
		if (len <= 2)
			ft_error(1);
		if (wolf->len != len)
			ft_error(1);
		ft_valid_content(list);
		tmp = tmp->next;
	}
	if (wolf->len > 1000 || wolf->wid > 1000)
		ft_error(1);
}

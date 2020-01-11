/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalytvyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 13:35:46 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/02/25 13:35:50 by yalytvyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

char	**ft_cr_map(t_line *list, int count, t_wolf *wolf)
{
	char	**map;
	int		j;
	int		i;

	i = 0;
	MALLCHECK((map = (char**)malloc(sizeof(char*) * count)));
	while (list)
	{
		MALLCHECK((map[i] = (char*)malloc(sizeof(char) * (wolf->len + 1))));
		j = -1;
		while (++j < wolf->len)
		{
			map[i][j] = list->content[j];
		}
		map[i][j] = '\0';
		i++;
		list = list->next;
	}
	return (map);
}

char	**ft_read_file(char *file, t_wolf *wolf)
{
	int		fd;
	char	**map;
	char	*line;
	int		count;
	t_line	*list;

	count = 0;
	FDERROR((fd = open(file, O_RDONLY)));
	while (get_next_line(fd, &line) > 0)
	{
		if (count == 0)
		{
			list = ft_lnewline(line);
			wolf->len = ft_strlen(line);
		}
		else
			ft_lddline(&list, line);
		count++;
		free(line);
	}
	wolf->wid = count;
	ft_valid_len(list, wolf, count);
	map = ft_cr_map(list, count, wolf);
	ft_ldel(&list);
	return (map);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalytvyn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 16:37:26 by yalytvyn          #+#    #+#             */
/*   Updated: 2019/02/25 16:37:28 by yalytvyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

t_line	*ft_lnewline(char *content)
{
	t_line	*list;
	char	*str;

	str = ft_strnew(0);
	MALLCHECK((list = (t_line*)malloc(sizeof(t_line))));
	if (content == NULL)
		list->content = NULL;
	else
	{
		list->content = ft_strjoin(str, content);
		free(str);
	}
	list->next = NULL;
	return (list);
}

void	ft_lddline(t_line **list, char *content)
{
	t_line	*new_list;
	t_line	*tmp;
	t_line	*head;

	if (list == NULL)
		return ;
	tmp = *list;
	head = tmp;
	new_list = ft_lnewline(content);
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new_list;
	*list = head;
}

void	ft_ldel(t_line **list)
{
	t_line	*tmp;

	tmp = *list;
	if (tmp)
	{
		while (tmp->next)
		{
			free(tmp->content);
			free(tmp);
			tmp = tmp->next;
		}
		free(tmp->content);
		free(tmp);
	}
}

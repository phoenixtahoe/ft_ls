/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavid <pdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 14:13:12 by pdavid            #+#    #+#             */
/*   Updated: 2019/05/08 18:34:37 by pdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_info *ft_create_node(t_info *info, char *path, char *name)
{
	t_info	*new;
	t_info	*cur;
	struct stat *data;

	data = (struct stat *)malloc(sizeof(struct stat));
	new = (t_info *)malloc(sizeof(t_info));
	new->name = ft_strdup(name);
	new->path = ft_strdup(path);
	memcpy(&(new->time), &(data->st_atimespec), sizeof(struct timespec));
	new->time = data->st_mtimespec;
	new->next = NULL;
	new->sub = NULL;
	new->prev = NULL;
	if (info == NULL)
		info = new;
	else
	{
		cur = info;
		while (cur->next != NULL)
			cur = cur->next;
		cur->next = new;
		new->prev = cur;
	}
	return (new);
}
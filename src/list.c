/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavid <pdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 14:13:12 by pdavid            #+#    #+#             */
/*   Updated: 2019/05/23 16:46:51 by pdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_info *create_list(t_info *info, char *path, char *name)
{
	t_info	*new;
	t_info	*cur;
	struct stat *data;

	data = (struct stat *)malloc(sizeof(struct stat));
	new = (t_info *)malloc(sizeof(t_info));
	new->name = ft_strdup(name);
	new->path = ft_strdup(path);
	lstat(new->path, data);
	new->data = data;
	memcpy(&(new->time), &(data->st_atimespec), sizeof(struct timespec));
	new->time = data->st_mtimespec;
	new->next = NULL;
	new->sub = NULL;
	new->prev = NULL;
	if (info == NULL)
	{
		info = new;
	}
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

t_info  *merge_links(t_env *e, t_info *first, t_info *second)
{
	if (!(first))
		return (second);
	if (!(second))
		return (first);
	if (first->name[e->i] < second->name[e->i])
	{
		e->i = 0;
		first->next = merge_links(e, first->next, second);
		first->next->prev = first;
		first->prev = NULL;
		return (first);
	}
	else if (first->name[e->i] > second->name[e->i]) 
	{
		e->i = 0;
		second->next = merge_links(e, first, second->next);
		second->next->prev = second;
		second->prev = NULL;
		return (second);
	}
	else
	{
		e->i++;
		return (merge_links(e, first, second));
	}
}

t_info	*merge_split(t_info *head)
{
	t_info *fast;
	t_info *slow;
	t_info *temp;

	fast = head;
	slow = head;
	while (fast->next && fast->next->next)
	{
		fast = fast->next->next;
		slow = slow->next;
	}
	temp = slow->next;
	slow->next = NULL;
	return (temp);
}
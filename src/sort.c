/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavid <pdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:21:35 by pdavid            #+#    #+#             */
/*   Updated: 2019/05/22 16:18:38 by pdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_info	*recursive_sort(t_env *e, t_info *head)
{
	t_info *ptr;

	ptr = head;
	while (head)
	{
		ptr = head;
		if (head && e->options.R == true && head->sub != NULL)
			head->sub = recursive_sort(e, head->sub);
		head = head->next;
	}
	return (ptr);
}

t_info  *merge_sort(t_env *e, t_info *head)
{
	t_info *second;
	t_info *ptr;

	e->i = 0;
	ptr = head;
	if (!head || !head->next)
		return head;
	second = merge_split(head);
	head = merge_sort(e, head);
	second = merge_sort(e, second);
	return (e->options.t == true ? time_sort(e, head, second) 
		: merge_links(e, head, second));
}

t_info  *time_sort(t_env *e, t_info *first, t_info *second)
{
	if (!(first))
		return (second);
	if (!(second))
		return (first);
	// if (ft_get_time(first, second))
	// {
	// 	first->next = time_sort(e, first->next, second);
	// 	first->next->prev = first;
	// 	first->prev = NULL;
	// 	return (first);
	// }
	second->next = time_sort(e, first, second->next);
	second->next->prev = second;
	second->prev = NULL;
	return (second);
}
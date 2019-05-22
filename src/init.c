/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavid <pdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:03:26 by pdavid            #+#    #+#             */
/*   Updated: 2019/05/22 16:25:05 by pdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void init_paths(t_env *e, int ac)
{
	int i;

	i = 0;
	e->paths = (char **)malloc(sizeof(char *) * ac);
	while (i < ac)
		e->paths[i++] = NULL;
}

void init_env(t_env *e, int ac)
{
	e->options.R = false;
	e->options.a = false;
	e->options.t = false;
	e->options.l = false;
	e->options.r = false;
	e->tot = true;
	e->run = true;
	e->info = NULL;
	e->args = NULL;
	e->type = NULL;
	e->dargs = NULL;
	init_paths(e, ac);
	e->i = 0;
	e->x = 0;
	e->px = 0;
	e->total = 0;
	e->temp = NULL;
}

void		init_flags(int argc, char **argv, t_env *e)
{
	e->i = 0;
	e->x = e->x + 1;
	if (argv[e->x] && argv[e->x][e->i] == '-' && argc > e->x)
	{
		e->i++;
		if ((argv[e->x][e->i - 1]) && !argv[e->x][e->i])
			err(0, &argv[e->x][0]);
		while (argv[e->x][e->i])
		{
			IFR = ARGLETTER == 'R' ? true : IFR;
			IFa = ARGLETTER == 'a' ? true : IFa;
			IFt = ARGLETTER == 't' ? true : IFt;
			IFl = ARGLETTER == 'l' ? true : IFl;
			IFr = ARGLETTER == 'r' ? true : IFr;
			if (ARGLETTER != 'R' && ARGLETTER != 'a' &&
				ARGLETTER != 't' && ARGLETTER != 'l' &&
				ARGLETTER != 'r' && ARGLETTER)
					err(0, &argv[e->x][1]);
			e->i++;
		}
	}
	else
		return ;
	init_flags(argc, argv, e);
}

void init_ls(t_env *e, t_info *temp)
{
	e->info = init_merge(e, e->info);
	display_print(e, e->info);
	if (temp->next || (temp->prev && e->options.r))
		write(1, "\n", 1);
	e->run = true;
}

t_info *init_merge(t_env *e, t_info *head)
{
	t_info *ptr;

	if (head)
	{
		head = merge_sort(e, head);
	}
	ptr = head;
	while (ptr != NULL)
	{
		if (ptr->sub)
		{
			ptr->sub = init_merge(e, ptr->sub);
		}
		ptr = ptr->next;
	}
	return (head);
}
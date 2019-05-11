/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavid <pdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 16:03:26 by pdavid            #+#    #+#             */
/*   Updated: 2019/05/10 21:38:09 by pdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void ft_init_2d(t_env *e, int ac)
{
	int i;

	i = 0;
	printf("%s\n", "dumb idiot");
	e->paths = (char **)malloc(sizeof(char *) * ac);
	while (i < ac)
		e->paths[i++] = NULL;
}

void init_env(t_env *e, int ac)
{
	printf("%s\n", "dumb idiot");
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
	ft_init_2d(e, ac);
	e->i = 0;
	e->x = 0;
	e->px = 0;
	e->total = 0;
	e->temp = NULL;
}
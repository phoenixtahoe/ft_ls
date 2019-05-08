/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavid <pdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 14:08:55 by pdavid            #+#    #+#             */
/*   Updated: 2019/05/08 15:56:07 by pdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int main(int ac, char **av)
{
	t_env *e;
	if (ac < 2)
	{
		// e = error();
	}
	else
	{
		if (!(e = (t_env *)malloc(sizeof(t_env))))
			exit(1);
		if (!(e->flags = (t_flags *)malloc(sizeof(t_flags))))
				exit(1);
		e->flags->cur = format_flags(av, &e->flags->flag);
		printf("%d\n", e->flags->l);
		// e->dir = init_dirs(av, &e->dir);
	}
	// init_env(e, 0);
	return (0);
}
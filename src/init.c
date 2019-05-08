/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavid <pdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 14:13:12 by pdavid            #+#    #+#             */
/*   Updated: 2019/05/08 15:54:26 by pdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void	get_flags(t_env *e)
{
	int i;
	
	i = 0;
	e->flags = (t_flags *)malloc(sizeof(t_flags));
	while (i < e->flags->flag)
	{
		if (e->flags->cur[i] == 'l')
			e->flags->l = 1;
		else if (e->flags->cur[i] == 'R')
			e->flags->cr = 1;
		else if (e->flags->cur[i] == 'r')
			e->flags->r = 1;
		else if (e->flags->cur[i] == 'a')
			e->flags->a = 1;
		else if (e->flags->cur[i] == 't')
			e->flags->t = 1;
		// else if (validate_flags(e) == -1)
		// 	printf("%s\n", "illegal option. For help do ./ft_ls -h");
		i++;
	}
}

int		validate_flags(t_env *e)
{
	int	ver;
	int	i;
	
	i = 0;
	ver = 0;
	while (i < e->flags->flag)
	{
		if (e->flags->cur[i] == 'l')
			ver++;
		else if (e->flags->cur[i] == 'R')
			ver++;
		else if (e->flags->cur[i] == 'r')
			ver++;
		else if (e->flags->cur[i] == 'a')
			ver++;
		else if (e->flags->cur[i] == 't')
			ver++;
		i++;
	}
	if (ver != e->flags->flag)
		return (-1);
	return (1);
}

int		parse_flag(char *av[])
{
	int i;
	int y;
	int flags;
	
	flags = 0;
	i = 1;
	while (av[i])
	{
		if (av[i][0] == '-')
		{
			y = 1;
			while (av[i][y])
			{
				flags++;
				y++;
			}
		}
		i++;
	}
	return (flags);
}

char *format_flags(char *av[], int *flags)
{
	char *res;
	int i;
	int y;
	int x;
	
	*flags = parse_flag(av);
	if (flags == 0)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (*flags + 1));
	
	i = 1;
	x = 0;
	while (av[i][0])
	{
		if (av[i][1] == '-')
		{
			y = 1;
			while (av[i][1] != '\0')
			{
				res[x] = av[i][y];
				y++;
				x++;
			}
		}
		i++;
	}
	return (res);
}

void	init_flags(t_env *e)
{
	int	i;
	
	i = 0;
	e->dir = NULL;
	get_flags(e);
	if ((validate_flags(e)) == -1)
		return ;
	while (i < e->dir->dir)
	{
		printf("%s\n", "exit");
		// if (e->flags->cr == 1)
		// 	// recursive_sort(e->dir, e, e->flags, i);
		// else
		// 	// start_sort(e->dir, e, e->flags, i);
		// i++;
	}
	i = 0;
	while (e->flags->cur[i])
	{
		free(e->dir->cur[i]);
		i++;
	}
	free(e->dir->cur);
	free(e->flags->cur);
	free(e->flags);
}
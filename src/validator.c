/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavid <pdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:18:48 by pdavid            #+#    #+#             */
/*   Updated: 2019/05/22 16:25:50 by pdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void    validate_total(t_env *e, t_info *head)
{
	t_info *ptr;

	ptr = head;
	while (ptr)
	{
		e->total += ptr->data->st_blocks;
		ptr = e->options.r ? ptr->prev : ptr->next;
	}
}

void		validate_dir(t_env *e, struct stat *info)
{
	if (ft_strcmp(e->paths[e->px], ".") != 0)
	{
		lstat(e->paths[e->px], info);
	}
	if (lstat(e->paths[e->px], info) || (!S_ISDIR(info->st_mode) 
	&& !S_ISREG(info->st_mode) && !S_ISCHR(info->st_mode)
	&& !S_ISBLK(info->st_mode) && !S_ISFIFO(info->st_mode)
	&& !S_ISLNK(info->st_mode) && !S_ISSOCK(info->st_mode)
	&& ft_strcmp(e->paths[e->px], ".")))
	{
		err(1, e->paths[e->px]);
		e->paths[e->px] = NULL;
	}
	else if (e->paths[e->px] && ft_strcmp(e->paths[e->px], ".")
			&& !S_ISDIR(info->st_mode))
			e->args = create_list(e->args, e->paths[e->px], ".");
	else if (e->paths[e->px] && (!ft_strcmp(e->paths[e->px], ".")
			|| S_ISDIR(info->st_mode)))
			e->dargs = create_list(e->dargs, e->paths[e->px], PATH);
	else
		free(e->paths[e->px]);
}

void		validate_path(t_env *e)
{
	struct stat     *info;

	e->px = 0;
	if (!(e->paths[e->px]))
	{
		e->paths[e->px] = ft_strnew(2);
		e->paths[e->px][e->px] = '.';
		e->paths[e->px + 1] = NULL;
	}
	while (e->paths[e->px])
	{
		info = (struct stat *)malloc(sizeof(struct stat));
		validate_dir(e, info);
		free(info);
		e->px++;
	}
	while (e->args && e->args->prev != NULL)
		e->args = e->args->prev;
	while (e->dargs && e->dargs->prev != NULL)
		e->dargs = e->dargs->prev;
	e->dargs = e->dargs ? init_merge(e, e->dargs) : e->dargs;
	parse_files(e);
	e->x = 0;
	e->i = 0;
	
}
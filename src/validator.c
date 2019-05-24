/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavid <pdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:18:48 by pdavid            #+#    #+#             */
/*   Updated: 2019/05/23 16:07:44 by pdavid           ###   ########.fr       */
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

int		validate_time(t_info *first, t_info *second)
{
	long seconds;
	long nano_seconds;

	seconds = first->time.tv_sec - second->time.tv_sec;
	if (!seconds)
	{
		nano_seconds = first->time.tv_nsec - second->time.tv_nsec;
		if (!nano_seconds)
			return (ft_strcmp(first->name, second->name) <= 0 ? 1 : 0);
		return (nano_seconds > 0 ? 1: 0);
	}
	return (seconds > 0 ? 1 : 0);
}

void	validate_perms(t_info *head, char *perms)
{
	if (S_ISDIR(head->data->st_mode))
	   perms = ft_strjoin(perms, "d");
	else if (S_ISCHR(head->data->st_mode))
		perms = ft_strjoin(perms, "c");
	else if (S_ISBLK(head->data->st_mode))
		perms = ft_strjoin(perms, "b");
	else if (S_ISLNK(head->data->st_mode))
	   perms = ft_strjoin(perms, "l");
	else if (S_ISSOCK(head->data->st_mode))
		perms = ft_strjoin(perms, "s");
	else if (S_ISFIFO(head->data->st_mode))
		perms = ft_strjoin(perms, "p");
	else
	   perms = ft_strjoin(perms, "-");
	perms = S_IRUSR & HEDDATA ? ft_strjoin(perms, "r") : ft_strjoin(perms, "-");
	perms = S_IWUSR & HEDDATA ? ft_strjoin(perms, "w") : ft_strjoin(perms, "-");
	perms = S_IXUSR & HEDDATA ? ft_strjoin(perms, "x") : ft_strjoin(perms, "-");
	perms = S_IRGRP & HEDDATA ? ft_strjoin(perms, "r") : ft_strjoin(perms, "-");
	perms = S_IWGRP & HEDDATA ? ft_strjoin(perms, "w") : ft_strjoin(perms, "-");
	perms = S_IXGRP & HEDDATA ? ft_strjoin(perms, "x") : ft_strjoin(perms, "-");
	perms = S_IROTH & HEDDATA ? ft_strjoin(perms, "r") : ft_strjoin(perms, "-");
	perms = S_IWOTH & HEDDATA ? ft_strjoin(perms, "w") : ft_strjoin(perms, "-");
	perms = S_IXOTH & HEDDATA ? ft_strjoin(perms, "x") : ft_strjoin(perms, "-");
	printf("%s  ", perms);
	free(perms);
}

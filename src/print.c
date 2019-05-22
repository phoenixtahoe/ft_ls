/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavid <pdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 18:35:15 by pdavid            #+#    #+#             */
/*   Updated: 2019/05/22 16:25:27 by pdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void    path_print(t_env *e, t_info *head)
{
	t_info *ptr;
	char *temp;

	ptr = head;
	temp = ft_strdup(ptr->path);
	if (e->dargs && (e->dargs->next || e->dargs->prev || e->args) && e->run == true)
	{
		while (ptr->path[e->i])
		{
			if (ptr->path[e->i] == '/')
			{
				if (ptr->path[e->i + 1] && ptr->path[e->i + 1] != '/')
				{
					temp[e->i] = '\0';
					printf("%s:\n", temp);
					e->run = false;
				}
			}
			e->i++;
		}
	}
	free(temp);
}

void    time_print(t_info *head)
{
	char *timer;
	int i;

	timer = ctime(&head->time.tv_sec);
	timer += 4;
	i = ft_strlen(timer);
	i -= 9;
	timer[i] = '\0';
	printf("%s\n", timer);
}

void    info_print(t_info *head)
{
	// perms = ft_strnew(1);
	// // ft_get_perms(head, perms);
	printf("%d ", head->data->st_nlink);
	// grp = getgrgid(head->data->st_gid);
	// usr = getpwuid(head->data->st_uid);
	// printf("%s ", usr->pw_name);
	// printf("%s ", grp->gr_name);
	printf("%6lld", head->data->st_size);
	// time_print(head);
}

void    basic_print(t_env *e, t_info *head)
{
	t_info *ptr;

	ptr = head;
	while (ptr)
	{
		printf("%s", ptr->name);
		printf("\n");
		ptr = e->options.r ? ptr->prev : ptr->next;
	}
}

void	long_print(t_env *e, t_info *head)
{
	struct group *grp;
	struct passwd *usr;
	char *link;

	path_print(e, head);
	validate_total(e, head);
	if (e->tot == true)
	{
		printf("total %d\n", e->total);
	}
	e->total = 0;
	while (head)
	{
		usr = NULL;
		grp = NULL;
		info_print(head);
		if (S_ISLNK(head->data->st_mode) && (link = STRNEW))
		{
			readlink(head->path, link, 1024);
			printf("%s -> %s\n", head->name, link);
		}
		printf("%s\n", head->name);
		head = e->options.r == true ? head->prev : head->next;
	}
}

void	display_print(t_env *e, t_info *head)
{
	t_info *ptr;
	
	ptr = head;
	
	if (e->options.r == false && e->options.l == false)
	{
		basic_print(e, ptr);
	}
	if (e->options.l == true)
	{
		long_print(e, ptr);
	}
	if (e->options.r == true)
	{
		recursive_sort(e, ptr);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavid <pdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 14:08:55 by pdavid            #+#    #+#             */
/*   Updated: 2019/05/10 22:05:40 by pdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_info	*ft_split(t_info *head)
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

t_info  *ft_time_sort(t_env *e, t_info *first, t_info *second)
{
	if (!(first))
		return (second);
	if (!(second))
		return (first);
	// if (ft_get_time(first, second))
	// {
	// 	first->next = ft_time_sort(e, first->next, second);
	// 	first->next->prev = first;
	// 	first->prev = NULL;
	// 	return (first);
	// }
	else
	{
		second->next = ft_time_sort(e, first, second->next);
		second->next->prev = second;
		second->prev = NULL;
		return (second);
	}
}

t_info  *ft_merge_links(t_env *e, t_info *first, t_info *second)
{
	if (!(first))
		return (second);
	if (!(second))
		return (first);
	if (first->name[e->i] < second->name[e->i])
	{
		e->i = 0;
		first->next = ft_merge_links(e, first->next, second);
		first->next->prev = first;
		first->prev = NULL;
		return (first);
	}
	else if (first->name[e->i] > second->name[e->i]) 
	{
		e->i = 0;
		second->next = ft_merge_links(e, first, second->next);
		second->next->prev = second;
		second->prev = NULL;
		return (second);
	}
	else
	{
		e->i++;
		return (ft_merge_links(e, first, second));
	}
}

t_info  *ft_merge_sort(t_env *e, t_info *head)
{
	t_info *second;
	t_info *ptr;

	e->i = 0;
	ptr = head;
	if (!head || !head->next)
		return head;
	second = ft_split(head);
	head = ft_merge_sort(e, head);
	second = ft_merge_sort(e, second);
	return (e->options.t == true ? ft_time_sort(e, head, second) 
		: ft_merge_links(e, head, second));
}

t_info *ft_init_merge(t_env *e, t_info *head)
{
	t_info *ptr;

	if (head)
	{
		head = ft_merge_sort(e, head);
	}
	ptr = head;
	while (ptr != NULL)
	{
		if (ptr->sub)
		{
			ptr->sub = ft_init_merge(e, ptr->sub);
		}
		ptr = ptr->next;
	}
	return (head);
}

t_info	*ft_ls(t_env *e, char *path, t_info *info)
{
	DIR				*type;
	struct dirent	*file;
	char			*etype;

	if ((type = opendir(path)) == NULL)
	{
		printf("%s\n", "error");
		exit(1);
	}
	while ((file = readdir(type)) && (etype = ft_strjoin(path, file->d_name)))
	{
		if ((ft_strncmp(file->d_name, ".", 1) == 0 && IFa == true) || NOTDOT)
		{
			info = ft_create_node(info, etype, file->d_name);
		}
		else
		{
			free(etype);
			continue ;
		}
		if (DRPERMS && ((!IFa && NOTDOT) || (IFa && DOTCMP && ISDOT)))
		{
			info->sub = ft_ls(e, etype, info->sub);
		}
		else if (info)
		{
			info->sub = NULL;
		}
		free(etype);
	}
	closedir(type);
	while (info && info->prev != NULL)
	{
		info = info->prev;
	}
	return(info);
}

void	parse_path(int ac, char **av, t_env *e)
{
	e->i = 0;
	if (av[e->x] && av[e->x][e->i] != '-')
	{
		e->paths[e->px] = ft_strnew(ft_strlen(av[e->x]) + 1);
		while ((size_t)e->i < ft_strlen(av[e->x]))
		{
			e->paths[e->px][e->i] = av[e->x][e->i];
			e->i++;
		}
		e->paths[e->px][e->i] = '\0';
	}
	else
	{
		return ;
	}
	e->x = e->x + 1;
	e->px = e->px + 1;
	parse_path(ac, av, e);
}

void		ft_toggle_options(int argc, char **argv, t_env *e)
{
	e->i = 0;
	e->x = e->x + 1;
	if (argv[e->x] && argv[e->x][e->i] == '-' && argc > e->x)
	{
		e->i++;
		if ((argv[e->x][e->i - 1]) && !argv[e->x][e->i])
			printf("%s\n", "big gay");
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
					printf("%s\n", "big gay");
			e->i++;
		}
	}
	else
		return ;
	ft_toggle_options(argc, argv, e);
}

void		ft_make_files(t_env *e)
{
	if (e->args)
	{
		e->args = ft_init_merge(e, e->args);
		e->tot = false;
		ft_display(e, e->args);
		e->tot = true;
		if (e->dargs)
		{
			write (1, "\n", 1);
		}
	}
}

void		ft_check_file(t_env *e, struct stat *info)
{
	if (ft_strcmp(e->paths[e->px], ".") != 0)
	{
		lstat(e->paths[e->px], info);
	}
}

void		ft_check_paths(t_env *e)
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
		ft_check_file(e, info);
		free(info);
		e->px++;
	}
	while (e->args && e->args->prev != NULL)
		e->args = e->args->prev;
	while (e->dargs && e->dargs->prev != NULL)
		e->dargs = e->dargs->prev;
	e->dargs = e->dargs ? ft_init_merge(e, e->dargs) : e->dargs;
	ft_make_files(e);
	e->x = 0;
	e->i = 0;
}

void ft_doshit(t_env *e, t_info *temp)
{
	e->info = ft_init_merge(e, e->info);
	ft_display(e, e->info);
	if (temp->next || (temp->prev && e->options.r))
		write(1, "\n", 1);
	e->run = true;
}


int main(int ac, char **av)
{
	t_env e;
	t_info *temp;

	init_env(&e, ac);
	ft_toggle_options(ac, av, &e);
	parse_path(ac, av, &e);
	ft_check_paths(&e);
	if (e.options.r)
		// e.dargs = ft_goto_end(&e, e.dargs);
		printf("%s\n", "fag boi");
	temp = e.dargs;
	while (temp)
	{
		if (!(e.info = ft_ls(&e, temp->name, e.info)))
		{
			temp = e.options.r ? temp->prev : temp->next;
			continue ;
		}
		ft_doshit(&e, temp);
		temp = e.options.r ? temp->prev : temp->next;
	}
	return (0);
}
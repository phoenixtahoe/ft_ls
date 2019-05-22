/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavid <pdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 14:08:55 by pdavid            #+#    #+#             */
/*   Updated: 2019/05/22 16:23:44 by pdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

t_info		*err(int i, char *str)
{
	printf("%s\n", str);
	if (i == 0)
	{
		printf("%s\n", "idiot wrong flags");
		exit(0);
	}
	else if (i == 1)
	{
		printf("%s\n", "wrong dir");
	}
	else if (i == 2)
	{
		printf("%s\n", "no perms");
	}
	return (NULL);
}

t_info		*ft_ls(t_env *e, char *path, t_info *info)
{
	DIR				*type;
	struct dirent	*file;
	char			*etype;

	if ((type = opendir(path)) == NULL)
	{
		return(err(2, path));
	}
	while ((file = readdir(type)) && (etype = ft_strjoin(path, file->d_name)))
	{
		if ((ft_strncmp(file->d_name, ".", 1) == 0 && IFa == true) || NOTDOT)
		{
			info = create_list(info, etype, file->d_name);
		}
		else
		{
			free(etype);
			continue;
		}
		// if (DRPERMS && ((!IFa && NOTDOT) || (IFa && DOTCMP && ISDOT)))
		// {
		// 	info->sub = ft_ls(e, etype, info->sub);
		// }
		if (info)
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

void		parse_path(int ac, char **av, t_env *e)
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

void		parse_files(t_env *e)
{
	if (e->args)
	{
		e->args = init_merge(e, e->args);
		e->tot = false;
		display_print(e, e->args);
		e->tot = true;
		if (e->dargs)
		{
			write (1, "\n", 1);
		}
	}
}

int			main(int ac, char **av)
{
	t_env 	e;
	t_info 	*temp;

	init_env(&e, ac);
	init_flags(ac, av, &e);
	parse_path(ac, av, &e);
	validate_path(&e);
	if (e.options.r)
		e.dargs = recursive_sort(&e, e.dargs);
	temp = e.dargs;
	while (temp)
	{
		if (!(e.info = ft_ls(&e, temp->name, e.info)))
		{
			temp = e.options.r ? temp->prev : temp->next;
			continue ;
		}
		init_ls(&e, temp);
		temp = e.options.r ? temp->prev : temp->next;
	}
	return (0);
}
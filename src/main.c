/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavid <pdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 14:08:55 by pdavid            #+#    #+#             */
/*   Updated: 2019/05/08 19:58:03 by pdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

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

int main(int ac, char **av)
{
	t_env e;
	t_info *temp;

	init_env(&e, ac);
	parse_path(ac, av, &e);
	check_paths(&e);
	if (e.options->r)
		// e.dargs = ft_goto_end(e, e.dargs);
		printf("%s\n", "dumb idiot");
	temp = e.dargs;
	while (temp)
	{
		printf("%s\n", "wubs is dumb idiot");
		// ft_doshit(e, temp);
		// temp = e.options->r ? temp->prev : temp->next;
	}
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavid <pdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 14:13:22 by pdavid            #+#    #+#             */
/*   Updated: 2019/05/10 21:38:35 by pdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <stdint.h>
# include <stdlib.h>
# include <stdio.h>
# include "./libft/libft.h"
# include <errno.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/xattr.h>
# include <unistd.h>
# include <grp.h>
# include <pwd.h>
# include <stdbool.h>
# include <time.h>

# define IFa e->options.a
# define IFR e->options.R
# define IFr e->options.r
# define IFl e->options.l
# define IFt e->options.t
# define USR struct passwd *usr
# define DATA info->data->st_mode
# define PATH e->paths[e->px]
# define HEDDATA head->data->st_mode
# define ARGLETTER argv[e->x][e->i]
# define ISDOT strcmp(file->d_name, ".")
# define DOTCMP ft_strncmp(file->d_name, "..", 3)
# define STRJOIN2 ft_strjoin2(path, file->d_name)
# define STRNEW ft_strnew(ft_strlen(head->path) + 1)
# define NOTDOT (ft_strncmp(file->d_name, ".", 1) != 0)
# define DRPERMS S_ISDIR(DATA) && IFR && (S_IRUSR & DATA) && PERMS
# define PERMS (S_IRGRP & DATA) && (S_IROTH & DATA) && (S_IWUSR & DATA)

typedef	struct			s_options
{
	bool				R;
	bool				a;
	bool				t;
	bool				l;
	bool				r;
}						t_options;

typedef	struct			s_info
{
	char				*name;
	char				*path;
	char				*color;
	struct	stat		*data;
	struct	s_info		*next;
	struct	s_info		*prev;
	struct	s_info		*sub;
	struct	timespec	time;
}						t_info;

typedef	struct			s_env
{
	t_info				*info;
	t_info				*args;
	t_info				*dargs;
	t_options			options;
	char				**paths;
	char				*type;
	char				*temp;
	bool				run;
	bool				tot;
	bool				run2;
	int					total;
	int					px;
	int					x;
	int					i;
}						t_env;

void ft_display(t_env *e, t_info *head);
void init_env(t_env *e, int ac);
t_info *ft_create_node(t_info *info, char *path, char *name);

#endif
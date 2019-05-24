/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavid <pdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 14:13:22 by pdavid            #+#    #+#             */
/*   Updated: 2019/05/23 16:28:34 by pdavid           ###   ########.fr       */
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
# define ISDOT ft_strcmp(file->d_name, ".")
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

/*		Functions that validate				*/
/*		flags, paths, dirs					*/
	
	void				validate_path(t_env *e);
	void				validate_dir(t_env *e, struct stat *info);
	void    			validate_total(t_env *e, t_info *head);
	void				validate_perms(t_info *head, char *perms);
	int					validate_time(t_info *first, t_info *second);
	
/*		Functions that handle				*/
/*		sorting of the ls					*/

	t_info				*time_sort(t_env *e, t_info *first, t_info *second);
	t_info				*recursive_sort(t_env *e, t_info *head);
	t_info				*merge_sort(t_env *e, t_info *head);
	
/*		Functions that initialize			*/
/*		the merge-sort, flags, environment	*/

	t_info 				*init_merge(t_env *e, t_info *head);
	void				init_ls(t_env *e, t_info *temp);
	void				init_flags(int argc, char **argv, t_env *e);
	void				init_env(t_env *e, int ac);
	void				init_paths(t_env *e, int ac);
	
/*		Functions that magically			*/
/*		sort my list's aka (merge-sort method)	*/

t_info					*create_list(t_info *info, char *path, char *name);
t_info					*merge_links(t_env *e, t_info *first, t_info *second);
t_info					*merge_split(t_info *head);

/*		Functions that are print			*/
/* 		long, basic etc...					*/

void				long_print(t_env *e, t_info *head);
void				basic_print(t_env *e, t_info *head);
void				info_print(char *perms, t_info *head, USR, struct group *grp);
void				time_print(t_info *head);
void				path_print(t_env *e, t_info *head);
void				display_print(t_env *e, t_info *head);

/*		Functions that are utils			*/
/* 											*/

t_info				*err(int i, char *str);
void				parse_files(t_env *e);
void				parse_path(int ac, char **av, t_env *e);
t_info				*ft_ls(t_env *e, char *path, t_info *info);

#endif
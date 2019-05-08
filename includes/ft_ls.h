/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavid <pdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 14:13:22 by pdavid            #+#    #+#             */
/*   Updated: 2019/05/08 15:51:14 by pdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../includes/libft/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <dirent.h>
# include <unistd.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>
# include <stdio.h>
# include <stdbool.h>

typedef struct	s_flags
{
	char 	*cur;
	bool		l;
	bool		cr;
	bool		a;
	bool		r;
	bool		t;
	int			flag;
}				t_flags;

typedef struct	s_dir
{
	char 	**cur;
	int		dir;
}				t_dir;

typedef struct	s_env
{
	t_flags		*flags;
	t_dir		*dir;
	int			i;
	int			ret;
	int			len;
	
}				t_env;

char 	*format_flags(char *av[], int *flags);
void	get_flags(t_env *e);
void	init_flags(t_env *e);

#endif
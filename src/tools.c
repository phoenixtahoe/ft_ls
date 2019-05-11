/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavid <pdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 18:35:15 by pdavid            #+#    #+#             */
/*   Updated: 2019/05/10 21:45:55 by pdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

void    ft_print_path(t_env *e, t_info *head)
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

void    ft_print_time(t_info *head)
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

void    ft_get_total(t_env *e, t_info *head)
{
    t_info *ptr;

    ptr = head;
    while (ptr)
    {
        e->total += ptr->data->st_blocks;
        ptr = e->options.r ? ptr->prev : ptr->next;
    }
}

void    ft_print_info(char *perms, t_info *head, struct passwd *usr, struct group *grp)
{
    perms = ft_strnew(1);
    // ft_get_perms(head, perms);
    printf("%d ", head->data->st_nlink);
    grp = getgrgid(head->data->st_gid);
    usr = getpwuid(head->data->st_uid);
    printf("%s ", usr->pw_name);
    printf("%s ", grp->gr_name);
    printf("%6lld", head->data->st_size);
    ft_print_time(head);
}

void    ft_printer(t_env *e, t_info *head)
{
    t_info *ptr;

    ptr = head;
    ft_print_path(e, ptr);
    while (ptr)
    {
        printf("%s%s", ptr->color, ptr->name);
        printf("\n");
        ptr = e->options.r ? ptr->prev : ptr->next;
    }
}

// void    ft_print_long(t_env *e, t_info *head)
// {
//     char *perms;
//     struct group *grp;
//     struct passw *usr;
//     // char *link;

//     ft_get_total(e, head);
//     if (e->tot == true)
//     {
//         printf("total %d\n", e->total);
//     }
//     e->total = 0;
//     while (head)
//     {
//         perms = NULL;
//         usr = NULL;
//         grp = NULL;
//         ft_print_info(perms, head, usr, grp);
//         printf("%s%s\n", head->color, head->name);
//         head = e->options.r == true ? head->prev : head->next;
//     }
// }

void ft_display(t_env *e, t_info *head)
{
    t_info *ptr;
    
    ptr = head;

    ft_printer(e, ptr);
}

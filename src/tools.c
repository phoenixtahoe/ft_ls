/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pdavid <pdavid@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/08 18:35:15 by pdavid            #+#    #+#             */
/*   Updated: 2019/05/08 18:37:13 by pdavid           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

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
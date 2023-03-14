/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:31:35 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/03/14 13:50:38 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_check(char *cmd)
{
    int i;
    i = 0;
    int k1;
    int k2;
    k1 = 0;
    k2 = 0;
    while(cmd[i])
    {
        if(cmd[i] == 39)
            k1++;
        else if(cmd[i] == 34)
            k2++;
        i++;
    }
	if (k1 % 2 == 1 && k1 > 0)
		return (0);
	if (k2 % 2 == 1 && k2 > 0)
		return (0);
    if (k1 % 2 == 0 && k1 > 0)
		return (2);
	if (k2 % 2 == 0 && k2 > 0)
		return (2);
	return (1);
}

char    *skip_quote(char *cmd)
{
    int i;
    int j;
    j = 0;
    i = 0;
    char *dst;
    dst = malloc(ft_strlen(cmd));
    while(cmd[i])
    {
        if(cmd[i] == 39)
            i++;
        else if(cmd[i] == 34)
            i++;
        else
        {
            dst[j] = cmd[i];
            j++;
            i++;
        }
    }
    dst[j] = '\0';
    return dst;
}

int count_2d(char **dst)
{
    int i;
    i = 0;
    while(dst[i])
        i++;
    return i;
}

void    fix_arg(t_all *my_struct)
{
    int i;
    int j;
    j = 0;
    i = 0;
    my_struct->my_command = malloc(count_2d(my_struct->fix_cmd)+1);
    while(my_struct->fix_cmd[i])
    {
        if(quote_check(my_struct->fix_cmd[i]) == 2 || quote_check(my_struct->fix_cmd[i]) == 1)
        {
            my_struct->my_command[j] = skip_quote(my_struct->fix_cmd[i]);
            printf("[%s ",my_struct->my_command[j]);
            j++;
        }
        else if(quote_check(my_struct->fix_cmd[i]) == 0)
            printf("error");
        i++;
    }
    printf("]");
    // exit(0);
}
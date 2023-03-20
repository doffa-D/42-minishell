/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:31:35 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/03/16 18:38:45 by nouakhro         ###   ########.fr       */
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

int count_2d(t_all *my_struct)
{
    my_struct->command_len = -1;
    while(my_struct->fix_cmd[++my_struct->command_len]);
    return my_struct->command_len;
}

int checker(char *cmd)
{
    int i;
    i = 0;
    while(cmd[i])
    {
        if(cmd[i] == 39 && cmd[i+1] == 34 && cmd[i+2] == 39)
            return 1;
        else if (cmd[i] == 34 && cmd[i+1] == 39 && cmd[i+2] == 34)
            return 2;
        i++;
    }
    return 0;
}


char    *upload(char *cmd,int x)
{
    int i;
    i = 0;
    int j;
    j = 0;
    char *dst = malloc(sizeof(char) * ft_strlen(cmd)+1);
    if(x == 2)
    {
        while(cmd[i])
        {
            if(cmd[i] == 34)
            {
                i++;
            }
            else
            {
                dst[j] = cmd[i];
                i++;
                j++;
            }
        }
    }
    else if(x == 1)
    {

        while(cmd[i])
        {
            if(cmd[i] == 39)
            {
                i++;
            }
            else
            {
                dst[j] = cmd[i];
                i++;
                j++;

            }
        }
    }
    dst[j] = '\0';
    return dst;

}

char    *dollar_handle(char *cmd,int *dollar)
{
    int i;
    int j;
    int x;
    i = 0;
    j = 0;
    x = 0;
    char *dst = malloc(ft_strlen(cmd));
    char *dst2 = malloc(ft_strlen(cmd));
    while(cmd[i])
    {
        if(cmd[i] == '$' && (cmd[i+1] != 34 || cmd[i+1] != 39))
        {
            j = i;
            i++;
            *dollar = 1;
        }
        else if(cmd[i+1] == 34 || cmd[i+1] == 39)
        {
            break;
        }
        else
            i++;
    }
    while(j <= i)
    {
        dst[x] = cmd[j];
        x++;
        j++;
    }
    dst[j] = '\0';
	if (getenv(&dst[1]) != NULL)
    {
        dst2 = ft_strjoin(getenv(&dst[1]),skip_quote(&cmd[i+1]));
        return(dst2);
    }
    else if(cmd[i+2])
    {
        return skip_quote(&cmd[i+1]);
    }
    return 0;
}

void    fix_arg(t_all *my_struct)
{
    int i;
    int j;
    j = 0;
    i = 0;
    char *cmd;
    my_struct->my_command = malloc(sizeof(char *) * (count_2d(my_struct)+1));
    while(my_struct->fix_cmd[i])
    {
        if(quote_check(my_struct->fix_cmd[i]) == 2)
        {
            if(ft_strchr(my_struct->fix_cmd[i],'$'))
            {
                cmd = dollar_handle(my_struct->fix_cmd[i],&my_struct->dollar);
                if(cmd != 0)
                    my_struct->my_command[j] = cmd;
                else
                    my_struct->my_command[j] = 0;
            }
            else
                my_struct->my_command[j] = skip_quote(my_struct->fix_cmd[i]);
            j++;
        }
        else if (quote_check(my_struct->fix_cmd[i]) == 1)
        {
            my_struct->my_command[j] = my_struct->fix_cmd[i];
            j++;
        }
        else if(quote_check(my_struct->fix_cmd[i]) == 0)
        {
            if(checker(my_struct->fix_cmd[i]) == 1 || checker(my_struct->fix_cmd[i]) == 2)
            {
                my_struct->my_command[j] = upload(my_struct->fix_cmd[i],checker(my_struct->fix_cmd[i]));
                j++;
            }
            else
            {
                printf("error\n");
                exit(0);
            }
        }
        i++;
    }
    my_struct->my_command[j] = 0;
}
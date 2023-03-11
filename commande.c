/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commande.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:19:24 by nouakhro          #+#    #+#             */
/*   Updated: 2023/03/10 14:52:08 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    exicut_echo(t_all *my_struct)
{
    int len;
    len = 0;
    while(my_struct->my_command[len])
        len++;
    my_struct->command_len = len;
    int i;
    int j;
    i = 0;
    j = 1;
    char *buff;
    while(my_struct->my_command[j])
    {
        i = 0;
        while((size_t)i < ft_strlen(my_struct->my_command[j]))
        {
            if(my_struct->my_command[j][i] == 34)
                i++;
            else if(my_struct->my_command[j][i] == '$')
            {
                int x;
                int z;
                x = i+1;
                z = 0;
                buff = malloc(ft_strlen(my_struct->my_command[j]));
                while(my_struct->my_command[j][x])
                {
                    if(my_struct->my_command[j][x] != 34 && my_struct->my_command[j][x] != '$' && my_struct->my_command[j][x] != 39 && my_struct->my_command[j][x] != ' ')
                    {
                        buff[z] = my_struct->my_command[j][x];
                        z++;
                    }
                }
                if(my_struct->my_command[j][i-1] == 34 && my_struct->my_command[j][ft_strlen(my_struct->my_command[j])-1] == 34)
                    printf("%s",getenv(buff));
                else if (my_struct->my_command[j][i-1] == 39 && my_struct->my_command[j][ft_strlen(my_struct->my_command[j])-1] == 39)
                    printf("$%s",buff);
                else if(!my_struct->my_command[j][i-1] && !my_struct->my_command[j][ft_strlen(my_struct->my_command[j])])
                    printf("%s",getenv(buff));
                free(buff);
                break;
            }
            i++;
        }
        printf(" ");
        j++;
    }
    printf("\n");
}

void exicut_commande(t_all my_struct, int i)
{
    if(!ft_strncmp(my_struct.my_command[0], "cd", ft_strlen("cd")))
		exit(1);
    else if(!ft_strncmp(my_struct.my_command[0], "echo", ft_strlen("echo")))
        exicut_echo(&my_struct);
	else if(!ft_strncmp(my_struct.cmd, my_struct.cmd, ft_strlen(my_struct.cmd)))
    {
        check_rediractions(my_struct);
        execve(my_struct.my_path[i], my_struct.my_command, NULL);
    }
}
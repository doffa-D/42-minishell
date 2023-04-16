/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_echo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/10 18:00:54 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/04/16 19:59:09 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	exicut_echo(t_all *my_struct, int c_of_s)
{
    int i;
    int j;
    j = 0;
    i = 1;
    while(j <= c_of_s)
    {
        i = 1;
        if (my_struct->each_cmd[j].cmd[1][0] == '-' && my_struct->each_cmd[j].cmd[1][1] == 'n' &&  !my_struct->each_cmd[j].cmd[1][2])
            i++;
        while (my_struct->each_cmd[j].cmd[i])
        {
            printf("%s", my_struct->each_cmd[j].cmd[i]);
            i++;
        }
        if (!(my_struct->each_cmd[j].cmd[1][0] == '-' && my_struct->each_cmd[j].cmd[1][1] == 'n' && !my_struct->each_cmd[j].cmd[1][2]))
            printf("\n");
        j++;
    }
}
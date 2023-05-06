/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:18:50 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/06 19:50:10 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void free_all()
{
    int i = 0;
    if(g_struct.my_path)
    {
        while (g_struct.my_path[i])
        {
            free(g_struct.my_path[i]);
            i++;
        }
        free(g_struct.my_path);
    }
    i = 0;
    // if(_struct.my_command)
    // {
    //     while (_struct.my_command[i])
    //     {
    //         free(_struct.my_command[i]);
    //         i++;
    //     }
    //     free(_struct.my_command);
    // }
    free((char *)g_struct.cmd);
}
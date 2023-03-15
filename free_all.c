/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:18:50 by nouakhro          #+#    #+#             */
/*   Updated: 2023/03/15 11:30:35 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void free_all(t_all my_struct)
{
    int i = 0;
    if(my_struct.my_path)
    {
        while (my_struct.my_path[i])
        {
            free(my_struct.my_path[i]);
            i++;
        }
        free(my_struct.my_path);
    }
    i = 0;
    if(my_struct.my_command)
    {
        while (my_struct.my_command[i])
        {
            free(my_struct.my_command[i]);
            i++;
        }
        free(my_struct.my_command);
    }
    free((char *)my_struct.cmd);
}
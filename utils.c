/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:20:11 by nouakhro          #+#    #+#             */
/*   Updated: 2023/04/13 00:02:22 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int get_the_path(t_all my_struct)
{
    int i = 0;
    while (my_struct.my_path[i])
    {
        if(my_struct.my_command[0])
        {
            my_struct.my_path[i] = ft_strjoin(my_struct.my_path[i], "/");
	        my_struct.my_path[i] = ft_strjoin(my_struct.my_path[i], my_struct.my_command[0]);
            i++;
        }
		else
            return 1;
    }
    return 0;
}

void exit_the_program(t_all my_struct)
{
    if(!ft_strncmp(my_struct.cmd, "exit", ft_strlen("exit")) || \
	!ft_strncmp(my_struct.cmd, "quit", ft_strlen("quit")) || \
    !ft_strncmp(my_struct.cmd, "q", ft_strlen("q")) ||\
    !ft_strncmp(my_struct.cmd, "e", ft_strlen("e")))
        exit(0);
}
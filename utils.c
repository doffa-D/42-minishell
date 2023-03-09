/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:20:11 by nouakhro          #+#    #+#             */
/*   Updated: 2023/03/09 14:21:52 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void get_the_path(t_all my_struct)
{
    int i = 0;
    while (my_struct.my_path[i])
    {
        my_struct.my_path[i] = ft_strjoin(my_struct.my_path[i], "/");
	    my_struct.my_path[i] = ft_strjoin(my_struct.my_path[i], my_struct.my_command[0]);
		    i++;
    }
}

void exit_the_program(t_all my_struct)
{
    if(!ft_strncmp(my_struct.commande_line, "exit", ft_strlen("exit")) || \
	!ft_strncmp(my_struct.commande_line, "quit", ft_strlen("quit")) || \
    !ft_strncmp(my_struct.commande_line, "q", ft_strlen("q")) ||\
    !ft_strncmp(my_struct.commande_line, "e", ft_strlen("e")))
        exit(0);
}
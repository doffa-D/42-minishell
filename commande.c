/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commande.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:19:24 by nouakhro          #+#    #+#             */
/*   Updated: 2023/03/10 14:47:54 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    exicut_echo(t_all *my_struct)
{
    int len;
    len = 0;
    while(my_struct->cmd[len])
        len++;
    printf("%d\n",len);

}

void exicut_commande(t_all my_struct, int i)
{
    if(!ft_strncmp(my_struct.my_command[0], "cd", ft_strlen("cd")))
    {
		exit(1);
    }
    else if(!ft_strncmp(my_struct.my_command[0], "echo", ft_strlen("echo")))
        exicut_echo(&my_struct);
	else if(!ft_strncmp(my_struct.cmd, my_struct.cmd, ft_strlen(my_struct.cmd)))
    {
        check_rediractions(my_struct);
        execve(my_struct.my_path[i], my_struct.my_command, NULL);
    }
}
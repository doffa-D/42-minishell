/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commande.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:19:24 by nouakhro          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/03/09 15:50:08 by hdagdagu         ###   ########.fr       */
=======
/*   Updated: 2023/03/09 16:04:01 by nouakhro         ###   ########.fr       */
>>>>>>> 70f341826ec3c81f3c49c0ecd52c9bc33781e516
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    exicut_echo(t_all *my_struct)
{
    int len;
    len = 0;
    while(my_struct->cmd[len])
        len++;
<<<<<<< HEAD
    my_struct->command_len = len;
    printf("[%d]\n",my_struct->command_len);
=======
    printf("%d\n",len);
>>>>>>> 70f341826ec3c81f3c49c0ecd52c9bc33781e516
    // int i;
    // int j;
    // i = 0;
    // j = 1;
    // while(j <)
    
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
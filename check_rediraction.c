/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rediraction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:18:08 by nouakhro          #+#    #+#             */
/*   Updated: 2023/03/10 14:59:29 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void check_rediractions(t_all my_struct)
{
    int j = 1;
    while (my_struct.my_command[j])
    {
        if(my_struct.my_command[j] && \
        !ft_strncmp(my_struct.my_command[j], ">>", \
        ft_strlen(my_struct.my_command[j])) \
        && ft_strlen(my_struct.my_command[j]) == 2)
        {
            if(my_struct.my_command[j + 1])
            {
                int fd = open(my_struct.my_command[j + 1] ,O_RDWR | O_APPEND);
                dup2(fd, STDOUT_FILENO);
                while (my_struct.my_command[j])
                {
                    my_struct.my_command[j] = 0;
                    j++;
                }
                break;
            }
        }
        if(my_struct.my_command[j] && \
        !ft_strncmp(my_struct.my_command[j],">", \
        ft_strlen(my_struct.my_command[j])))
        {
            if(my_struct.my_command[j + 1])
            {
                int fd = open(my_struct.my_command[j + 1] ,O_RDWR | O_TRUNC);
                printf("%s", "");
                dup2(fd, STDOUT_FILENO);
                while (my_struct.my_command[j])
                {
                    my_struct.my_command[j] = 0;
                    j++;
                }
                break;
            }
        }
        else if(my_struct.my_command[j] && \
        !ft_strncmp(my_struct.my_command[j], "<", \
        ft_strlen(my_struct.my_command[j])))
        {
            if(my_struct.my_command[j + 1])
            {
                int fd = open(my_struct.my_command[j + 1],O_RDWR);
                dup2(fd, STDIN_FILENO);
                while (my_struct.my_command[j])
                {
                    my_struct.my_command[j] = 0;
                    j++;
                }
                break;
            }
        }
        j++;
    }
}
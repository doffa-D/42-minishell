/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rediraction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:18:08 by nouakhro          #+#    #+#             */
/*   Updated: 2023/03/20 12:26:30 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"
#include<string.h>

void check_rediractions(t_all my_struct)
{
    int j = 1;
    while (my_struct.my_command[j])
    {
        if(my_struct.my_command[j] && !ft_strncmp(my_struct.my_command[j], "<<", ft_strlen(my_struct.my_command[j])) && ft_strlen(my_struct.my_command[j]) == 2)
        {
            
            if(my_struct.my_command[j + 1])
            {
                // int i = 1;
                char *beffer = 0;
                // char *herdoc = "";
                while(1)
                {
                    beffer = readline("> ");
                    if(strstr(beffer, my_struct.my_command[j + 1]))
                        break;
                    // herdoc = ft_strjoin(herdoc, beffer);
                    // herdoc = ft_strjoin(herdoc, "\n");
                }
                my_struct.my_command[j] = 0;
                break;
                // int fd = open(my_struct.my_command[j + 1],O_CREAT| O_RDWR, 0777);
                // dup2(STDOUT_FILENO, STDIN_FILENO);
                // printf("%s", herdoc);
            }
        }
        else if(my_struct.my_command[j] && !ft_strncmp(my_struct.my_command[j], ">>", ft_strlen(my_struct.my_command[j])) && ft_strlen(my_struct.my_command[j]) == 2)
        {
            if(my_struct.my_command[j + 1])
            {
                int fd = open(my_struct.my_command[j + 1] ,O_CREAT| O_RDWR| O_APPEND, 0777);
                dup2(fd, STDOUT_FILENO);
                my_struct.my_command[j] = 0;
                close(fd);
            }
        }
        else if(my_struct.my_command[j] && !ft_strncmp(my_struct.my_command[j],">", ft_strlen(my_struct.my_command[j])))
        {
            if(my_struct.my_command[j + 1])
            {
                int fd = open(my_struct.my_command[j + 1] ,O_CREAT| O_RDWR| O_TRUNC, 0777);
                dup2(fd, STDOUT_FILENO);
                my_struct.my_command[j] = 0;
                close(fd);
            }
        }
        else if(my_struct.my_command[j] && !ft_strncmp(my_struct.my_command[j], "<", ft_strlen(my_struct.my_command[j])))
        {
            if(my_struct.my_command[j + 1])
            {
                int fd = open(my_struct.my_command[j + 1],O_CREAT| O_RDWR, 0777);
                dup2(fd, STDIN_FILENO);
                my_struct.my_command[j] = 0;
                close(fd);
            }
        }
        j++;
    }
}
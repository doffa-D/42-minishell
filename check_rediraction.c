/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rediraction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:18:08 by nouakhro          #+#    #+#             */
/*   Updated: 2023/04/14 18:24:23 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"
#include<string.h>


//ssir fhm hadchi mz1
// void check_rediractions(t_all my_struct)
// {
//     int j = 0;
//     printf("%s\n",my_struct.my_command[j]);
//     while (my_struct.my_command[j])
//     {
//         if(!ft_strncmp(my_struct.my_command[j], "<<", ft_strlen(my_struct.my_command[j])) && ft_strlen(my_struct.my_command[j]) == 2)
//         {
            
//             if(my_struct.my_command[j + 1])
//             {
//                 int fd_by_pipe[2];
//                 char *beffer = 0;
//                 char *herdoc = ft_strdup("");
//                 pipe(fd_by_pipe);
//                 while(1)
//                 {
//                     beffer = readline("> ");
//                     if(strstr(beffer, my_struct.my_command[j + 1]))
//                         break;
//                     herdoc = ft_strjoin(herdoc, beffer);
//                     herdoc = ft_strjoin(herdoc, "\n");
//                 }
//                 ft_putstr_fd(herdoc, fd_by_pipe[1]);
//                 dup2(fd_by_pipe[0], STDIN_FILENO);
//                 close(fd_by_pipe[1]);
//                 my_struct.my_command[j] = 0;
//             }
//         }
//         else if(!ft_strncmp(my_struct.my_command[j], ">>", ft_strlen(my_struct.my_command[j])) && ft_strlen(my_struct.my_command[j]) == 2)
//         {
//             if(my_struct.my_command[j + 1])
//             {
//                 int fd = open(my_struct.my_command[j + 1] ,O_CREAT| O_RDWR| O_APPEND, 0777);
//                 dup2(fd, STDOUT_FILENO);
//                 my_struct.my_command[j] = 0;
//                 close(fd);
//             }
//         }
//         else if(!ft_strncmp(my_struct.my_command[j],">", ft_strlen(my_struct.my_command[j])))
//         {
//             if(my_struct.my_command[j + 1])
//             {
//                 printf("cdscs\n");
//                 int fd = open(my_struct.my_command[j + 1] ,O_CREAT| O_RDWR| O_TRUNC, 0777);
//                 dup2(fd, STDOUT_FILENO);
//                 my_struct.my_command[j] = 0;
//                 close(fd);
//             }
//         }
//         else if(!ft_strncmp(my_struct.my_command[j], "<", ft_strlen(my_struct.my_command[j])))
//         {
//             if(my_struct.my_command[j + 1])
//             {
//                 int fd = open(my_struct.my_command[j + 1], O_RDWR, 0777);
//                 if(fd == -1)
//                 {
//                     perror(my_struct.my_command[j + 1]);
//                     exit(1);
//                 }
//                 dup2(fd, STDIN_FILENO);
//                 my_struct.my_command[j] = 0;
//                 close(fd);
//             }
//         }
//         j++;
//     }
// }
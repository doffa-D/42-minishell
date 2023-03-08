/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:07:52 by nouakhro          #+#    #+#             */
/*   Updated: 2023/03/08 16:10:39 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <stdio.h>
#include <limits.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>



typedef struct s_all
{

    size_t  linght_path;
    char **my_path;
    char **my_all_path;
    char *my_curent_path;
  	char **my_command;
  	char *read_all;
    const char *commande_line;
}               t_all;


int main()
{
    
    t_all my_struct;
    int i = 0;
    int j;
    my_struct.my_path = 0;
    my_struct.my_curent_path = " ";
    while (1)
    {
        i = 0;
        j = 0;
        my_struct.commande_line = readline("escanour > ");
        my_struct.my_path = ft_split(getenv("PATH"), ':');
        printf("%s\n", getenv("HOME"));
        my_struct.my_command = ft_split(my_struct.commande_line, ' ');
        if(ft_strlen(my_struct.commande_line) > 0)
            add_history(my_struct.commande_line);
        i = fork();
        if(i == 0)
        {
			i = 0;
			j = 0;
        	while (my_struct.my_path[i])
            {
        	    my_struct.my_path[i] = ft_strjoin(my_struct.my_path[i], "/");
			    my_struct.my_path[i] = ft_strjoin(my_struct.my_path[i], my_struct.my_command[0]);
				    i++;
            }
            i = 0;
            while (my_struct.my_path[i])
            {
        	    if(!access(my_struct.my_path[i], F_OK))
                {
                 	j = 1;
                    break;
                }
                i++;
            }
            if(!ft_strncmp(my_struct.commande_line, "exit", ft_strlen("exit")) || \
	  		    !ft_strncmp(my_struct.commande_line, "quit", ft_strlen("quit")) || \
                !ft_strncmp(my_struct.commande_line, "q", ft_strlen("q")) ||\
                !ft_strncmp(my_struct.commande_line, "e", ft_strlen("e")))
                    break;
            if(j != 1)
            {
                printf("%s command not found\n", my_struct.my_command[0]);
                exit(0);
            }
            else
            {
            	if(!ft_strncmp(my_struct.my_command[0], "cd", ft_strlen("cd")))
					exit(1);
			    else if(!ft_strncmp(my_struct.commande_line, my_struct.commande_line, ft_strlen(my_struct.commande_line)))
                {
                    j = 1;
                    while (my_struct.my_command[j])
                    {
                        if(my_struct.my_command[j] && !ft_strncmp(my_struct.my_command[j], ">>", ft_strlen(my_struct.my_command[j])) && ft_strlen(my_struct.my_command[j]) == 2)
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
                        if(my_struct.my_command[j] && !ft_strncmp(my_struct.my_command[j],">", ft_strlen(my_struct.my_command[j])))
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
                        else if(my_struct.my_command[j] && !ft_strncmp(my_struct.my_command[j], "<", ft_strlen(my_struct.my_command[j])))
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
              	    execve(my_struct.my_path[i], my_struct.my_command, NULL);
                }
                
            }
               i = 0;
        }
        waitpid(-1, &i, 0);
        // close(fd);
        if(!ft_strncmp(my_struct.my_command[0], "cd", ft_strlen("cd")))
        {
            chdir(my_struct.my_command[1]);
            // loop++;
        }
        if(!ft_strncmp(my_struct.commande_line, "exit", ft_strlen("exit")) || \
	  	!ft_strncmp(my_struct.commande_line, "quit", ft_strlen("quit")) || \
        !ft_strncmp(my_struct.commande_line, "q", ft_strlen("q")) ||\
        !ft_strncmp(my_struct.commande_line, "e", ft_strlen("e")))
            break;
        // else if()
        // {
        //     // char buffer[10000];
        //     // read(0, buffer, 50);
        //     // printf("%s\n", buffer);
        // }
        // if(my_struct.my_path)
        // {
        //     while (my_struct.my_path[i])
        //     {
        //         free(my_struct.my_path[i]);
        //         i++;
        //     }
        //     free(my_struct.my_path);
        // }
    }
}

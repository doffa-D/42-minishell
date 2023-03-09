/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:07:52 by nouakhro          #+#    #+#             */
/*   Updated: 2023/03/09 16:08:01 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"


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
        my_struct.cmd = readline("escanour > ");
        my_struct.my_path = ft_split(getenv("PATH"), ':');
        my_struct.my_command = ft_split(my_struct.cmd, ' ');
        if(ft_strlen(my_struct.cmd) > 0)
            add_history(my_struct.cmd);
        i = fork();
        if(i == 0)
        {
        	get_the_path(my_struct);
            i = 0;
            // exit_the_program(my_struct);
            while (my_struct.my_path[i])
            {
        	    if(!access(my_struct.my_path[i], F_OK))
                {
                 	j = 1;
                    break;
                }
                i++;
            }
            if(j != 1)
            {
                printf("%s command not found\n", my_struct.my_command[0]);
                exit(0);
            }
            else
                exicut_commande(my_struct, i);
               i = 0;
        }
        waitpid(-1, &i, 0);
        if(!ft_strncmp(my_struct.my_command[0], "cd", ft_strlen("cd")))
        {
            if(ft_strlen(my_struct.cmd) == 2 || my_struct.my_command[1][0] == '~')
                chdir(getenv("HOME"));
            else
                chdir(my_struct.my_command[1]);
        }
        // exit_the_program(my_struct);
        free_all(my_struct);
    }
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:07:52 by nouakhro          #+#    #+#             */
/*   Updated: 2023/03/20 19:52:04 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void handler(int sig)
{
    if(sig == SIGINT)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
    }
    if(sig == SIGQUIT)
        return ;
}
int cd_commade(t_all my_struct, int loop)
{
    if(my_struct.my_command[0] && ft_strlen(my_struct.cmd) && !ft_strncmp(my_struct.my_command[0], "cd", ft_strlen(my_struct.my_command[0])))
    {
        printf("test[%s]\n", my_struct.my_command[1]);
        if((ft_strlen(my_struct.cmd) == 2 || my_struct.my_command[1][0] == '~'))
        {
            chdir(getenv("HOME"));
            if(my_struct.my_command[1] && my_struct.my_command[1][1] == '/' && my_struct.my_command[1][2])
                chdir(my_struct.my_command[1] + 2);
        }
        else if(ft_strlen(my_struct.cmd) == 2 || (my_struct.my_command[1][0] == '-' &&  my_struct.my_command[1][1]))
            chdir(my_struct.my_all_path[loop - (ft_atoi(&my_struct.my_command[1][1])) + 1]);
        else if(ft_strlen(my_struct.cmd) == 2 || my_struct.my_command[1][0] == '-')
            chdir(my_struct.my_all_path[loop]);
        else
            chdir(my_struct.my_command[1]);
        loop++;
        my_struct.i = 0;
    }
    return loop;
}
int somting_in_readline(t_all my_struct, char *cwd_path, char *old_path, int loop)
{
    int i = 0;
    int j = 0;
    my_struct.my_path = ft_split(getenv("PATH"), ':');
    my_struct.fix_cmd = ft_split(my_struct.cmd, ' ');
    fix_arg(&my_struct);
    add_history(my_struct.cmd);
    ft_bzero(cwd_path, sizeof(cwd_path));
    getcwd(cwd_path, sizeof(cwd_path));
    if(ft_strlen(cwd_path) > ft_strlen(old_path))
        my_struct.linght_path = ft_strlen(cwd_path);
    else if(ft_strlen(cwd_path) < ft_strlen(old_path))
        my_struct.linght_path = ft_strlen(old_path);
    
    if(my_struct.my_command[0] && !ft_strncmp(my_struct.my_command[0], "cd", ft_strlen(my_struct.my_command[0])) && ft_strncmp(cwd_path, old_path , my_struct.linght_path))
        my_struct.i = 1;
    if (loop != -1 && my_struct.i == 1)
    {
        my_struct.my_curent_path = ft_strjoin(my_struct.my_curent_path, cwd_path);
        my_struct.my_curent_path = ft_strjoin(my_struct.my_curent_path, " ");
        my_struct.my_all_path = ft_split(my_struct.my_curent_path, ' ');
        getcwd(old_path, sizeof(old_path));
    }
    j = 0;
    i = fork();
    if(i == 0)
    {
        j = 0;
    	if(!get_the_path(my_struct))
        {
            i = 0;
            i = 0;
            while (my_struct.my_path[i])
            {
                if(access(my_struct.my_path[i], F_OK) == 0)
                {
                    j = 1;
                    break;
                }
                i++;
            }
        }
        // if(i == 0)
        //     exit(0);
        if(j != 1)
        {
            if(my_struct.my_command[0])
                printf("%s command not found\n", my_struct.my_command[0]);
            else
                printf(" command not found\n");
            exit(0);
        }
        else
            exicut_commande(my_struct, i);
    }
    waitpid(-1, &i, 0);
    // loop = cd_commade(my_struct, loop);
    // free_all(my_struct);
    return loop;
}
int main()
{
    t_all my_struct;
    int i = 0;
    int loop = -1;
    char cwd_path[PATH_MAX];
    char old_path[PATH_MAX];
    my_struct.my_path = 0;
    my_struct.my_command = 0;
    my_struct.my_curent_path = " ";
    my_struct.i = 1;
    getcwd(cwd_path, sizeof(cwd_path));
    getcwd(old_path, sizeof(cwd_path));
    my_struct.my_curent_path = ft_strjoin(my_struct.my_curent_path, cwd_path);
    my_struct.my_curent_path = ft_strjoin(my_struct.my_curent_path, " ");
    my_struct.my_all_path = ft_split(my_struct.my_curent_path, ' ');
    signal(SIGINT, &handler);
    signal(SIGQUIT, &handler);
    while (1)
    {
        i = 0;
        my_struct.cmd = readline("escanour > ");
        if(!my_struct.cmd)
            exit(0);
        if(ft_strlen(my_struct.cmd) != 0)
            loop = somting_in_readline(my_struct, cwd_path, old_path, loop);
            
    }
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:07:52 by nouakhro          #+#    #+#             */
/*   Updated: 2023/04/17 20:41:50 by hdagdagu         ###   ########.fr       */
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
// int cd_commade(t_all my_struct)
// {
//     // printf("fdfvfd\n");
//     if(my_struct.my_command[0] && ft_strlen(my_struct.cmd) && !ft_strncmp(my_struct.my_command[0], "cd", ft_strlen(my_struct.my_command[0])))
//     {
//         // printf("test[%s]\n", my_struct.my_command[1]);
//         if((ft_strlen(my_struct.cmd) == 2 || my_struct.my_command[1][0] == '~'))
//         {
//             chdir(getenv("HOME"));
//             if(my_struct.my_command[1] && my_struct.my_command[1][1] == '/' && my_struct.my_command[1][2])
//                 chdir(my_struct.my_command[1] + 2);
//         }
//         // else if(ft_strlen(my_struct.cmd) == 2 || (my_struct.my_command[1][0] == '-' &&  my_struct.my_command[1][1]))
//         //     chdir(my_struct.my_all_path[loop - (ft_atoi(&my_struct.my_command[1][1])) + 1]);
//         // else if(ft_strlen(my_struct.cmd) == 2 || my_struct.my_command[1][0] == '-')
//         //     chdir(my_struct.my_all_path[loop]);
//         else
//             chdir(my_struct.my_command[1]);
//         my_struct.i = 0;
//     }
//     return 0;
// }
int somting_in_readline(t_all *my_struct)
{
    int i = 0;
    int j = 0;
    int checker = 0;
    my_struct->tmp_cmd = 0;
    my_struct->tmp_cmd = ft_strdup(my_struct->cmd);
    my_struct->the_commande = 0;
    while(my_struct->tmp_cmd[i])
    {

        char splite_char = ' ';
        checker = 0;
        while(my_struct->tmp_cmd[i] && my_struct->tmp_cmd[i] != splite_char)
        {
            if(my_struct->tmp_cmd[i] == 34 && !checker)
            {   
                splite_char = 34;
                checker = 1;
            }
            if(my_struct->tmp_cmd[i] == 39 && !checker)
            {
                splite_char = 39;
                checker = 1;
            }
            i++;
        }
        if(splite_char != ' ')
            i++;
        if(my_struct->tmp_cmd[i] == ' ')
        {
            if(!my_struct->the_commande)
                my_struct->the_commande = ft_calloc(1,1);
            my_struct->tmp_cmd[i] = 3;
            i++;

            my_struct->the_commande = ft_strjoin_v2(my_struct->the_commande, ft_substr(my_struct->tmp_cmd , j , i - j));
            j = i;
        }
        if(!my_struct->tmp_cmd[i])
        {
            if(!my_struct->the_commande)
                my_struct->the_commande = ft_calloc(1,1);
            my_struct->the_commande = ft_strjoin_v2(my_struct->the_commande, ft_substr(my_struct->tmp_cmd , j , i - j));

            break;
        }
    }

    my_struct->my_path = ft_split(getenv("PATH"), ':');
    my_struct->fix_cmd = ft_split(my_struct->the_commande, 3);
    free(my_struct->the_commande);
    free(my_struct->tmp_cmd);
    my_struct->the_commande = 0;
    my_struct->tmp_cmd = 0;
    // i = 0;
    // while(my_struct->fix_cmd[i])
    // {
    //     printf("[%s]\n", my_struct->fix_cmd[i]);
    //     i++;
    // }
    fix_arg(my_struct);
    add_history(my_struct->cmd);
    // ft_bzero(cwd_path, sizeof(cwd_path));
    // getcwd(cwd_path, sizeof(cwd_path));
    // if(ft_strlen(cwd_path) > ft_strlen(old_path))
    //     my_struct->linght_path = ft_strlen(cwd_path);
    // else if(ft_strlen(cwd_path) < ft_strlen(old_path))
    //     my_struct.linght_path = ft_strlen(old_path);
    
    // if(my_struct.my_command[0] && !ft_strncmp(my_struct.my_command[0], "cd", ft_strlen(my_struct.my_command[0])) && ft_strncmp(cwd_path, old_path , my_struct.linght_path))
    //     my_struct.i = 1;
    // if (loop != -1 && my_struct.i == 1)
    // {
    //     my_struct.my_curent_path = ft_strjoin(my_struct.my_curent_path, cwd_path);
    //     my_struct.my_curent_path = ft_strjoin(my_struct.my_curent_path, " ");
    //     my_struct.my_all_path = ft_split(my_struct.my_curent_path, ' ');
    //     getcwd(old_path, sizeof(old_path));
    // }
    // j = 0;
    int c_of_s = 0;
    // i = fork();
    // if(i == 0)
    // {
    //     j = 0;
    // 	if(!get_the_path(my_struct, 0))
    //     {
    //         i = 0;
    //         while (my_struct->my_path[i])
    //         {
    //             if(access(my_struct->my_path[i], F_OK) == 0)
    //             {
    //                 j = 1;
    //                 break;
    //             }
    //             i++;
    //         }
    //     }
    //     // if(j != 1)
    //     // {
    //     //     if(my_struct->each_cmd[c_of_s].cmd[0] && !ft_strchr(my_struct->each_cmd[c_of_s].cmd[0],'/'))
    //     //     {
    //     //         printf("%s: command not found\n", my_struct->each_cmd[c_of_s].cmd[0]);
    //     //         exit(127);
    //     //     }
    //     //     else if(ft_strchr(my_struct->each_cmd[c_of_s].cmd[0],'/'))
    //     //     {
    //     //         if(!chdir(my_struct->each_cmd[c_of_s].cmd[0]))
    //     //             printf("%s: is a directory\n", my_struct->each_cmd[c_of_s].cmd[0]);
    //     //         else
    //     //             printf("%s: No such file or directory\n", my_struct->each_cmd[c_of_s].cmd[0]);
    //     //     }
    //     //     exit(1);
    //     // }
    //     // else
        exicut_commande(my_struct, i, c_of_s);
    // }
    // waitpid(-1, &i, 0);
    // cd_commade(my_struct);
    // free_all(my_struct);
    return 0;
}

char    **charge_varible(char **src)
{
    char **dst;
    int i;
    i = 0;
    while(src[i])
        i++;
    dst = calloc(sizeof(char *),i + 1);
    i = 0;
    while(src[i])
    {
        dst[i] = ft_strdup(src[i]);
        i++;
    }
    return dst;
}

void    fill_linked_list(char **dst, t_list **list)
{
    int     i;

    i = 0;
    while (dst[i])
    {
        t_list  *new_node; 
        new_node = ft_lstnew(ft_strdup(dst[i]));
        ft_lstadd_back(list, new_node);
        i++;
    }
}

int main(int argc,char **argv,char **env)
{
    (void)argv;
    (void)argc;
    (void)env;
    t_all my_struct;
    my_struct.list = NULL;
    my_struct.the_commande = 0;
    // my_struct.export = env;
    fill_linked_list(env, &my_struct.list);
    // my_struct.export = charge_varible(env);
    // my_struct.env = charge_varible(env);
    // int i = 0;
    // int loop = -1;
    // char cwd_path[PATH_MAX];
    // char old_path[PATH_MAX];
    // my_struct.my_path = 0;
    // my_struct.my_command = 0;
    // my_struct.my_curent_path = " ";
    // my_struct.i = 1;
    // getcwd(cwd_path, sizeof(cwd_path));
    // getcwd(old_path, sizeof(cwd_path));
    // my_struct.my_curent_path = ft_strjoin(my_struct.my_curent_path, cwd_path);
    // my_struct.my_curent_path = ft_strjoin(my_struct.my_curent_path, " ");
    // my_struct.my_all_path = ft_split(my_struct.my_curent_path, ' ');
    signal(SIGINT, &handler);
    signal(SIGQUIT, &handler);
    int i = 0;
    while (1)
    {
        my_struct.cmd = readline("escanour > ");
        if(!my_struct.cmd)
            exit(0);
        
        if(ft_strlen(my_struct.cmd) != 0)
            somting_in_readline(&my_struct);
        i++;
    }
}
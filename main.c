/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:07:52 by nouakhro          #+#    #+#             */
/*   Updated: 2023/04/26 00:46:36 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	handler(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		rl_replace_line("", 0);
// 		printf("\n");
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// 	if (sig == SIGQUIT)
// 		return ;
// }




int	somting_in_readline(t_all *my_struct)
{
	int		i;
	int		j;
	int		c_of_s = 0;

	i = 0;
	j = 0;
	parccen(my_struct);
	i = 0;
	my_struct->fix_cmd = ft_split(my_struct->the_commande, 3);
	// while(my_struct->fix_cmd[i])
	// {
	// 	printf("[%s]\n", my_struct->fix_cmd[i]);
	// 	i++;
	// }
	free(my_struct->the_commande);
	free(my_struct->tmp_cmd);
	add_history(my_struct->cmd);
	my_struct->the_commande = 0;
	my_struct->tmp_cmd = 0;
	i = fix_arg(my_struct);
	if(i == 258)
		return 258;
	if(i == 2)
		return 2;
	c_of_s = 0;
	if(my_struct->number_of_pipes == 1)
	{
		c_of_s = builtins(my_struct, c_of_s);
		if(c_of_s == 1)
			return 0;
		if(c_of_s == -1)
			return 1;
	}
	my_struct->my_path = ft_split(my_getenv(my_struct->list, "PATH"), ':');
	if(!my_struct->my_path[0])
	{
		printf("minishell: No such file or directory\n");
		return 127;
	}
	int pipe_n[my_struct->number_of_pipes][2];
	while(my_struct->number_of_pipes > 0)
	{
		if(my_struct->number_of_pipes > 1)
			pipe(pipe_n[c_of_s]);
		i = fork();
		if (i == 0)
		{
			pipe_and_rederaction(j, c_of_s, my_struct, pipe_n);
			j = 0;
			if (!get_the_path(my_struct, c_of_s))
			{
				i = 0;
				while (my_struct->my_path && my_struct->my_path[i])
				{
					if (access(my_struct->my_path[i], F_OK) == 0)
					{
						j = 1;
						break ;
					}
					i++;
				}
			}
			if (j != 1)
			{
				if (my_struct->each_cmd[c_of_s].cmd[0]
					&& (!ft_strchr(my_struct->each_cmd[c_of_s].cmd[0], '/')))
				{
					ft_putstr_fd("minishell: command not found\n", 2);
					// printf("minishell %s: command not found\n",
					// 		my_struct->each_cmd[c_of_s].cmd[0]);
					exit(127);
				}
				else if (my_struct->each_cmd[c_of_s].cmd[0] && ft_strchr(my_struct->each_cmd[c_of_s].cmd[0], '/'))
				{
					if (!chdir(my_struct->each_cmd[c_of_s].cmd[0]))
					{
						ft_putstr_fd("minishell: is a directory\n", 2);
						// printf("minishell %s: is a directory\n",
						// 		my_struct->each_cmd[c_of_s].cmd[0]);
						exit(126);
					}
					else
					{
						ft_putstr_fd("minishell: No such file or directory\n", 2);
						// printf("minishell %s: No such file or directory\n",
						// 	my_struct->each_cmd[c_of_s].cmd[0]);
						exit(127);
					}
				}
			}
			else
				exicut_commande(my_struct, i, c_of_s, pipe_n[c_of_s]);
		}
		waitpid(-1, &my_struct->exit_status, 0);
		my_struct->exit_status = my_struct->exit_status >> 8;
		if(my_struct->number_of_pipes > 1)
			close(pipe_n[c_of_s][1]);
		my_struct->number_of_pipes--;
		c_of_s++;
	}
	return (my_struct->exit_status);
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
	my_struct.exit_status = 0;
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
    // signal(SIGINT, &handler);
    // signal(SIGQUIT, &handler);
    int i = 0;
    while (1)
    {
        my_struct.cmd = readline("escanour > ");
        if(!my_struct.cmd)
            exit(my_struct.exit_status);
        if(ft_strlen(my_struct.cmd) != 0)
            my_struct.exit_status = somting_in_readline(&my_struct);
        i++;
    }
}

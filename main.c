/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:07:52 by nouakhro          #+#    #+#             */
/*   Updated: 2023/04/24 17:47:40 by nouakhro         ###   ########.fr       */
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

int cd_commade(t_all *my_struct)
{
	if(my_struct->each_cmd[0].cmd[1] && access(my_struct->each_cmd[0].cmd[1], F_OK) == -1)
	{
		printf("minishell: %s: %s: No such file or directory\n", my_struct->each_cmd[0].cmd[0], my_struct->each_cmd[0].cmd[1]);
		return 1;
	}
    if((ft_strlen(my_struct->each_cmd[0].cmd[0]) == 2 && my_struct->each_cmd[0].cmd[1] && (my_struct->each_cmd[0].cmd[1][0] == '~' \
	|| my_struct->each_cmd[0].cmd[1][1] == '/')))
    {
		if(my_struct->each_cmd[0].cmd[1][0] == '~')
        	chdir(my_getenv(my_struct->list,"HOME"));
		if(my_struct->each_cmd[0].cmd[1] && my_struct->each_cmd[0].cmd[1][1] == '/')
		{
            chdir(my_struct->each_cmd[0].cmd[1]);
		}
    }
	if(ft_strlen(my_struct->each_cmd[0].cmd[0]) == 2 && !my_struct->each_cmd[0].cmd[1])
        chdir(my_getenv(my_struct->list,"HOME"));
    else
        chdir(my_struct->each_cmd[0].cmd[1]);
    return (0);
}

int builtins(t_all *my_struct, int c_of_s)
{
	if(my_struct->each_cmd[0].cmd[0] && ft_strlen(my_struct->each_cmd[0].cmd[0]) \
	&& !ft_strncmp(my_struct->each_cmd[0].cmd[0], "cd", ft_strlen(my_struct->each_cmd[0].cmd[0])))
	{
		if(cd_commade(my_struct))
			return (-1);
		return (1);
	}
	if (my_struct->each_cmd[0].cmd[0] && !ft_strncmp(my_struct->each_cmd[c_of_s].cmd[0], "echo", ft_strlen("echo")+1))
	{
		echo_command(my_struct,c_of_s);
		return (1);
	}
	if (my_struct->each_cmd[0].cmd[0] && !ft_strncmp(my_struct->each_cmd[c_of_s].cmd[0], "export", ft_strlen("export")+1))
	{
		export_command(my_struct,c_of_s);
		return (1);
	}
	else if (my_struct->each_cmd[0].cmd[0] && !ft_strncmp(my_struct->each_cmd[c_of_s].cmd[0], "env", ft_strlen("env")+1))
	{
		env_command(my_struct->list);
		return (1);
	}
	else if (my_struct->each_cmd[0].cmd[0] && !ft_strncmp(my_struct->each_cmd[c_of_s].cmd[0], "unset", ft_strlen("unset")+1))
	{
		unset_command(my_struct,c_of_s);
		return (1);
	}
	return (0);
}

int	somting_in_readline(t_all *my_struct)
{
	int		i;
	int		j;
	int		checker;
	char	splite_char;
	int		c_of_s = 0;

	i = 0;
	j = 0;
	checker = 0;
	my_struct->tmp_cmd = 0;
	my_struct->tmp_cmd = ft_strdup(my_struct->cmd);
	my_struct->the_commande = 0;
	while (my_struct->tmp_cmd[i])
	{
		splite_char = ' ';
		checker = 0;
		while (my_struct->tmp_cmd[i] && my_struct->tmp_cmd[i] != splite_char)
		{
			if (my_struct->tmp_cmd[i] == 34 && !checker)
			{
				splite_char = 34;
				checker = 1;
			}
			if (my_struct->tmp_cmd[i] == 39 && !checker)
			{
				splite_char = 39;
				checker = 1;
			}
			i++;
		}
		if (splite_char != ' ' && my_struct->tmp_cmd[i])
			i++;
		if (my_struct->tmp_cmd[i] == ' ')
		{
			if (!my_struct->the_commande)
				my_struct->the_commande = ft_calloc(1, 1);
			my_struct->tmp_cmd[i] = 3;
			i++;
			my_struct->the_commande = ft_strjoin_v2(my_struct->the_commande,
					ft_substr(my_struct->tmp_cmd, j, i - j));
			j = i;
		}
		if (!my_struct->tmp_cmd[i])
		{
			if (!my_struct->the_commande)
				my_struct->the_commande = ft_calloc(1, 1);
			my_struct->the_commande = ft_strjoin_v2(my_struct->the_commande,
					ft_substr(my_struct->tmp_cmd, j, i - j));
			break ;
		}
	}
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
	i = 0;
	if(fix_arg(my_struct) == -1)
		return 127;
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
	int pipe_n[my_struct->number_of_pipes][2];
	while(my_struct->number_of_pipes > 0)
	{
		if(my_struct->number_of_pipes > 1)
			pipe(pipe_n[c_of_s]);
		i = fork();
		if (i == 0)
		{
			if(c_of_s > 0)
			{
        		close(pipe_n[c_of_s - 1][1]);
				dup2(pipe_n[c_of_s - 1][0], STDIN_FILENO);
        		close(pipe_n[c_of_s - 1][0]);
			}
			if(my_struct->number_of_pipes > 1)
			{
				close(pipe_n[c_of_s][0]);
				dup2(pipe_n[c_of_s][1], STDOUT_FILENO);
				close(pipe_n[c_of_s][1]);
			}
			if(my_struct->each_cmd[c_of_s].files)
				check_rediractions(my_struct, c_of_s);
			j = builtins(my_struct, c_of_s);
			if(j == 1)
				exit(0);
			if(j == -1)
			exit(1);
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
					printf("minishell %s: command not found\n",
							my_struct->each_cmd[c_of_s].cmd[0]);
					exit(127);
				}
				else if (my_struct->each_cmd[c_of_s].cmd[0] && ft_strchr(my_struct->each_cmd[c_of_s].cmd[0], '/'))
				{
					if (!chdir(my_struct->each_cmd[c_of_s].cmd[0]))
						printf("minishell %s: is a directory\n",
								my_struct->each_cmd[c_of_s].cmd[0]);
					else
					{
						printf("minishell %s: No such file or directory\n",
							my_struct->each_cmd[c_of_s].cmd[0]);
					}
				}
				exit(1);
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

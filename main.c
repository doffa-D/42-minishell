/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:07:52 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/04 01:23:47 by nouakhro         ###   ########.fr       */
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

void free_all_v2(int num,t_all *my_struct)
{
	int i = 0;
	int j = 0;
	if(num == 1)
	{
		while(my_struct->my_path[i])
		{
			free(my_struct->my_path[i]);
			i++;
		}
		free(my_struct->my_path);
	}
	i = 0;
	j = 0;
	while(my_struct->each_cmd[i].files)
	{
		j = 0;
		while (my_struct->each_cmd[i].files[j].files)
		{
			free(my_struct->each_cmd[i].files[j].files);
			j++;
		}
		free(my_struct->each_cmd[i].files);
		i++;
	}
	i = 0;
	while(my_struct->each_cmd[i].cmd)
	{
		j = 0;
		while (my_struct->each_cmd[i].cmd[j])
		{
			free(my_struct->each_cmd[i].cmd[j]);
			j++;
		}
		free(my_struct->each_cmd[i].cmd);
		i++;
	}
	free(my_struct->each_cmd);
}


int cd_commade(t_all *my_struct, int c_of_s)
{
	int pid = 0;
	if(my_struct->each_cmd[c_of_s].cmd[1] && access(my_struct->each_cmd[c_of_s].cmd[1], F_OK) == -1)
	{
		dup2(2, 1);
		ft_putstr_fd("minishell: No such file or directory\n", 2);
		return 1;
	}
    if((ft_strlen(my_struct->each_cmd[c_of_s].cmd[0]) == 2 && my_struct->each_cmd[c_of_s].cmd[1] && (my_struct->each_cmd[c_of_s].cmd[1][0] == '~' \
	|| my_struct->each_cmd[c_of_s].cmd[1][1] == '/')))
    {
		if(my_struct->each_cmd[c_of_s].cmd[1][0] == '~')
		{

        	chdir(my_getenv(my_struct->list,"HOME", 0));

		}
		if(my_struct->each_cmd[c_of_s].cmd[1] && my_struct->each_cmd[c_of_s].cmd[1][1] == '/')
		{
            chdir(my_struct->each_cmd[c_of_s].cmd[1]);
		}
    }
	if(ft_strlen(my_struct->each_cmd[c_of_s].cmd[0]) == 2 && !my_struct->each_cmd[c_of_s].cmd[1])
	{
        if(chdir(my_getenv(my_struct->list,"HOME", 0)) == -1)
		{
			pid = fork();
			if(pid == 0)
			{
				dup2(2, 1);
				printf("minishell: %s: HOME not set\n", my_struct->each_cmd[c_of_s].cmd[0]);
				exit(1);
			}
			wait(&pid);
			return 1;
		}
	}
    else
        chdir(my_struct->each_cmd[c_of_s].cmd[1]);
    return (0);
}

int builtins(t_all *my_struct, int c_of_s)
{
	int i = 0;
	if(my_struct->each_cmd[c_of_s].cmd[0] && ft_strlen(my_struct->each_cmd[c_of_s].cmd[0]) \
	 &&!ft_strncmp(my_struct->each_cmd[c_of_s].cmd[0], "cd", ft_strlen(my_struct->each_cmd[c_of_s].cmd[0])))
	{
		if(cd_commade(my_struct, c_of_s))
			return (-1);
		return (1);
	}
	if (my_struct->each_cmd[c_of_s].cmd[0] && !ft_strncmp(my_struct->each_cmd[c_of_s].cmd[0], "export", ft_strlen("export")+1))
	{
		my_struct->check = 0;
		export_command(my_struct,c_of_s);

		if(my_struct->check == 1)
			return (-1);
		return (1);
	}
	else if (my_struct->each_cmd[c_of_s].cmd[0] && !ft_strncmp(my_struct->each_cmd[c_of_s].cmd[0], "env", ft_strlen("env")+1))
	{
		env_command(my_struct->list);
		return (1);
	}
	else if (my_struct->each_cmd[c_of_s].cmd[0] && !ft_strncmp(my_struct->each_cmd[c_of_s].cmd[0], "unset", ft_strlen("unset")+1))
	{
		unset_command(my_struct,c_of_s);
		return (1);
	}
	else if (my_struct->each_cmd[c_of_s].cmd && my_struct->each_cmd[c_of_s].cmd[0] && !ft_strncmp(my_struct->each_cmd[c_of_s].cmd[0], "exit", ft_strlen("exit")))
	{
		
		if(my_struct->each_cmd[c_of_s].cmd && my_struct->each_cmd[c_of_s].cmd[1])
		{
			while (my_struct->each_cmd[c_of_s].cmd[1][i])
			{
				if(ft_isalpha(my_struct->each_cmd[c_of_s].cmd[1][i]))
				{
					dup2(2, 1);
					printf("minishell: exit: %s: numeric argument required\n", my_struct->each_cmd[c_of_s].cmd[1]);
					exit(255);
				}
				i++;
			}
			if(!my_struct->each_cmd[c_of_s].cmd[2])
				exit(ft_atoi(my_struct->each_cmd[c_of_s].cmd[1]));
		}
		if(my_struct->each_cmd[c_of_s].cmd && my_struct->each_cmd[c_of_s].cmd[1] && my_struct->each_cmd[c_of_s].cmd[2])
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			exit(1);
		}
		exit(my_struct->exit_status);
	}

	return (0);
}
int	somting_in_readline(t_all *my_struct)
{
	int		i;
	int		j;
	int		c_of_s = 0;
	int		checker;
	char	splite_char;
	i = 0;
	j = 0;
	my_struct->tmp_cmd = 0;
	my_struct->tmp_cmd = ft_strtrim(my_struct->cmd, " ");
	if(!*my_struct->tmp_cmd)
		return my_struct->exit_status;
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
	if(i == 1)
		return 1;
	c_of_s = 0;
	if(my_struct->number_of_pipes == 1)
	{
		// if(my_struct->each_cmd[c_of_s].files)
		// 	check_rediractions(my_struct, c_of_s, 1);
		c_of_s = builtins(my_struct, c_of_s);
		if(c_of_s == 1)
		{
			free_all_v2(0 ,my_struct);
			return 0;
		}
		if(c_of_s == -1)
		{
			free_all_v2(0, my_struct);
			return 1;
		}
	}
	char *str = my_getenv(my_struct->list, "PATH", 0);
	my_struct->my_path = ft_split(str, ':');
	free(str);
	if(!my_struct->my_path[0])
	{
		i = fork();
		if(i == 0)
		{
			dup2(2, 1);
			printf("minishell: %s: No such file or directory\n", my_struct->each_cmd[c_of_s].cmd[0]);
			exit(1);
		}
		wait(&i);
		return 127;
	}
	int *pid = malloc(my_struct->number_of_pipes * sizeof(int));
	c_of_s = 0;
	int pipe_n[my_struct->number_of_pipes][2];
	while(my_struct->number_of_pipes > 0)
	{
		if(my_struct->number_of_pipes > 1)
			pipe(pipe_n[c_of_s]);
		i = fork();
		if (i == -1)
		{
			perror("fork");
			exit(1);
		}
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
			if (my_struct->each_cmd[0].cmd[0] && \
			!ft_strncmp(my_struct->each_cmd[c_of_s].cmd[0], "echo", ft_strlen("echo")+1))
			{
				echo_command(my_struct,c_of_s);
				exit(0);
			}
			if (my_struct->each_cmd[c_of_s].cmd[0] && \
			!ft_strncmp(my_struct->each_cmd[c_of_s].cmd[0], "pwd", ft_strlen("pwd")+1))
			{
				pwd_command();
				exit(0);
			}
			j = builtins(my_struct, c_of_s);
			if(j == 1)
				exit(0);
			if(j == -1)
				exit(1);
			j = 0;
			if (my_struct->each_cmd[c_of_s].cmd[0] && \
			!ft_strchr(my_struct->each_cmd[c_of_s].cmd[0], '/') && !get_the_path(my_struct, c_of_s))
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
			else
			{
				if (my_struct->each_cmd[c_of_s].cmd[0] && access(my_struct->each_cmd[c_of_s].cmd[0], F_OK) == 0)
					j = 1;
			}
			if (j != 1)
			{
				if (my_struct->each_cmd[c_of_s].cmd[0]
					&& (!ft_strchr(my_struct->each_cmd[c_of_s].cmd[0], '/')))
				{
					dup2(2, 1);
					printf("minishell: %s: command not found\n", my_struct->each_cmd[c_of_s].cmd[0]);
					exit(127);
				}
				else if (my_struct->each_cmd[c_of_s].cmd[0] && ft_strchr(my_struct->each_cmd[c_of_s].cmd[0], '/'))
				{
					if (!chdir(my_struct->each_cmd[c_of_s].cmd[0]))
					{
						dup2(2, 1);
						printf("minishell: %s: Is a directory\n", my_struct->each_cmd[c_of_s].cmd[0]);
						exit(126);
					}
					else
					{
						dup2(2, 1);
						printf("minishell: %s: No such file or directory\n", my_struct->each_cmd[c_of_s].cmd[0]);
						exit(127);
					}
				}
			}
			else
				exicut_commande(my_struct, i, c_of_s, pipe_n[c_of_s]);
		}
		else
			pid[c_of_s] = i;
		if(my_struct->number_of_pipes > 1)
			close(pipe_n[c_of_s][1]);
		my_struct->number_of_pipes--;
		c_of_s++;
	}
	i = 0;
	while (i < c_of_s - 1)
	{
		close(pipe_n[i][1]);
		close(pipe_n[i][0]);
		i++;
	}
	i = 0;
	while(i < c_of_s)
	{
		waitpid(pid[i], &my_struct->exit_status, 0);
		my_struct->exit_status = my_struct->exit_status >> 8;
		i++;
	}
	free(pid);
	free_all_v2(1, my_struct);
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
    t_all my_struct;
    my_struct.list = NULL;
    fill_linked_list(env, &my_struct.list);
	my_struct.exit_status = 0;
    int i = 0;
    while (1)
    {
		my_struct.the_commande = 0;
        my_struct.cmd = readline("escanour > ");
        if(!my_struct.cmd)
            exit(my_struct.exit_status);
        if(ft_strlen(my_struct.cmd) != 0)
            my_struct.exit_status = somting_in_readline(&my_struct);
		free(my_struct.cmd);
        i++;
    }
}
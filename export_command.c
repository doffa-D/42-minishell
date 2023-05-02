/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:02:29 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/05/02 16:23:01 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_export_error(char *cmd,t_all *my_struct)
{
	int pid;
	if ((cmd[0] == '=' && !cmd[1]) || cmd[0] == '=')
	{
		
		pid = fork();
		if(pid == 0)
		{
			dup2(2, 1);
			printf("minishell: not a valid identifier\n");
			exit(1);
		}
		wait(&pid);
		my_struct->check = 1;
		return (2);
	}
	else if (mini_check_export(cmd, 1) == 1)
	{
		pid = fork();
		if(pid == 0)
		{
			dup2(2, 1);
			printf("minishell: not a valid identifier\n");
			exit(1);
		}
		wait(&pid);
		my_struct->check = 1;
		return (2);
	}
	return (1);
}

int	handle_export(char *cmd, int print, t_list *list,t_all *my_struct)
{
	int pid;
	print = check_export_error(cmd,my_struct);
	if (print == 0)
		return (print);
	else if (cmd && cmd[ft_strlen(cmd) - 1] != '=' && ft_strchr(cmd, '=') &&!duplicate_check_export(list, cmd) && print != 2)
	{
		string_dakche(list);
		if (replace_varible(list, cmd) == 0)
			add_node_back(cmd, &list);
	}
	else if (cmd[ft_strlen(cmd) - 1] == '=' && !duplicate_check_export(list, cmd) && print != 2)
	{
		if (mini_checker_export(list, cmd) == 0)
			add_node_back(cmd, &list);
	}
	else if (!ft_strchr(cmd, '=' && !duplicate_check_export(list, cmd)) && check_varible_if_have(list, cmd) == 0 && print != 2)
	{
		if (mini_check_export(cmd, 0) == 1)
		{
			pid = fork();
			if(pid == 0)
			{
				dup2(2, 1);
				printf("export: `%s': not a valid identifier\n", cmd);
				exit(1);
			}
			wait(&pid);
		}
		else
			add_node_back(cmd, &list);
	}
	return (print);
}

void	export_command(t_all *my_struct, int c_of_s)
{
	int		i;
	int		print;
	t_list	*ptr;

	i = 1;
	ptr = my_struct->list;
	print = 1;
	while (my_struct->each_cmd[c_of_s].cmd[i])
	{
		print = handle_export(my_struct->each_cmd[c_of_s].cmd[i], print, my_struct->list,my_struct);
		if (print == 0)
			break ;
		i++;
	}
	if (print == 1 && !my_struct->each_cmd[c_of_s].cmd[1])
	{
		print_export(my_struct->list);
	}
	my_struct->list = ptr;
}

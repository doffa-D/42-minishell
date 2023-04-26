/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 00:36:57 by nouakhro          #+#    #+#             */
/*   Updated: 2023/04/26 00:38:47 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

int cd_commade(t_all *my_struct)
{
	if(my_struct->each_cmd[0].cmd[1] && access(my_struct->each_cmd[0].cmd[1], F_OK) == -1)
	{
		ft_putstr_fd("minishell: No such file or directory\n", 2);
		return 1;
	}
    if((ft_strlen(my_struct->each_cmd[0].cmd[0]) == 2 && my_struct->each_cmd[0].cmd[1] && (my_struct->each_cmd[0].cmd[1][0] == '~' \
	|| my_struct->each_cmd[0].cmd[1][1] == '/')))
    {
		if(my_struct->each_cmd[0].cmd[1][0] == '~')
		{

        	chdir(my_getenv(my_struct->list,"HOME"));

		}
		if(my_struct->each_cmd[0].cmd[1] && my_struct->each_cmd[0].cmd[1][1] == '/')
		{
            chdir(my_struct->each_cmd[0].cmd[1]);
		}
    }
	if(ft_strlen(my_struct->each_cmd[0].cmd[0]) == 2 && !my_struct->each_cmd[0].cmd[1])
	{
        if(chdir(my_getenv(my_struct->list,"HOME")) == -1)
		{
			printf("minishell: cd: HOME not set\n");
			return 1;
		}
	}
    else
	{
        chdir(my_struct->each_cmd[0].cmd[1]);
	}
    return (0);
}

int builtins(t_all *my_struct, int c_of_s)
{
	if(my_struct->each_cmd[c_of_s].cmd[0] && ft_strlen(my_struct->each_cmd[c_of_s].cmd[0]) \
	 &&!ft_strncmp(my_struct->each_cmd[c_of_s].cmd[0], "cd", ft_strlen(my_struct->each_cmd[c_of_s].cmd[0])))
	{
		if(cd_commade(my_struct))
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
	else if (my_struct->each_cmd[c_of_s].cmd[0] && !ft_strncmp(my_struct->each_cmd[c_of_s].cmd[0], "pwd", ft_strlen("pwd")+1))
	{
		pwd_command();
		return (1);
	}
	else if (my_struct->each_cmd[c_of_s].cmd[0] && !ft_strncmp(my_struct->each_cmd[c_of_s].cmd[0], "exit", ft_strlen("exit")))
	{
		exit(ft_atoi(my_struct->each_cmd[c_of_s].cmd[1]));
	}
	return (0);
}
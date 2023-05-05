/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 00:36:57 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/05 20:29:34 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

// int cd_commade(t_all *_struct)
// {
// 	if(_struct->each_cmd[0].cmd[1] && access(_struct->each_cmd[0].cmd[1], F_OK) == -1)
// 	{
// 		ft_putstr_fd("minishell: No such file or directory\n", 2);
// 		return 1;
// 	}
//     if((ft_strlen(_struct->each_cmd[0].cmd[0]) == 2 && _struct->each_cmd[0].cmd[1] && (_struct->each_cmd[0].cmd[1][0] == '~' \
// 	|| _struct->each_cmd[0].cmd[1][1] == '/')))
//     {
// 		if(_struct->each_cmd[0].cmd[1][0] == '~')
// 		{

//         	chdir(my_getenv(_struct->list,"HOME"));

// 		}
// 		if(_struct->each_cmd[0].cmd[1] && _struct->each_cmd[0].cmd[1][1] == '/')
// 		{
//             chdir(_struct->each_cmd[0].cmd[1]);
// 		}
//     }
// 	if(ft_strlen(_struct->each_cmd[0].cmd[0]) == 2 && !_struct->each_cmd[0].cmd[1])
// 	{
//         if(chdir(my_getenv(_struct->list,"HOME")) == -1)
// 		{
// 			printf("minishell: cd: HOME not set\n");
// 			return 1;
// 		}
// 	}
//     else
// 	{
//         chdir(_struct->each_cmd[0].cmd[1]);
// 	}
//     return (0);
// }

// int builtins(t_all *_struct, int c_of_s)
// {
// 	if(_struct->each_cmd[c_of_s].cmd[0] && ft_strlen(_struct->each_cmd[c_of_s].cmd[0]) \
// 	 &&!ft_strncmp(_struct->each_cmd[c_of_s].cmd[0], "cd", ft_strlen(_struct->each_cmd[c_of_s].cmd[0])))
// 	{
// 		if(cd_commade(_struct))
// 			return (-1);
// 		return (1);
// 	}
// 	if (_struct->each_cmd[c_of_s].cmd[0] && !ft_strncmp(_struct->each_cmd[c_of_s].cmd[0], "export", ft_strlen("export")+1))
// 	{
// 		_struct->check = 0;
// 		export_command(_struct,c_of_s);
// 		if(_struct->check == 1)
// 			return (-1);
// 		return (1);
// 	}
// 	else if (_struct->each_cmd[c_of_s].cmd[0] && !ft_strncmp(_struct->each_cmd[c_of_s].cmd[0], "env", ft_strlen("env")+1))
// 	{
// 		env_command(_struct->list);
// 		return (1);
// 	}
// 	else if (_struct->each_cmd[c_of_s].cmd[0] && !ft_strncmp(_struct->each_cmd[c_of_s].cmd[0], "unset", ft_strlen("unset")+1))
// 	{
// 		unset_command(_struct,c_of_s);
// 		return (1);
// 	}
// 	else if (_struct->each_cmd[c_of_s].cmd[0] && !ft_strncmp(_struct->each_cmd[c_of_s].cmd[0], "pwd", ft_strlen("pwd")+1))
// 	{
// 		pwd_command();
// 		return (1);
// 	}
// 	else if (_struct->each_cmd[c_of_s].cmd[0] && !ft_strncmp(_struct->each_cmd[c_of_s].cmd[0], "exit", ft_strlen("exit")))
// 	{
// 		exit(ft_atoi(_struct->each_cmd[c_of_s].cmd[1]));
// 	}
// 	return (0);
// }
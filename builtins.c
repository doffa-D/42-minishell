/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 00:36:57 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/06 19:47:24 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

// int cd_commade()
// {
// 	if(g_struct.each_cmd[0].cmd[1] && access(g_struct.each_cmd[0].cmd[1], F_OK) == -1)
// 	{
// 		ft_putstr_fd("minishell: No such file or directory\n", 2);
// 		return 1;
// 	}
//     if((ft_strlen(g_struct.each_cmd[0].cmd[0]) == 2 && g_struct.each_cmd[0].cmd[1] && (g_struct.each_cmd[0].cmd[1][0] == '~' \
// 	|| g_struct.each_cmd[0].cmd[1][1] == '/')))
//     {
// 		if(g_struct.each_cmd[0].cmd[1][0] == '~')
// 		{

//         	chdir(my_getenv(g_struct.list,"HOME"));

// 		}
// 		if(g_struct.each_cmd[0].cmd[1] && g_struct.each_cmd[0].cmd[1][1] == '/')
// 		{
//             chdir(g_struct.each_cmd[0].cmd[1]);
// 		}
//     }
// 	if(ft_strlen(g_struct.each_cmd[0].cmd[0]) == 2 && !g_struct.each_cmd[0].cmd[1])
// 	{
//         if(chdir(my_getenv(g_struct.list,"HOME")) == -1)
// 		{
// 			printf("minishell: cd: HOME not set\n");
// 			return 1;
// 		}
// 	}
//     else
// 	{
//         chdir(g_struct.each_cmd[0].cmd[1]);
// 	}
//     return (0);
// }

// int builtins(int c_of_s)
// {
// 	if(g_struct.each_cmd[c_of_s].cmd[0] && ft_strlen(g_struct.each_cmd[c_of_s].cmd[0]) \
// 	 &&!ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "cd", ft_strlen(g_struct.each_cmd[c_of_s].cmd[0])))
// 	{
// 		if(cd_commade())
// 			return (-1);
// 		return (1);
// 	}
// 	if (g_struct.each_cmd[c_of_s].cmd[0] && !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "export", ft_strlen("export")+1))
// 	{
// 		g_struct.check = 0;
// 		export_command(_struct,c_of_s);
// 		if(g_struct.check == 1)
// 			return (-1);
// 		return (1);
// 	}
// 	else if (g_struct.each_cmd[c_of_s].cmd[0] && !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "env", ft_strlen("env")+1))
// 	{
// 		env_command(g_struct.list);
// 		return (1);
// 	}
// 	else if (g_struct.each_cmd[c_of_s].cmd[0] && !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "unset", ft_strlen("unset")+1))
// 	{
// 		unset_command(_struct,c_of_s);
// 		return (1);
// 	}
// 	else if (g_struct.each_cmd[c_of_s].cmd[0] && !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "pwd", ft_strlen("pwd")+1))
// 	{
// 		pwd_command();
// 		return (1);
// 	}
// 	else if (g_struct.each_cmd[c_of_s].cmd[0] && !ft_strncmp(g_struct.each_cmd[c_of_s].cmd[0], "exit", ft_strlen("exit")))
// 	{
// 		exit(ft_atoi(g_struct.each_cmd[c_of_s].cmd[1]));
// 	}
// 	return (0);
// }
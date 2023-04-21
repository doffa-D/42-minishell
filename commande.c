/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commande.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:19:24 by nouakhro          #+#    #+#             */
/*   Updated: 2023/04/20 15:27:56 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exicut_commande(t_all *my_struct, int i, int c_of_s)
{
	if (!ft_strncmp(my_struct->each_cmd[c_of_s].cmd[0], "cd", ft_strlen("cd")+1))
		exit(1);
	else if (!ft_strncmp(my_struct->each_cmd[c_of_s].cmd[0], "echo", ft_strlen("echo")+1))
		exicut_echo(my_struct,c_of_s);
	else if (!ft_strncmp(my_struct->each_cmd[c_of_s].cmd[0], "export", ft_strlen("export")+1))
		export_command(my_struct,c_of_s);
	else if (!ft_strncmp(my_struct->each_cmd[c_of_s].cmd[0], "env", ft_strlen("env")+1))
		env_command(my_struct->list);
	else if (!ft_strncmp(my_struct->each_cmd[c_of_s].cmd[0], "unset", ft_strlen("unset")+1))
		unset_command(my_struct,c_of_s);
	else if (!ft_strncmp(my_struct->cmd, my_struct->cmd,ft_strlen(my_struct->cmd)))
	{
		check_rediractions(my_struct, c_of_s);
		execve(my_struct->my_path[i], my_struct->each_cmd[c_of_s].cmd, NULL);
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commande.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:19:24 by nouakhro          #+#    #+#             */
/*   Updated: 2023/04/16 22:06:17 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_command(t_all *my_struct,int c_of_s)
{
	// int i;
	// i = 0;
	// char **dst;
	// while(my_struct->env[i])
	// {
	// 	i++;
	// }
	// printf("%d\n",i);
	// dst = calloc(sizeof(char *), i + 2);
	// i = 0;
	// while(my_struct->env[i])
	// {
	// 	dst[i] = ft_strdup(my_struct->env[i]);
	// 	i++;
	// }
	// if(ft_strchr(my_struct->my_command[1],'=') && my_struct->my_command[1])
	// {
	// 	dst[i] = ft_strdup(my_struct->my_command[1]);
	// }
	// i = -1;
	// while(my_struct->env[++i])
	// 	free(my_struct->env[i]);
	// free(my_struct->env);
	// my_struct->env = calloc(sizeof(char *), i + 5);
	// i = 0;
	// while(dst[i])
	// {
	// 	my_struct->env[i] = ft_strdup(dst[i]);
	// 	free(dst[i]);
	// 	i++;
	// }
	// i = -1;
	// while(my_struct->my_command[++i])
	// 	printf("ssss[%s]\n",my_struct->my_command[i]);
	// if(my_struct->my_command[1])
	// free(dst);
	int i;
	int j;
	j = 0;
	i = 0;
	// char *dst;
	while(j <= c_of_s)
	{
		while(my_struct->each_cmd[j].cmd[i])
		{
			printf("=====> %s\n",my_struct->each_cmd[j].cmd[i]);
			i++;
		}
		// dst = calloc(sizeof(char *), i + 2);
		// i = 0;
		// while(my_struct->each_cmd[j].cmd[i])
		// {
		// 	dst[i] = ft_strdup(my_struct->each_cmd[j].cmd[i]);
		// 	i++;
		// }
		// if(ft_strchr(my_struct->each_cmd[j].cmd[1],'=') && my_struct->each_cmd[j].cmd[1])
		// 	dst[i] = ft_strdup(my_struct->each_cmd[j].cmd[1]);
		// while()
		j++;
	}

}


void	exicut_commande(t_all *my_struct, int i, int c_of_s)
{
	if (!ft_strncmp(my_struct->each_cmd[c_of_s].cmd[0], "cd", ft_strlen("cd")))
		exit(1);
	else if (!ft_strncmp(my_struct->each_cmd[c_of_s].cmd[0], "echo", ft_strlen("echo")))
	{
		exicut_echo(my_struct,c_of_s);
	}
	// printf("ssss\n");
	else if (!ft_strncmp(my_struct->each_cmd[c_of_s].cmd[0], "export", ft_strlen("export")))
	{

		export_command(my_struct,c_of_s);
	}
	else if (!ft_strncmp(my_struct->cmd, my_struct->cmd,
				ft_strlen(my_struct->cmd)))
	{
		check_rediractions(my_struct, c_of_s);
		execve(my_struct->my_path[i], my_struct->each_cmd[c_of_s].cmd, NULL);
	}
}
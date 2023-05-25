/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commande.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 14:19:24 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/13 15:55:12 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**new_env(t_list *list)
{
	t_list	*ptr;
	int		i;
	char	**dst;

	ptr = list;
	i = 0;
	while (list != NULL)
	{
		list = list->next;
		i++;
	}
	dst = malloc(sizeof(char *) * (i + 1));
	i = 0;
	list = ptr;
	while (list != NULL)
	{
		dst[i] = list->content;
		list = list->next;
		i++;
	}
	list = ptr;
	dst[i] = 0;
	return (dst);
}

void	free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

void	exicut_commande(int i, int c_of_s)
{
	char	**env;

	env = new_env(g_struct.list);
	if (g_struct.each_cmd[c_of_s].cmd[0] \
	&& ft_strchr(g_struct.each_cmd[c_of_s].cmd[0], '/'))
	{
		if (execve(g_struct.each_cmd[c_of_s].cmd[0], \
		g_struct.each_cmd[c_of_s].cmd, env) == -1)
		{
			dup2(2, 1);
			printf("minishell: %s: Is a directory\n", \
			g_struct.each_cmd[c_of_s].cmd[0]);
			free_env(env);
			exit(126);
		}
	}
	if (execve(g_struct.my_path[i], g_struct.each_cmd[c_of_s].cmd, env) == -1)
	{
		dup2(2, 1);
		printf("minishell: %s: command not found\n", \
		g_struct.each_cmd[c_of_s].cmd[0]);
		free_env(env);
		exit(127);
	}
	free_env(env);
}

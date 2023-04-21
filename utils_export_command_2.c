/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export_command_2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:52:51 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/04/20 18:08:14 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_varible(int j, int x, t_list *list, char *cmd)
{
	int		i;
	char	*old;
	char	*backup;

	backup = calloc(sizeof(char), ft_strlen(cmd) + 1);
	i = 0;
	if (j == 1)
	{
		i = 0;
		old = calloc(sizeof(char), ft_strlen(cmd) + 1);
		x = mini_search(cmd, '=');
		while (i <= x)
		{
			if (cmd[i])
			{
				old[i] = cmd[i];
			}
			i++;
		}
		backup = ft_strjoin_v2(old, ft_strdup(&cmd[x + 1]));
		free(list->content);
		list->content = ft_strdup(backup);
		free(backup);
	}
}

int	check_if(char *str, int i, int j, char *cmd)
{
	while (str[i])
	{
		if (str[i] == cmd[i] && cmd[i])
		{
			if (str[i] == '=' || str[i + 1] == '\0')
			{
				j = 1;
				break ;
			}
			i++;
		}
		else
			break ;
	}
	return (j);
}

int	replace_varible(t_list *list, char *cmd)
{
	int	i;
	int	j;
	int	x;

	x = 0;
	i = 0;
	j = 0;
	while (list != NULL)
	{
		j = check_if(((char *)list->content), 0, j, cmd);
		if (j == 1)
			break ;
		list = list->next;
		x++;
	}
	fill_varible(j, x, list, cmd);
	return (j);
}

void	search_varible(char *cmd, t_list *list)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (list != NULL)
	{
		i = 0;
		x = check_if(((char *)list->content), 0, x, cmd);
		if (x == 1)
			break ;
		list = list->next;
	}
	if (x == 1)
	{
		free(list->content);
		list->content = ft_strdup(cmd);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   untils_unset.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 03:39:21 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/14 03:39:45 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	unset_checker(t_list *list, char *cmd, t_list *head, int i)
{
	int	x;

	x = 0;
	if (unset_utils(list, cmd))
		return (1);
	while (list != NULL)
	{
		unset_utils_2(list, cmd, &x, i);
		if (x == 1)
			break ;
		list = list->next;
	}
	delete_node(list, head, x);
	return (0);
}

//p it's mean ptr list and c it's mean cas_of_string

int	unset_command(int c)
{
	t_list	*p;
	int		i;

	p = g_struct.list;
	i = 0;
	while (g_struct.each_cmd[c].cmd[++i])
	{
		if (mini_check_export(g_struct.each_cmd[c].cmd[i]) == 1
			|| ft_strchr(g_struct.each_cmd[c].cmd[i], '='))
		{
			printf("unset: `%s': not a valid identifier\n",
				g_struct.each_cmd[c].cmd[i]);
			return (-1);
		}
		else
		{
			if (unset_checker(g_struct.list, g_struct.each_cmd[c].cmd[i], p, 0))
			{
				g_struct.list = NULL;
				return (0);
			}
		}
	}
	g_struct.list = p;
	return (0);
}

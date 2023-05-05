/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 15:05:18 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/05/05 20:29:34 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_node(t_list *list, t_list *head, int x)
{
	t_list	*back;

	back = head;
	if (x == 1)
	{
		while (back)
		{
			if (back->next->content == list->content)
				break ;
			back = back->next;
		}
		free(list->content);
		back->next = list->next;
	}
}

int	first_varible(char *str, char *cmd, t_list *list)
{
	char	**dst;
	int		i;

	i = -1;
	dst = ft_split(str, '=');
	if (!ft_strncmp(cmd, dst[0], ft_strlen(dst[0]) + 1))
	{
		free(str);
		while (dst[++i])
			free(dst[i]);
		free(dst);
		*list = *list->next;
		return (1);
	}
	return (0);
}

void	unset_checker(t_list *list, char *cmd, t_list *head, int i)
{
	int	x;

	x = 0;
	if (first_varible(list->content, cmd, list) == 1)
		return ;
	while (list != NULL)
	{
		while (cmd[i])
		{
			if (((char *)list->content)[i]
				&& ((char *)list->content)[i] == cmd[i])
			{
				i++;
				if (((char *)list->content)[i] == '='
					|| ((char *)list->content)[i] == 0)
					x = 1;
			}
			else
				break ;
		}
		if (x == 1)
			break ;
		list = list->next;
	}
	delete_node(list, head, x);
}

void	unset_command(t_all *_struct, int c_of_s)
{
	t_list	*ptr;
	int		i;

	ptr = _struct->list;
	i = 0;
	while (_struct->each_cmd[c_of_s].cmd[i])
	{
		if (mini_check_export(_struct->each_cmd[c_of_s].cmd[i], 1) == 1
			|| ft_strchr(_struct->each_cmd[c_of_s].cmd[i], '='))
		{
			printf("unset: `%s': not a valid identifier\n",
				_struct->each_cmd[c_of_s].cmd[i]);
			i++;
		}
		else
		{
			unset_checker(_struct->list, _struct->each_cmd[c_of_s].cmd[i],
				ptr, 0);
			i++;
		}
	}
	_struct->list = ptr;
	i = 0;
}

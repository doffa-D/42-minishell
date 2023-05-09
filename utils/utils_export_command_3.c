/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_export_command_3.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 17:01:03 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/05/09 13:27:00 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../library/minishell.h"

int	check_if_v2(char *str, char *cmd, int x, int i)
{
	while (cmd[i])
	{
		if (str[i] && str[i] == cmd[i])
		{
			if (str[i] == '=' || str[i + 1] == '\0')
			{
				x = 1;
				break ;
			}
			i++;
		}
		else
			break ;
	}
	return (x);
}

int	mini_checker_export(t_list *list, char *cmd)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (list != NULL)
	{
		x = check_if_v2(list->content, cmd, x, 0);
		if (x == 1)
			break ;
		list = list->next;
	}
	if (x == 1)
	{
		free(list->content);
		list->content = ft_strdup(cmd);
		return (1);
	}
	return (0);
}

int	check_varible_if_have(t_list *list, char *cmd)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (list != NULL)
	{
		i = 0;
		while (cmd[i])
		{
			if (((char *)list->content)[i]
				&& ((char *)list->content)[i] == cmd[i])
			{
				i++;
				if (((char *)list->content)[i] == '=')
					x = 1;
			}
			else
				break ;
		}
		if (x == 1)
			break ;
		list = list->next;
	}
	return (x);
}

void	mini_print_export(char *dst, int i, int j)
{
	while (dst[i])
	{
		if (dst[i] == '=' && j == 1)
		{
			printf("=%c", 34);
			j = 0;
		}
		else if (dst[i] == '$' || dst[i] == 34)
		{
			printf("\\%c", dst[i]);
		}
		else if (dst[i + 1] == '\0' && j == 0)
		{
			printf("%c", dst[i]);
		}
		else
			printf("%c", dst[i]);
		i++;
	}
}

void	print_export(t_list *list)
{
	int		i;
	int		j;
	char	*dst;

	i = 0;
	j = 1;
	while (list != NULL)
	{
		dst = (char *)list->content;
		printf("declare -x ");
		mini_print_export(dst, 0, 1);
		if (ft_strchr(list->content, '='))
			printf("%c\n", 34);
		else
			printf("\n");
		list = list->next;
	}
}

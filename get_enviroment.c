/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_enviroment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 13:50:48 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/08 21:55:44 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

char	*_get_env(t_list *head, int j, int trim, char *expande_variable)
{
	int	i;

	free(expande_variable);
	expande_variable = ft_substr(head->content, j + 1,
			ft_strlen(head->content + (j + 1)));
	free_parccing_part_after_error(expande_variable);
	i = 0;
	if (trim == 1)
	{
		while (expande_variable[i])
		{
			if (expande_variable[i] == ' ')
				expande_variable[i] = 3;
			i++;
		}
	}
	return (expande_variable);
}

char	*my_getenv(t_list *head, char *var, int trim)
{
	int		j;
	char	*expande_variable;

	j = 0;
	expande_variable = ft_calloc(1, 1);
	free_parccing_part_after_error(expande_variable);
	while (head != NULL)
	{
		if (*(char *)head->content == var[0])
		{
			j = 0;
			while (((char *)head->content)[j] == var[j] ||
					((char *)head->content)[j] == '=')
			{
				if (((char *)head->content)[j] == '=' && !var[j])
				{
					expande_variable = _get_env(head, \
					j, trim, expande_variable);
					return (expande_variable);
				}
				j++;
			}
		}
		head = head->next;
	}
	return (expande_variable);
}

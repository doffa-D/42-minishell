/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expande_varbles.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:22:56 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/09 15:42:28 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*split_variable_or_not(char *variable)
{
	if (g_struct.status == IN_DCOTE)
		variable = my_getenv(g_struct.list, variable, 0);
	else
		variable = my_getenv(g_struct.list, variable, 1);
	return (variable);
}

char	*expande_variable_utils(t_var *variables, \
	char *whotout_expande, char *variable, int end)
{
	variable = ft_substr(whotout_expande, variables->index_j + 1, (end \
		- (variables->index_j + 1)));
	free_parccing_part_after_error(variable);
	variable = split_variable_or_not(variable);
	return (variable);
}

char	*is_alphabet_after_dolar(t_var *variables, \
	char *whotout_expande, char *my_string, int end)
{
	char	*str;
	char	*variable;

	variable = 0;
	variable = expande_variable_utils(variables, \
	whotout_expande, variable, end);
	if (variable)
	{
		my_string = ft_strjoin(my_string, variable);
		free_parccing_part_after_error(my_string);
		if (g_struct.ambiguous == 1)
		{
			str = ft_strtrim(my_string, "\003\000");
			free_parccing_part_after_error(str);
			if (!str || (ft_strlen(str) == 0 \
			&& ((whotout_expande[variables->index_j - 1] == 3 \
			&& (whotout_expande[end] == 3 || whotout_expande[end] == 0))
						|| ft_strchr(variable, 3))))
				g_struct.error_ambiguous = 1;
			free(str);
		}
		free(variable);
	}
	variables->index_j = end - 1;
	return (my_string);
}

char	*in_single_quotes(t_var *variables, \
	char *whotout_expande, char *my_string, int end)
{
	char	*variable;

	if (g_struct.status == IN_COTE)
	{
		variable = ft_substr(whotout_expande, variables->index_j, (end \
			- variables->index_j));
		free_parccing_part_after_error(variable);
		my_string = ft_strjoin_v2(my_string, variable);
		free_parccing_part_after_error(my_string);
		variables->index_j = end - 1;
	}
	return (my_string);
}

char	*variables_parceen(t_var *variables, \
	char *whotout_expande, char *my_string)
{
	int		end;

	end = variables->index_j + 1;
	while (whotout_expande[end] && (ft_isalpha(whotout_expande[end]) \
	|| ft_isdigit(whotout_expande[end]) || whotout_expande[end] == '_'))
		end++;
	if (g_struct.status == IN_DCOTE || g_struct.status == OUTSIDE)
	{
		if (ft_isdigit(whotout_expande[variables->index_j + 1]))
			variables->index_j++;
		else if (ft_isalpha(whotout_expande[variables->index_j + 1])
			|| whotout_expande[variables->index_j + 1] == '_')
			my_string = is_alphabet_after_dolar(variables, \
			whotout_expande, my_string, end);
	}
	my_string = in_single_quotes(variables, \
	whotout_expande, my_string, end);
	return (my_string);
}

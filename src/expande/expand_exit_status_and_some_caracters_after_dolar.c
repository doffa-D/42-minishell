/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_exit_status_and_some_caracters_after        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 14:23:53 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/09 15:53:17 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*other_character_after_dolar(char *whotout_expande, char *my_string,
		t_var *variables)
{
	if (whotout_expande[variables->index_j + 1] == '?')
	{
		if (g_struct.status != IN_COTE)
		{
			variables->index_j++;
			my_string = \
			ft_strjoin(my_string, ft_itoa(g_struct.exit_status));
			free_parccing_part_after_error(my_string);
			variables->start = variables->index_j;
		}
	}
	else if ((whotout_expande[variables->index_j + 1] == 34 \
	|| whotout_expande[variables->index_j + 1] == 39) \
	&& g_struct.status == OUTSIDE)
		variables->start = variables->index_j;
	else if (!ft_isalnum(whotout_expande[variables->index_j + 1]) \
	&& whotout_expande[variables->index_j + 1] != '$')
	{
		variables->index_j++;
		variables->start = variables->index_j;
	}
	return (my_string);
}

char	*expande_all(char *whotout_expande, char *my_string,
		t_var *variables)
{
	if (ft_isalnum(whotout_expande[variables->index_j + 1]) \
	|| whotout_expande[variables->index_j + 1] == '_')
	{
		if (whotout_expande[variables->index_j + 1])
		{
			variables->start++;
			my_string = variables_parceen(variables, \
			whotout_expande, my_string);
			variables->start = variables->index_j;
		}
	}
	else
	{
		my_string = other_character_after_dolar(whotout_expande, \
		my_string, variables);
	}
	return (my_string);
}

char	*exit_status(char *my_string, t_var *variables)
{
	if (g_struct.status != IN_COTE)
	{
		variables->index_j++;
		my_string = ft_strjoin_v2(my_string, \
		ft_itoa(g_struct.exit_status));
		free_parccing_part_after_error(my_string);
		variables->start = variables->index_j;
	}
	else
		variables->start = variables->index_j - 1;
	return (my_string);
}

char	*_not_alphanum_after_dolar(char *whotout_expande, char *my_string,
		t_var *variables)
{
	if (whotout_expande[variables->index_j + 1] == '?')
		my_string = exit_status(my_string, variables);
	else if (g_struct.status != OUTSIDE \
		&& (whotout_expande[variables->index_j + 1] == 8 \
		|| whotout_expande[variables->index_j + 1] == 6))
		variables->start = variables->index_j - 1;
	else if (!ft_isalnum(whotout_expande[variables->index_j + 1]) \
	&& whotout_expande[variables->index_j + 1] != '$' \
	&& whotout_expande[variables->index_j + 1] != 8 \
	&& whotout_expande[variables->index_j + 1] != 6)
	{
		variables->index_j++;
		variables->start = variables->index_j;
	}
	else if (whotout_expande[variables->index_j + 1] == '$')
	{
		variables->index_j++;
		variables->start = variables->index_j - 1;
	}
	return (my_string);
}

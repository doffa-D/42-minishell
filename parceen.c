/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcceen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 00:39:18 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/06 00:01:14 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"
// void parccc(t_all *_struct)
// {
//     int		i;
// 	int		j;
// 	int		checker;
// 	char	splite_char;
// 	i = 0;
//     // _struct->tmp_cmd = 0;
// 	// _struct->tmp_cmd = ft_strdup(_struct->cmd);
// 	// _struct->the_commande = 0;
// 	// while (_struct->tmp_cmd[i])
// 	// {
// 	// 	splite_char = ' ';
// 	// 	checker = 0;
// 	// 	while (_struct->tmp_cmd[i] && _struct->tmp_cmd[i] != splite_char)
// 	// 	{
// 	// 		if (_struct->tmp_cmd[i] == 34 && !checker)
// 	// 		{
// 	// 			splite_char = 34;
// 	// 			checker = 1;
// 	// 		}
// 	// 		if (_struct->tmp_cmd[i] == 39 && !checker)
// 	// 		{
// 	// 			splite_char = 39;
// 	// 			checker = 1;
// 	// 		}
// 	// 		i++;
// 	// 	}
// 	// 	if (splite_char != ' ' && _struct->tmp_cmd[i])
// 	// 		i++;
// 	// 	if (_struct->tmp_cmd[i] == ' ')
// 	// 	{
// 	// 		if (!_struct->the_commande)
// 	// 			_struct->the_commande = ft_calloc(1, 1);
// 	// 		_struct->tmp_cmd[i] = 3;
// 	// 		i++;
// 	// 		_struct->the_commande = ft_strjoin_v2(_struct->the_commande,
// 	// 				ft_substr(_struct->tmp_cmd, j, i - j));
// 	// 		j = i;
// 	// 	}
// 	// 	if (!_struct->tmp_cmd[i])
// 	// 	{
// 	// 		if (!_struct->the_commande)
// 	// 			_struct->the_commande = ft_calloc(1, 1);
// 	// 		_struct->the_commande = ft_strjoin_v2(_struct->the_commande,
// 	// 				ft_substr(_struct->tmp_cmd, j, i - j));
// 	// 		break ;
// 	// 	}
// 	// }

// }


char *_get_env(t_list *head, int j, int trim, char *expande_variable)
{
	int i;
	free(expande_variable);
	expande_variable = ft_substr(head->content, j + 1,
			ft_strlen(head->content + (j + 1)));
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
    return expande_variable;
}

char	*my_getenv(t_list *head, char *var, int trim)
{
	int		j;
	char	*expande_variable;

	j = 0;
	expande_variable = ft_calloc(1, 1);
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
					expande_variable = _get_env(head, j, trim, expande_variable);
					return (expande_variable);
				}
				j++;
			}
		}
		head = head->next;
	}
	return (expande_variable);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:31:35 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/04/16 23:13:24 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define IN_DCOTE 0
#define IN_COTE 1
#define VAR 3
#define WORD 4
#define OUTSIDE 5



char	*ft_strjoin_v2(char const *s1, char const *s2)
{
	char	*b;
	int		i;
	int		j;

	if (s1 == 0 || s2 == 0)
		return (0);
	i = 0;
	b = malloc((ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!b)
		return (b);
	j = 0;
	while (s1[i])
	{
		b[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		b[i] = s2[j];
		i++;
		j++;
	}
	b[i] = 0;
    free((char *)s1);
    free((char *)s2);
	return (b);
}

void    fix_arg(t_all *my_struct)
{
    int i = 0;
    int j = 0;
    int c = -1;
    int var;
    char		*variable;
    char splite[2];
    splite[0] = 3; 
    splite[1] = '\0';
    int			status;
    i = 0;
    my_struct->number_of_pipes = 1;
    my_struct->the_commande = 0;
    my_struct->the_commande = ft_calloc(1, 1);
    while(my_struct->fix_cmd[i])
    {
        j = 0;
        c = -1;
        status = OUTSIDE;
        while (my_struct->fix_cmd[i][j])
        {
            if((my_struct->fix_cmd[i][j] == 34) && status != IN_COTE)
            {
                c++;
                if(my_struct->fix_cmd[i][j] == 34 && status == IN_DCOTE)
                    status = OUTSIDE;
                else
                    status = IN_DCOTE;
                my_struct->the_commande = ft_strjoin_v2(my_struct->the_commande, ft_substr(my_struct->fix_cmd[i], c, j - c));
                c = j;
            }
            if((my_struct->fix_cmd[i][j] == 39)&& status != IN_DCOTE)
            {
                c++;
                if(my_struct->fix_cmd[i][j] == 39 && status == IN_COTE)
                    status = OUTSIDE;
                else
                    status = IN_COTE;
                my_struct->the_commande = ft_strjoin_v2(my_struct->the_commande, ft_substr(my_struct->fix_cmd[i], c, j - c));
                c = j;
            }
            if(my_struct->fix_cmd[i][j] == '|' && status == OUTSIDE)
            {
                my_struct->fix_cmd[i][j] = 4;
                my_struct->number_of_pipes++;
            }
            if(my_struct->fix_cmd[i][j] == '>' && status == OUTSIDE)
                my_struct->fix_cmd[i][j] = 2;
            if(my_struct->fix_cmd[i][j] == '<' && status == OUTSIDE)
                my_struct->fix_cmd[i][j] = 5;
            if(my_struct->fix_cmd[i][j] == '$' && my_struct->fix_cmd[i][j + 1])
            {
                if(my_struct->fix_cmd[i][j + 1] != 39 && my_struct->fix_cmd[i][j + 1] != 34)
                {
                    if(ft_isalpha(my_struct->fix_cmd[i][j + 1]))
                    {
                        c++;
                        var = j + 1;
                        my_struct->the_commande = ft_strjoin_v2(my_struct->the_commande, ft_substr(my_struct->fix_cmd[i], c, j - c));
                        while (my_struct->fix_cmd[i][var]  && (ft_isalpha(my_struct->fix_cmd[i][var]) || ft_isdigit(my_struct->fix_cmd[i][var])))
                            var++;
                        if(status == IN_DCOTE || status == OUTSIDE)
                        {
                            variable = ft_substr(my_struct->fix_cmd[i], j + 1, (var - (j + 1)));
                            if(getenv(variable))
                                my_struct->the_commande = ft_strjoin(my_struct->the_commande, getenv(variable));
                            j = var - 1;
                        }
                        if(status == IN_COTE)
                        {
                            variable = ft_substr(my_struct->fix_cmd[i], j, (var - j));
                            my_struct->the_commande = ft_strjoin(my_struct->the_commande, variable);
                            j = var - 1;
                        }
                        c = j;
                    }
                    else
                    {
                        j++;
                        c = j;
                    }
                }
                else if(status == OUTSIDE && (my_struct->fix_cmd[i][j + 1] == 39 || my_struct->fix_cmd[i][j + 1] == 34))
                {
                    my_struct->the_commande = ft_strjoin_v2(my_struct->the_commande, ft_substr(my_struct->fix_cmd[i], c + 1, j - (c + 1)));
                    c = j;
                }
            }
            j++;
        }
        if(status == OUTSIDE)
        {
            if(status == OUTSIDE)
                c++;
            my_struct->the_commande = ft_strjoin_v2(my_struct->the_commande, ft_substr(my_struct->fix_cmd[i], c, j - c));
        }
        my_struct->the_commande = ft_strjoin(my_struct->the_commande, splite);
        free(my_struct->fix_cmd[i]);
        my_struct->fix_cmd[i] = 0;
        i++;
    }
    free(my_struct->fix_cmd);
    free(my_struct->the_commande);
    my_struct->splite_pipe = ft_split(my_struct->the_commande, 4);
    my_struct->the_commande = 0;
    i = 0; 
    j = 0;
    my_struct->each_cmd = ft_calloc(sizeof(t_each_command) , my_struct->number_of_pipes + 1);
    int c_of_s = 0;
    while(my_struct->splite_pipe[i])
    {
        j = 0;
        var = 0;
        my_struct->the_commande = ft_calloc(1, 1);
        while(my_struct->splite_pipe[i][j])
        {
            if (my_struct->splite_pipe[i][j] == 2 || my_struct->splite_pipe[i][j] == 5)
            {
                while (my_struct->splite_pipe[i][j] == 2)
                    j++;
                var++;
            }
            j++;
        }
        my_struct->each_cmd[i].files = ft_calloc(sizeof(t_files), (var + 1));
        j = 0;
        while (my_struct->splite_pipe[i][j])
        {
            if(my_struct->splite_pipe[i][j] == 2)
            {
	            my_struct->each_cmd[i].files[c_of_s].OUTPUT = 0;
	            my_struct->each_cmd[i].files[c_of_s].APPEND = 0;
	            my_struct->each_cmd[i].files[c_of_s].ERROR_SYNTACSO = 0;
	            my_struct->each_cmd[i].files[c_of_s].number_of_O = 0;
	            my_struct->each_cmd[i].files[c_of_s].number_of_I = 0;
                while (my_struct->splite_pipe[i][j] && (my_struct->splite_pipe[i][j] == 2 || my_struct->splite_pipe[i][j] == 3 || my_struct->splite_pipe[i][j] == 5))
                {
                    if(my_struct->splite_pipe[i][j] == 2)
                        my_struct->each_cmd[i].files[c_of_s].number_of_O++;
                    if(my_struct->splite_pipe[i][j] == 5)
                        my_struct->each_cmd[i].files[c_of_s].number_of_I++;
                    j++;
                }
                var = j;
                while (my_struct->splite_pipe[i][var] && my_struct->splite_pipe[i][var] != 2 && my_struct->splite_pipe[i][var] != 5 && my_struct->splite_pipe[i][var] != 3)
                    var++;
                if(my_struct->each_cmd[i].files[c_of_s].number_of_O && my_struct->each_cmd[i].files[c_of_s].number_of_I)
	                my_struct->each_cmd[i].files[c_of_s].ERROR_SYNTACSO = 1;
                else if(my_struct->each_cmd[i].files[c_of_s].number_of_O == 2)
	                my_struct->each_cmd[i].files[c_of_s].APPEND = 1;
                else if(my_struct->each_cmd[i].files[c_of_s].number_of_O == 1)
	                my_struct->each_cmd[i].files[c_of_s].OUTPUT = 1;
                else if(my_struct->each_cmd[i].files[c_of_s].number_of_O > 2)
	                my_struct->each_cmd[i].files[c_of_s].ERROR_SYNTACSO = 1;
                my_struct->each_cmd[i].files[c_of_s].files = ft_substr(my_struct->splite_pipe[i], j, var - j);
                // printf("{%s}\n", my_struct->each_cmd[i].files[c_of_s].files);
                c_of_s++;
                j = var - 1;
            }
            else if(my_struct->splite_pipe[i][j] == 5)
            {
                
	            my_struct->each_cmd[i].files[c_of_s].INPUT = 0;
	            my_struct->each_cmd[i].files[c_of_s].HERDOC = 0;
	            my_struct->each_cmd[i].files[c_of_s].ERROR_SYNTACSI = 0;
	            my_struct->each_cmd[i].files[c_of_s].number_of_O = 0;
	            my_struct->each_cmd[i].files[c_of_s].number_of_I = 0;
                while (my_struct->splite_pipe[i][j] && (my_struct->splite_pipe[i][j] == 2 || my_struct->splite_pipe[i][j] == 3 || my_struct->splite_pipe[i][j] == 5))
                {
                    if(my_struct->splite_pipe[i][j] == 2)
                        my_struct->each_cmd[i].files[c_of_s].number_of_O++;
                    if(my_struct->splite_pipe[i][j] == 5)
                        my_struct->each_cmd[i].files[c_of_s].number_of_I++;
                    j++;
                }
                var = j;
                while (my_struct->splite_pipe[i][var] && my_struct->splite_pipe[i][var] != 2 && my_struct->splite_pipe[i][var] != 5 && my_struct->splite_pipe[i][var] != 3)
                    var++;
                if(my_struct->each_cmd[i].files[c_of_s].number_of_O && my_struct->each_cmd[i].files[c_of_s].number_of_I)
	                my_struct->each_cmd[i].files[c_of_s].ERROR_SYNTACSI = 1;
                else if(my_struct->each_cmd[i].files[c_of_s].number_of_I == 1)
	                my_struct->each_cmd[i].files[c_of_s].INPUT = 1;
                else if(my_struct->each_cmd[i].files[c_of_s].number_of_I == 2)
	                my_struct->each_cmd[i].files[c_of_s].HERDOC = 1;
                else if(my_struct->each_cmd[i].files[c_of_s].number_of_I > 2)
	                my_struct->each_cmd[i].files[c_of_s].ERROR_SYNTACSI = 1;
                my_struct->each_cmd[i].files[c_of_s].files = ft_substr(my_struct->splite_pipe[i], j, var - j);
                c_of_s++;
                j = var - 1;
            }
            else if(my_struct->splite_pipe[i][j] != 5 && my_struct->splite_pipe[i][j] != 2)
            {
                var = j;
                while (my_struct->splite_pipe[i][var] && (my_struct->splite_pipe[i][var] != 2 && my_struct->splite_pipe[i][var] != 5))
                    var++;
                my_struct->the_commande  = ft_strjoin_v2(my_struct->the_commande, ft_substr(my_struct->splite_pipe[i], j, var - j));
                j = var - 1;
            }
            j++;
        }
        my_struct->each_cmd[i].cmd = ft_split(my_struct->the_commande, 3);
        // int k = 0;
        // while(my_struct->each_cmd[i].cmd[k])
        // {
        //     printf("#%s#\n",my_struct->each_cmd[i].cmd[k]);
        //     k++;
        // }
        // exit(1);
        free(my_struct->splite_pipe[i]);
        free(my_struct->the_commande);
        my_struct->the_commande = 0;
        my_struct->splite_pipe[i] = 0;;
        i++;
    }
    free(my_struct->splite_pipe);
    // while(1);
}
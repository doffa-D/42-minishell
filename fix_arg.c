/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 12:31:35 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/03/21 12:29:14 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_check(char *cmd)
{
    int i;
    i = 0;
    int k1;
    int k2;
    k1 = 0;
    k2 = 0;
    while(cmd[i])
    {
        if(cmd[i] == 39)
            k1++;
        else if(cmd[i] == 34)
            k2++;
        i++;
    }
	if (k1 % 2 == 1 && k1 > 0)
		return (0);
	if (k2 % 2 == 1 && k2 > 0)
		return (0);
    if (k1 % 2 == 0 && k1 > 0)
		return (2);
	if (k2 % 2 == 0 && k2 > 0)
		return (2);
	return (1);
}

char    *skip_quote(char *cmd)
{
    int i;
    int j;
    j = 0;
    i = 0;
    char *dst;
    dst = malloc(ft_strlen(cmd));
    while(cmd[i])
    {
        if(cmd[i] == 39)
            i++;
        else if(cmd[i] == 34)
            i++;
        else
        {
            dst[j] = cmd[i];
            j++;
            i++;
        }
    }
    dst[j] = '\0';
    return dst;
}

int count_2d(t_all *my_struct)
{
    my_struct->command_len = -1;
    while(my_struct->fix_cmd[++my_struct->command_len]);
    return my_struct->command_len;
}

int checker(char *cmd)
{
    int i;
    i = 0;
    while(cmd[i])
    {
        if(cmd[i] == 39 && cmd[i+1] == 34 && cmd[i+2] == 39)
            return 1;
        else if (cmd[i] == 34 && cmd[i+1] == 39 && cmd[i+2] == 34)
            return 2;
        i++;
    }
    return 0;
}


int	count_qoute(const char *s)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	if (s == 0)
		return (0);
	while (s[i])
	{
		while (s[i] && (s[i] == 39 || s[i] == 34 || s[i] == '$' ))
			i++;
		while (s[i] && (s[i] != 39 || s[i] != 34 || s[i] != '$'))
		{
			if ((s[i + 1] == 39 || s[i + 1] == 34 || s[i + 1] == '$') || !s[i + 1])
				j++;
			i++;
		}
	}
	return (j);
}

int	count_dollar(const char *s)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	if (s == 0)
		return (0);
	while (s[i])
	{
		while (s[i] && s[i] == '$')
			i++;
		while (s[i] && s[i] != '$')
		{
			if (s[i + 1] == '$' || !s[i + 1])
				j++;
			i++;
		}
	}
	return (j);
}

char *check_inve(char **split,int i)
{
    int x;
    x = 0;
        int q = 0;
    while (split[x])
        q += ft_strlen(split[x++]);
    char *backup = ft_calloc(q, sizeof(char));
    while(--i >= 0)
    {
        if(ft_strchr(split[i],'$'))
        {
            if(getenv(&split[i][1]) != NULL)
            {
        		ft_strlcat(backup, getenv(&split[i][1]),ft_strlen(backup) + 1);
            }
        }
        else
		    ft_strlcat(backup, split[i],ft_strlen(backup) + 1);
    }
    
    return backup;
}

char *split_dollar(char *cmd)
{
    char **split;
    char *dst;
    int i;
    int x;
    x = 0;
    i = ft_strlen(cmd)-1;
    split = calloc(sizeof(char *)*count_dollar(cmd) + 2 , 1);
    while(i >= 0)
    {
        if(cmd[i] == '$' || i == 0)
        {
            split[x] = ft_strdup(&cmd[i]);
            cmd[i] = '\0';
            x++;
        }
        i--;
    }
    dst = check_inve(split,x);
    return (dst);
}

char    *dollar_handle(char *cmd)
{
    cmd = split_dollar(cmd);
    return cmd;
}

char    *upload(char *cmd,int x)
{
    int i;
    int j;
    char *final;
    char **dst;

    final = malloc(sizeof(char) * ft_strlen(cmd) + 1);
    i = 0;
    j = 0;
    if(x == 1)
    {
        while(cmd[i])
        {
            if(cmd[i] == 39)
                i++;
            else
            {
                final[j] = cmd[i];
                i++;
                j++;
            }
        }
        final[j]='\0';
    }
    else if(x == 2)
    {
        while(cmd[i])
        {
            if(cmd[i] == 34)
                i++;
            else
            {
                final[j] = cmd[i];
                i++;
                j++;
            }
        }
        final[j]='\0';
    }
    dst = calloc(sizeof(char*) * count_qoute(final) + 1,1);
    i = ft_strlen(final);
    j = 0;
    while(--i >= 0)
    {
        if((final[i] == 39 || final[i] == '$' || i == 0) && x == 2)
        {
            dst[j] = ft_strdup(&final[i]);
            final[i] = '\0';
            j++;
        }
        else if((final[i] == 34 || final[i] == '$' || i == 0) && x == 1)
        {
            dst[j] = ft_strdup(&final[i]);
            final[i] = '\0';
            j++;
        }
    }
    ft_bzero(final,ft_strlen(final));
    final = check_inve(dst,j);
    while(dst[j])
        free(dst[j--]);
    free(dst);

    return final;
}

void    fix_arg(t_all *my_struct)
{
    int i;
    int j;
    j = 0;
    i = 0;
    char *cmd;
    my_struct->my_command = malloc(sizeof(char *) * (count_2d(my_struct)+1));
    while(my_struct->fix_cmd[i])
    {
        if((quote_check(my_struct->fix_cmd[i]) == 2 || quote_check(my_struct->fix_cmd[i]) == 1) && checker(my_struct->fix_cmd[i]) == 0)
        {
            if(ft_strchr(my_struct->fix_cmd[i],'$'))
            {
                cmd = dollar_handle(skip_quote(my_struct->fix_cmd[i]));
                if(cmd != 0)
                    my_struct->my_command[j] = cmd;
                else
                    my_struct->my_command[j] = 0;
            }
            else
                my_struct->my_command[j] = skip_quote(my_struct->fix_cmd[i]);
            j++;
        }
        else
        {
            if(checker(my_struct->fix_cmd[i]) == 1 || checker(my_struct->fix_cmd[i]) == 2)
            {
                my_struct->my_command[j] = upload(my_struct->fix_cmd[i],checker(my_struct->fix_cmd[i]));

                j++;
            }
            else
            {
                printf("error\n");
                break;
            }
        }
        i++;
    }

    my_struct->my_command[j] = 0;
    // j = 0;
    // while(my_struct->my_command[j])
    //     printf("\033[0;31m[%s]\033[0;37m\n",my_struct->my_command[j++]);

    // exit(0);
}
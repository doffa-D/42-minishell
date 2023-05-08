/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   git_branch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdagdagu <hdagdagu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/08 16:47:06 by hdagdagu          #+#    #+#             */
/*   Updated: 2023/05/08 23:26:58 by hdagdagu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*get_next_line(int fd)
{
	char	buffer;
	char	line[7000000];
	int		b;
	int		i;

	if (fd < 0 || 5 <= 0)
		return (NULL);
	i = 0;
	b = read(fd, &buffer, 1);
	while (b > 0)
	{
		line[i++] = buffer;
		if (buffer == '\n')
			break ;
		b = read(fd, &buffer, 1);
	}
	line[i] = '\0';
	if (b <= 0 && i == 0)
		return (NULL);
	return (ft_strdup(line));
}

char **find_git()
{
    int fd ;
    char *l;
    char **str;
    char *dst;

    dst = getcwd(NULL,554);
    l = NULL;
    l = ft_strjoin(dst,"/.git/HEAD");
    fd = open(l,O_RDONLY);
    free(l);
    l = get_next_line(fd);
    if (l == NULL)
    {
        close(fd);
        return NULL;
    }
    str = ft_split(l,'/');
    free(l);
    close(fd);
    return str;
}

char* get_git_branch_name()
{
    char *str1;
    char *l;
    char **str;
    int i;

    l = NULL;
    str = find_git();
    i = 0;
    while(str[i])
        i++;
    if(str[i-1])
    {
        str1 = ft_strdup(str[i-1]);
        free_split(str);
        l = ft_strtrim(str1,"\n");
        free(str1);
    }
    return l;
}

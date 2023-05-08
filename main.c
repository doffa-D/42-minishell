/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nouakhro <nouakhro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:07:52 by nouakhro          #+#    #+#             */
/*   Updated: 2023/05/08 17:27:19 by nouakhro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	handler(int sig)
// {
// 	if (sig == SIGINT)
// 	{
// 		rl_replace_line("", 0);
// 		printf("\n");
// 		rl_on_new_line();
// 		rl_redisplay();
// 	}
// 	if (sig == SIGQUIT)
// 		return ;
// }


int	after_parccing(int c_of_s)
{
	int	i;

	i = 0;
	c_of_s = _parent_builtins(c_of_s);
	if (c_of_s != 2)
		return (c_of_s);
	_path_comanmde();
	c_of_s = 0;
	while (c_of_s < g_struct.number_of_pipes - 1)
	{
		pipe(g_struct.each_cmd[c_of_s].fd);
		c_of_s++;
	}
	c_of_s = 0;
	pipe_is_exist_or_its_not_builtins(c_of_s, i);
	free_all_v2(1);
	return (2);
}

void	free_split(char **str)
{
	int i;
	i = 0;
	while(str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
char *my_zsh()
{
    static int j;
    j++;
    int    i;
    char **str;
    char *str3;
    char *str2;
    i = 0;
    char *k = getcwd(NULL, 254);
    str2 = k;
    str = ft_split(k,'/');
    free(str2);
    if(str[0] == NULL)
        str[0] = ft_strdup("/");
    str2 = my_getenv(g_struct.list,"USER",0);

    while(str[i])
        i++;
    if(str2 && str[i-1] && !ft_strncmp(str2,"hdagdagu",ft_strlen(str2)+1))
    {
        str3 = ft_strjoin_v2(ft_strdup("\033[0;31m𝗗 𝗢 𝗙 𝗟 𝗔 𝗠 𝗜 𝗡 𝗚 𝗢 🦩 \033[0;37m-> "),ft_strjoin(ft_strdup(str[i-1])," "));

    }
    else if(str2 && !ft_strncmp(str2,"nouakhro",ft_strlen(str2)+1))
    {
        str3 = ft_strjoin_v2(ft_strdup("\033[0;32mE S C A N O R ☀️ \033[0;37m-> "),ft_strjoin(ft_strdup(str[i-1])," "));
    }
    else
    {
        str3 = ft_strjoin_v2(ft_strdup("\033[0;32mE R E N Y E A G E R 💀 \033[0;37m-> "),ft_strjoin(ft_strdup(str[i-1])," "));
    }
    free(str2);
    free_split(str);
	str2 = get_git_branch_name();
    printf("%s\n",str2);
    free(str2);
    return str3;
}

int    main(int argc, char **argv, char **env)
{

    (void)argv;
    (void)argc;
    g_struct.list = NULL;
    fill_linked_list(env, &g_struct.list);
    g_struct.exit_status = 0;
    // signal(SIGINT, &handler);
    // signal(SIGQUIT, &handler);    
    char *str;
    while (1)
    {
        g_struct.the_commande = 0;
        // g_struct.cmd = readline("hi -> ");
        str = my_zsh();
        g_struct.cmd = readline(str);
        free(str);
        if (!g_struct.cmd)
            exit(g_struct.exit_status);
        if (ft_strlen(g_struct.cmd) != 0)
            g_struct.exit_status = somting_in_readline();
        free(g_struct.cmd);
    }
}
// int	main(int argc, char **argv, char **env)
// {
// 	int	i;

// 	(void)argv;
// 	(void)argc;
// 	g_struct.list = NULL;
// 	fill_linked_list(env, &g_struct.list);
// 	g_struct.exit_status = 0;
// 	// signal(SIGINT, &handler);
// 	// signal(SIGQUIT, &handler);
// 	i = 0;
// 	while (1)
// 	{
// 		g_struct.the_commande = 0;
// 		g_struct.cmd = readline("escanour > ");
// 		if (!g_struct.cmd)
// 			exit(g_struct.exit_status);
// 		if (ft_strlen(g_struct.cmd) != 0)
// 			g_struct.exit_status = somting_in_readline();
// 		free(g_struct.cmd);
// 		i++;
// 	}
// }

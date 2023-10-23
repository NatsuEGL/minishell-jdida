/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/05 07:29:08 by aamhal            #+#    #+#             */
/*   Updated: 2023/10/23 12:09:10 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	int		i;
	int		j;
	t_env	*head;
	t_list	*list;
	char	**envp;

	// catch_signals();
	(void)ac;
	(void)av;
	i = 0;
	head = NULL;
	list = NULL;
	if (!(*env))
	{
		puts("hme9 nta hhhh \n");
		exit(0);
	}
	while (env[i])
		i++;
	envp = malloc(sizeof(char *) * (i + 1));
	envp[i] = NULL;
	j = i;
	i = 0;
	while (i < j)
	{
		envp[i] = env[i];
		i++;
	}
	parsing(&list, &head, envp);
	return (0);
}

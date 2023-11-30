/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 10:24:26 by akaabi            #+#    #+#             */
/*   Updated: 2023/10/25 13:29:00 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_norm(t_env **prev, t_env **current, t_env **envp)
{
	if ((*prev))
		(*prev)->next = (*current)->next;
	else
		*envp = (*current)->next;
	free((*current)->c);
	free((*current)->v);
	free((*current));
}

void	instialise_unset(t_env **prev, t_env **current, t_env **envp, char *c)
{
	*prev = NULL;
	*current = *envp;
	while (*current && ft_strcmp((*current)->c, c) != 0)
	{
		*prev = *current;
		*current = (*current)->next;
	}
	if (*current)
		unset_norm(prev, current, envp);
}

void	delete_from_env(t_env **envp, char **p)
{
	t_env	*existing;
	t_env	*prev;
	t_env	*current;
	char	*c;

	p++;
	while (*p)
	{
		if (only_alnum(*p) == 1)
		{
			c = command_ret(*p);
			existing = find_node(*envp, c);
			if (existing)
				instialise_unset(&prev, &current, envp, c);
			free(c);
		}
		else
			free_export2((*p), envp);
		p++;
	}
}

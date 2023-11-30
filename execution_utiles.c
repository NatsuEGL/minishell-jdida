/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_utiles.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akaabi <akaabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 11:38:14 by aamhal            #+#    #+#             */
/*   Updated: 2023/11/30 13:58:27 by akaabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_if_separ(t_list **list, char *separ)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (!ft_strcmp(tmp->command, separ) && tmp->type == 'S')
			return (0);
		tmp = tmp->next;
	}
	return (-1);
}

int	check_if_her(t_list **list, char *separ)
{
	t_list	*tmp;

	tmp = *list;
	while (tmp)
	{
		if (!ft_strcmp(tmp->command, separ) && tmp->type == 'S')
		{
			tmp = tmp->next;
			if (tmp->command[0] == '\'' || tmp->command[0] == '\"')
				return (-1);
			else
				return (0);
		}
		tmp = tmp->next;
	}
	return (0);
}

void	free_empty_c(t_exec **exec_val)
{
	free((*exec_val)->command[0]);
	free((*exec_val)->command);
	exit (0);
}

void	closing_fds(t_exec **n)
{
	if ((*n)->outfile != STDOUT_FILENO)
		close ((*n)->outfile);
	if ((*n)->infile != STDIN_FILENO)
		close ((*n)->infile);
}

void	norm_shito(t_exec **n, t_exec **exec_val)
{
	closing_fds(n);
	free(exec_val);
}

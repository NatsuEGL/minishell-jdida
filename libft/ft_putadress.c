/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putadress.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aamhal <aamhal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:28:09 by aamhal            #+#    #+#             */
/*   Updated: 2023/06/05 09:19:10 by aamhal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putadress(unsigned long long n, int *count)
{
	if (n <= 9)
		ft_putchar(n + '0', count);
	else if (n > 9 && n < 16)
	{
		ft_putchar("abcdef"[n % 10], count);
	}
	else
	{
		ft_putadress(n / 16, count);
		ft_putadress(n % 16, count);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 01:51:45 by jngerng           #+#    #+#             */
/*   Updated: 2023/07/02 01:51:45 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	err_msg(void)
{
	write(2, "Error\n", 6);
	exit(1);
}

int	ft_ssp_atoi(char *s, UINT *i)
{
	UINT	j;
	int		out;
	int		sign;

	out = 0;
	sign = 1;
	j = 0;
	while ((s[j] >= 9 && s[j] <= 13) || s[j] == ' ')
		j ++;
	if (s[j] == '+' && s[j + 1] >= '0' && s[j + 1] <= '9')
		j ++;
	if (s[j] == '-' && s[j + 1] >= '0' && s[j + 1] <= '9')
	{
		sign = -1;
		j ++;
	}
	while (s[j] >= '0' && s[j] <= '9')
	{
		out = out * 10 + s[j] - 48;
		j ++;
	}
	while ((s[j] >= 9 && s[j] <= 13) || s[j] == ' ')
		j ++;
	*i = j;
	return (out * sign);
}

int	check_ord(int *arr, int siz)
{
	int	i;

	i = 0;
	if (!arr)
		err_msg();
	while (++ i < siz)
		if (arr[i - 1] > arr[i])
			return (1);
	return (0);
}

void	free_stack(t_stack *start)
{
	t_stack	*temp;

	while (start)
	{
		temp = start;
		start = start->next;
		temp->num = 0;
		free(temp);
	}
}

int	int_min(int a, int b)
{
	if (b < a)
		return (b);
	return (a);
}

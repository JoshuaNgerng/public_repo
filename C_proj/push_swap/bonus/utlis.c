/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:10:28 by jngerng           #+#    #+#             */
/*   Updated: 2023/07/19 17:10:28 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check.h"

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

void	free_2_stack(t_d_stack s)
{
	t_stack	*t;

	if (s.a_len == 1)
		free(s.a);
	if (s.a_len > 1)
	{
		t = s.a->prev;
		t->next = NULL;
		s.a->prev = NULL;
		free_stack(s.a);
	}
	if (s.b_len == 1)
		free(s.b);
	if (s.b_len > 1)
	{
		t = s.b->prev;
		t->next = NULL;
		s.b->prev = NULL;		
		free_stack(s.b);
	}
}

int	check_lst(t_stack *a, UINT len, UINT max)
{
	t_stack	*t;
	int		min;
	UINT	i;

	t = a->next;
	min = a->num;
	i = 1;
	if (len != max)
		return (1);
	while (t && i < len)
	{
		if (min >= t->num)
			return (1);
		t = t->next;
		i ++;
	}
	return (0);
}


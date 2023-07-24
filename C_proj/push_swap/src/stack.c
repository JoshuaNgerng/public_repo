/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 10:28:23 by jngerng           #+#    #+#             */
/*   Updated: 2023/06/16 10:28:23 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_stack	*get_rel_num(int ref, int *sorted, UINT siz)
{
	t_bin_search	t;
	t_stack			*out;

	t = (struct s_bin_search){0, 0, siz - 1};
	while (t.low <= t.high)
	{
		t.mid = (t.low + t.high) / 2;
		if (sorted[t.mid] < ref)
			t.low = t.mid + 1;
		if (sorted[t.mid] > ref)
			t.high = t.mid - 1;
		if (sorted[t.mid] == ref)
			break ;
	}
	if (t.low > t.high)
		return (NULL);
	out = (t_stack *) malloc (sizeof(t_stack));
	if (!out)
		return (NULL);
	out->num = t.mid;
	out->next = NULL;
	out->prev = NULL;
	return (out);
}

t_stack	*get_stack(int *ref, int *sorted, UINT siz)
{
	UINT	i;
	t_stack	*temp;
	t_stack	*start;
	t_stack	*new;

	i = 0;
	start = get_rel_num(ref[i], sorted, siz);
	if (!start)
		return (NULL);
	temp = start;
	while (++ i < siz)
	{
		new = get_rel_num(ref[i], sorted, siz);
		if (!new)
			return (free_stack(start), NULL);
		temp->next = new;
		new->prev = temp;
		temp = temp->next;
	}
	temp->next = NULL;
	return (start);
}

t_stack	*get_2_top(t_stack *s, UINT ref, UINT len, char p)
{
	UINT	i;
	UINT	j;
	t_stack	*t;

	i = 1;
	t = s;
	while (t->num >= ref)
	{
		i ++;
		if (i == len)
			break ;
		t = t->next;
	}
	j = 1;
	t = s;
	while (t->num >= ref)
	{
		j ++;
		if (j == len)
			break ;
		t = t->prev;
	}
	t = s;
	if (i < j)
	{
		while (i -- > 1)
			t = do_r(t, p);
	}
	else
	{
		while (j -- > 1)
			t = do_rr(t, p);
	}
	return (t);
}

t_stack	*get_last_lst(t_stack *s)
{
	t_stack *t;

	t = s;
	while (t)
	{
		if (!t->next)
			break ;
		t = t->next;
	}
	return (t);
}

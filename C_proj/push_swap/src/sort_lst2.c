/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_lst2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/04 14:15:15 by jngerng           #+#    #+#             */
/*   Updated: 2023/07/04 14:15:15 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static UINT	count_r(t_stack *s, UINT ref)
{
	UINT	out;
	t_stack	*t;

	out = 1;
	t = s;
	while (t->num != ref)
	{
		t = t->next;
		out ++;
	}
	return (out);
}

static t_stack	*get_small_2_top(t_stack *s, UINT ref, UINT len)
{
	t_stack	*out;
	UINT	r;
	UINT	rr;

	r = count_r(s, ref);
	rr = len - r + 1;
	out = s;
	if (r < rr)
	{
		while (r -- > 1)
			out = do_r(out, 'a');
	}
	else
	{
		while (rr -- > 1)
			out = do_rr(out, 'a');
	}
	return (out);
}

t_d_stack	sort_insert(t_d_stack s)
{
	t_d_stack	out;
	UINT		i;

	out = s;
	i = 0;
	while (out.a_len > 3)
	{
		out.a = get_small_2_top(out.a, i, out.a_len + 1);
		out = do_p(out, 'b');
		i ++;
	}
	out.a = proc_sort_3(out.a);
	while (out.b_len != 0)
		out = do_p(out, 'a');
	return (out);
}

t_d_stack	sort_radix(t_d_stack s)
{
	UINT	max;
	UINT	i;
	UINT	j;

	max = 0;
	while (s.max >> max)
		max ++;
	i = -1;
	while (++ i < max)
	{
		j = 0;
		while (j ++ < s.max)
		{
			if (((s.a->num >> i) & 1) == 1)
				s.a = do_r(s.a , 'a');
			else
				s = do_p(s, 'b');
		}
		while (s.b_len)
			s = do_p(s, 'a');
	}
	return (s);
}

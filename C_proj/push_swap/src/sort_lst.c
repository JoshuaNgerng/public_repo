/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_lst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 02:38:33 by jngerng           #+#    #+#             */
/*   Updated: 2023/06/26 02:38:33 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_stack	*proc_sort_3(t_stack *s)
{
	UINT	num[3];
	t_stack	*out;

	num[0] = s->num;
	num[1] = s->next->num;
	num[2] = s->next->next->num;
	if (num[0] < num[1] && num[0] < num[2] && num[1] < num[2])
		return (s);
	if (num[0] > num[1] && num[0] < num[2] && num[1] < num[2])
		out = do_s(s, 'a');
	else if (num[0] > num[1] && num[0] > num[2] && num[1] > num[2])
	{
		out = do_s(s, 'a');
		out = do_rr(out, 'a');
	}
	else if (num[0] > num[1] && num[0] > num[2] && num[1] < num[2])
		out = do_r(s, 'a');
	else if (num[0] < num[1] && num[0] < num[2] && num[1] > num[2])
	{
		out = do_s(s, 'a');
		out = do_r(out, 'a');
	}
	else
		out = do_rr(s, 'a');
	return (out);
}

static t_d_stack	sort_3(t_d_stack s)
{
	t_stack	*out;

	out = s.a;
	if (s.max == 1)
		return (s);
	if (s.max == 2)
	{
		if (out->num > out->next->num)
			out = do_s(out, 'a');
	}
	if (s.max == 3)
		out = proc_sort_3(out);
	s.a = out;
	return (s);
}

t_d_stack	parse_2_sort(t_d_stack s)
{
	t_stack	*t;

	t = get_last_lst(s.a);
	s.a->prev = t;
	t->next = s.a;
	if (s.max <= 3)
		s = sort_3(s);
	if (s.max > 3 && s.max <= 30)
		s = sort_insert(s);
	if (s.max > 30)
		s = sort_radix(s);
	t = s.a->prev;
	s.a->prev = NULL;
	t->next = NULL;
	return (s);
}

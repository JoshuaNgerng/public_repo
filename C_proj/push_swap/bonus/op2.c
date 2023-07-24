/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:37:48 by jngerng           #+#    #+#             */
/*   Updated: 2023/07/19 16:37:48 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check.h"

static t_stack	*do_p_mov(t_stack *in, t_stack **get, UINT len)
{
	t_stack	*out;
	t_stack	*t;

	if (!in)
		return (NULL);
	out = in->next;
	t = in->prev;
	*get = in;
	(*get)->next = NULL;
	(*get)->prev = NULL;
	if (len == 1)
		return (NULL);
	out->prev = t;
	t->next = out;
	return (out);
}

static	t_stack	*do_p_add(t_stack *in, t_stack *add)
{
	t_stack	*out;
	t_stack	*l;

	if (!in)
		return (add);
	if (!in->next || !in->prev)
	{
		out = add;
		out->next = in;
		in->prev = out;
		out->prev = in;
		in->next = out;
		return (out);
	}
	out = add;
	l = in->prev;
	l->next = out;
	out->prev = l;
	out->next = in;
	in->prev = out;
	return (out);
}

t_d_stack	do_p(t_d_stack start, char stack)
{
	t_d_stack	out;
	t_stack		*temp;

	out = start;
	temp = NULL;
	if (stack == 'a')
	{
		if (out.b_len == 0)
			return (out);
		out.b = do_p_mov(out.b, &temp, out.b_len);
		out.a = do_p_add(out.a, temp);
		out.a_len ++;
		out.b_len --;
	}
	if (stack == 'b')
	{
		if (out.a_len == 0)
			return (out);
		out.a = do_p_mov(out.a, &temp, out.a_len);
		out.b = do_p_add(out.b, temp);
		out.b_len ++;
		out.a_len --;
	}
	return (out);
}

t_d_stack	do_both(t_d_stack start, char cmd)
{
	t_d_stack	out;

	out = start;
	if (cmd == 'v')
	{
		out.a = do_rr(out.a);
		out.b = do_rr(out.b);
	}
	if (cmd == 'r')
	{
		out.a = do_r(out.a);
		out.b = do_r(out.b);
	}
	if (cmd == 's')
	{
		out.a = do_s(out.a);
		out.b = do_s(out.b);
	}
	return (out);
}

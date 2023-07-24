/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/03 10:29:16 by jngerng           #+#    #+#             */
/*   Updated: 2023/07/03 10:29:16 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	write_cmd(char *cmd, char s, int l)
{
	if (s)
	{
		write(1, cmd, l);
		write(1, &s, 1);
		write(1, "\n", 1);
	}
}

t_stack	*do_s(t_stack *start, char s)
{
	t_stack	*out;
	t_stack	*t;

	out = start;
	if (!out)
		return (write_cmd("s", s, 1), NULL);
	if (!out->next)
		return (write_cmd("s", s, 1), out);
	if (start->next)
	{
		out = start->next;
		t = out->next;
		start->next = t;
		t->prev = start;
		t = start->prev;
		start->prev = out;
		out->next = start;
		out->prev = t;
		t->next = out;
	}
	write_cmd("s", s, 1);
	return (out);
}

t_stack	*do_r(t_stack *start, char s)
{
	t_stack	*out;

	out = NULL;
	if (!start)
		return (write_cmd("r", s, 1), NULL);
	if (start->next)
		out = start->next;
	write_cmd("r", s, 1);
	return (out);
}

t_stack	*do_rr(t_stack *start, char s)
{
	t_stack	*out;

	out = NULL;
	if (!start)
		return (write_cmd("rr", s, 2), NULL);
	if (start->next)
		out = start->prev;
	write_cmd("rr", s, 2);
	return (out);
}

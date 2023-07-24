/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:37:43 by jngerng           #+#    #+#             */
/*   Updated: 2023/07/19 16:37:43 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check.h"

t_stack	*do_s(t_stack *start)
{
	t_stack	*out;
	t_stack	*t;

	out = start;
	if (!out)
		return (NULL);
	if (!out->next)
		return (out);
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
	return (out);
}

t_stack	*do_r(t_stack *start)
{
	t_stack	*out;

	out = NULL;
	if (!start)
		return (NULL);
	if (start->next)
		out = start->next;
	return (out);
}

t_stack	*do_rr(t_stack *start)
{
	t_stack	*out;

	out = NULL;
	if (!start)
		return (NULL);
	if (start->next)
		out = start->prev;
	return (out);
}

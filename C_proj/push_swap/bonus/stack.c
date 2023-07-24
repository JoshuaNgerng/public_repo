/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:37:52 by jngerng           #+#    #+#             */
/*   Updated: 2023/07/19 16:37:52 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check.h"

t_stack	*get_node(int num)
{
	t_stack	*s;

	s = (t_stack *) malloc (sizeof(t_stack));
	if (!s)
		return (NULL);
	s->num = num;
	s->prev = NULL;
	s->next = NULL;
	return (s);
}

// t_stack	*get_stack(int *ref, UINT siz)
// {
// 	UINT	i;
// 	t_stack	*temp;
// 	t_stack	*start;
// 	t_stack	*new;

// 	i = 0;
// 	start = get_node(ref[i]);
// 	if (!start)
// 		return (NULL);
// 	temp = start;
// 	while (++ i < siz)
// 	{
// 		new = get_node(ref[i]);
// 		if (!new)
// 			return (free_stack(start), NULL);
// 		temp->next = new;
// 		new->prev = temp;
// 		temp = temp->next;
// 	}
// 	temp->next = NULL;
// 	return (start);
// }

t_stack	*get_last_lst(t_stack *s)
{
	t_stack	*t;

	t = s;
	while (t)
	{
		if (!t->next)
			break ;
		t = t->next;
	}
	return (t);
}

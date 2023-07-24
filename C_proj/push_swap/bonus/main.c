/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:37:37 by jngerng           #+#    #+#             */
/*   Updated: 2023/07/19 16:37:37 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check.h"

static int	check_max_min(char *s, int sign)
{
	if (!sign)
		if ((ft_strncmp(s, "2147483647", 10)) > 0)
			return (1);
	if (sign)
		if ((ft_strncmp(s, "2147483648", 10)) > 0)
			return (1);
	return (0);
}

static UINT	check_err(char **av, UINT i, UINT j)
{
	int		s;
	UINT	k;

	k = 0;
	s = 0;
	if (j != 0)
		if (av[i][j - 1] == '-')
			s = 1;
	if (ft_checkset(av[i][j], "+-") && !ft_isdigit(av[i][j + 1]))
		err_msg();
	if (av[i][j] && !ft_isdigit(av[i][j]) && !ft_checkset(av[i][j], "+- "))
		err_msg();
	if (ft_isdigit(av[i][j]))
		while (ft_isdigit(av[i][j + k]))
			k ++;
	if (k > 10)
		err_msg();
	if (k == 10)
		if (check_max_min(&av[i][j], s))
			err_msg();
	if (k > 0)
		k --;
	return (k);
}

static UINT	get_len(UINT ac, char **av)
{
	t_check	c;

	c = (struct s_check){0, 0, 0, 0};
	while (++ c.i < ac)
	{
		c.j = 0;
		c.temp = 1;
		if ((av[c.i][c.j] == '\0') ||
			((ft_checkset(av[c.i][c.j], "+-")) && !av[c.i][c.j + 1]))
			err_msg();
		if (av[c.i][c.j] == ' ')
			c.temp = 0;
		while (av[c.i][++ c.j])
		{
			if (av[c.i][c.j] == ' ' && av[c.i][c.j + 1] != ' '
				&& av[c.i][c.j] != '\0')
				c.temp ++;
			c.j += check_err(av, c.i, c.j);
		}
		if (c.temp == 0)
			err_msg();
		c.out += c.temp;
	}
	return (c.out);
}

static t_stack	*get_stack(char **av)
{
	t_check	c;
	t_stack	*out;
	t_stack	*t;
	t_stack	*new;

	c = (t_check){0, 0, 0, 0};
	out = get_node(0);
	if (!out)
		return (NULL);
	t = out;
	while (av[++ c.i])
	{
		c.j = 0;
		while (av[c.i][c.j])
		{
			new = get_node(ft_ssp_atoi(&av[c.i][c.j], &c.temp));
			if (!new)
				return (free_stack(out), NULL);
			t->next = new;
			new->prev = t;
			t = t->next;
			c.j += c.temp;
		}
	}
	t = out;
	out = out->next;
	return (free(t), out);
}

int	main(int ac, char **av)
{
	t_d_stack	stack;
	t_stack		*l;

	if (ac < 2)
		return (0);
	stack = (struct s_d_stack){get_len((UINT)ac, av), 0, 0, NULL, NULL};
	stack.max = stack.a_len;
	stack.a = get_stack(av);
	if (!stack.a)
		err_msg();
	l = get_last_lst(stack.a);
	l->next = stack.a;
	stack.a->prev = l;
	stack = sort(stack);
	if (check_lst(stack.a, stack.a_len, stack.max))
	{
		free_2_stack(stack);
		err_msg();
	}
	write(1, "OK\n", 3);
	return (free_2_stack(stack), 0);
}

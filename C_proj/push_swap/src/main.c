/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 01:50:43 by jngerng           #+#    #+#             */
/*   Updated: 2023/07/02 01:50:43 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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
		c.j = -1;
		c.temp = 1;
		if (av[c.i][0] == '\0')
			err_msg();
		if (av[c.i][0] == ' ')
			c.temp = 0;
		while (av[c.i][++ c.j])
		{
			if (av[c.i][c.j] == ' ' && (av[c.i][c.j + 1] != ' '
				&& av[c.i][c.j + 1] != '\0'))
				c.temp ++;
			c.j += check_err(av, c.i, c.j);
		}
		if (c.temp == 0)
			err_msg();
		c.out += c.temp;
	}
	return (c.out);
}

static int	*v_get_num(char **av, UINT siz)
{
	UINT	i;
	UINT	j;
	UINT	l;
	UINT	w;
	int		*out;

	i = 0;
	w = 0;
	l = 0;
	out = (int *) malloc (siz * sizeof(int));
	if (!out)
		return (NULL);
	while (av[++ i])
	{
		j = 0;
		while (av[i][j])
		{
			out[w] = ft_ssp_atoi(&av[i][j], &l);
			w ++;
			j += l;
		}
	}
	return (out);
}

// static t_d_stack	prompt(void)
// {
// 	t_d_stack	out;
// 	char		*temp;
// 	char		*av[3];

// 	out = (t_d_stack){0, 0, 0, NULL, NULL, NULL, NULL};
// 	temp = get_next_line(0);
// 	if (!temp)
// 		err_msg();
// 	temp[ft_strlen(temp) - 2] = '\0';
// 	av[1] = temp;
// 	av[2] = NULL;
// 	out.max = get_len(2, av);
// 	out.a_len = out.max;
// 	out.ref = v_get_num(av, out.max);
// 	free(temp);
// 	return (out);
// }

int	main(int ac, char **av)
{
	t_d_stack	stack;

	if (ac < 2)
		return (0);
	stack = (struct s_d_stack){get_len((UINT)ac, av), 0, 0, \
								NULL, NULL, NULL, NULL};
	stack.max = stack.a_len;
	stack.ref = v_get_num(av, stack.a_len);
	if (!stack.ref)
		return (err_msg(), 1);
	if (!check_ord(stack.ref, stack.a_len))
		return (free(stack.ref), 0);
	stack.sorted = (int *) malloc (stack.a_len * sizeof(int));
	if (!stack.sorted)
		return (free(stack.ref), err_msg(), 1);
	if (sort_check(stack.sorted, stack.ref, stack.a_len))
		return (free(stack.ref), free(stack.sorted), err_msg(), 1);
	stack.a = get_stack(stack.ref, stack.sorted, stack.a_len);
	free(stack.ref);
	free(stack.sorted);
	if (!stack.a)
		return (err_msg(), 1);
	stack = parse_2_sort(stack);
	return (free_stack(stack.a), 0);
}

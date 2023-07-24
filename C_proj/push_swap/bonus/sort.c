/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 17:50:40 by jngerng           #+#    #+#             */
/*   Updated: 2023/07/19 17:50:40 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "check.h"

static int	check_2_cmd(char *line, char *stack, char cmd, char *end)
{
	if (line[0] == cmd)
	{
		if (ft_checkset(line[1], end))
		{
			*stack = line[1];
			return (1);
		}
	}
	return (0);
}

static char	check_cmd(char *line, char *stack, int len)
{
	if (len == 3)
	{
		if (!ft_strncmp(line, "rr", len - 1))
		{
			if (ft_checkset(line[len - 1], "abr"))
			{
				*stack = line[len - 1];
				return ('v');
			}
		}
	}
	if (len == 2)
	{
		if (check_2_cmd(line, stack, 's', "abs"))
			return ('s');
		if (check_2_cmd(line, stack, 'r', "abr"))
			return ('r');
		if (check_2_cmd(line, stack, 'p', "ab"))
			return ('p');
	}
	return (-1);
}

static char	get_cmd(char *stack)
{
	char	*line;
	char	out;
	int		l;

	line = get_next_line(0);
	if (!line)
		return ('\0');
	if (line[0] == '\n' || line[0] == '\0')
		return (free(line), '\0');
	l = ft_strlen(line) - 1;
	if (l < 2 || l > 3)
		return (free(line), -1);
	out = check_cmd(line, stack, l);
	return (free(line), out);
}

static t_d_stack	single_cmd(t_d_stack stack, char s, \
								t_stack *(*f)(t_stack *))
{
	if (s == 'a')
		stack.a = f(stack.a);
	else
		stack.b = f(stack.b);
	return (stack);
}

t_d_stack	sort(t_d_stack stack)
{
	char	cmd;
	char	s;

	s = '\0';
	cmd = get_cmd(&s);
	while (cmd > 0)
	{
		if (s == 'r' || s == 's')
			stack = do_both(stack, cmd);
		if (cmd == 'r')
			stack = single_cmd(stack, s, &do_r);
		if (cmd == 's')
			stack = single_cmd(stack, s, &do_s);
		if (cmd == 'v')
			stack = single_cmd(stack, s, &do_rr);
		if (cmd == 'p')
			stack = do_p(stack, s);
		cmd = get_cmd(&s);
	}
	if (cmd < 0)
	{
		free_2_stack(stack);
		err_msg();
	}
	return (stack);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 16:45:42 by jngerng           #+#    #+#             */
/*   Updated: 2023/07/19 16:45:42 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECK_H
# define CHECK_H
# define UINT unsigned int
# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_stack
{
	int				num;
	struct s_stack	*next;
	struct s_stack	*prev;
}	t_stack;

typedef struct s_d_stack
{
	UINT	a_len;
	UINT	b_len;
	UINT	max;
	t_stack	*a;
	t_stack	*b;
}	t_d_stack;

typedef struct s_check
{
	UINT	i;
	UINT	j;
	UINT	temp;
	UINT	out;
}	t_check;

void		err_msg(void);
int			ft_ssp_atoi(char *s, UINT *i);
void		free_stack(t_stack *start);
void		free_2_stack(t_d_stack s);
t_stack		*get_last_lst(t_stack *s);
t_stack		*get_node(int num);
t_stack		*do_rr(t_stack *start);
t_stack		*do_s(t_stack *start);
t_stack		*do_r(t_stack *start);
t_d_stack	do_p(t_d_stack start, char stack);
t_d_stack	do_both(t_d_stack start, char cmd);
t_d_stack	sort(t_d_stack stack);
int			check_lst(t_stack *a, UINT len, UINT max);

#endif
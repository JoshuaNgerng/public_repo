/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:18:13 by jngerng           #+#    #+#             */
/*   Updated: 2023/06/05 15:18:13 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H
# define UINT unsigned int
# include "libft.h"
# include "ft_printf.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>

typedef struct s_stack
{
	UINT			num;
	struct s_stack	*next;
	struct s_stack	*prev;
}	t_stack;

typedef struct s_d_stack
{
	UINT	a_len;
	UINT	b_len;
	UINT	max;
	int		*ref;
	int		*sorted;
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

typedef struct s_bin_search
{
	UINT	low;
	UINT	mid;
	UINT	high;
}	t_bin_search;


typedef struct s_merge
{
	int	len1;
	int	len2;
	int	*left;
	int	*right;
	int	k;
}	t_merge;

typedef struct s_radix
{
	UINT	*neg;
	UINT	*pos;
	UINT	neg_len;
	UINT	neg_max;
	UINT	pos_len;
	UINT	pos_max;
}	t_radix;

typedef struct s_para
{
	UINT	num;
	UINT	prev;
	UINT	c;
}	t_para;

typedef struct s_proc
{
	t_stack	*s;
	UINT	piv;
}	t_proc;

void		err_msg(void);
int			int_min(int a, int b);
UINT		uint_min(UINT a, UINT b);
int			ft_ssp_atoi(char *s, UINT *i);
int			sort_check(int *out, int *in, int len);
UINT		count_neg_num(int *in, UINT siz);
int			int_min(int a, int b);
int			*insertionsort(int in[], int len);
int			*timsort(int in[], int len);
int			*radixsort(int in[], UINT len);
int			check_ord(int *arr, int siz);
int			check_lst(t_stack *in, UINT siz);
t_stack		*get_last_lst(t_stack *s);
void		free_stack(t_stack *start);
t_stack		*get_stack(int *ref, int *sorted, UINT siz);
t_stack		*do_rr(t_stack *start, char s);
t_stack		*do_s(t_stack *start, char s);
t_stack		*do_r(t_stack *start, char s);
t_d_stack	do_p(t_d_stack start, char stack);
t_d_stack	do_both(t_d_stack start, char cmd);
t_d_stack	parse_2_sort(t_d_stack s);
t_stack		*get_2_top(t_stack *s, UINT ref, UINT len, char p);
t_stack		*proc_sort_3(t_stack *st);
t_stack		*proc_sort_3_b(t_stack *st);
t_d_stack	proc_sort_5(t_d_stack s);
t_d_stack	proc_sort_6(t_d_stack s);
int			int_sort_3_b(t_stack *s);
int			int_sort_3_a(t_stack *s);
t_d_stack	sort_insert(t_d_stack s);
t_d_stack	sort_radix(t_d_stack s);

#endif
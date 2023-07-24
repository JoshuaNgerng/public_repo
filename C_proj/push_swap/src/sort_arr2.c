/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_arr2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 09:51:53 by jngerng           #+#    #+#             */
/*   Updated: 2023/06/16 09:51:53 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	get_max(UINT *arr, UINT len)
{
	UINT	i;
	UINT	max;
	UINT	out;

	i = 0;
	out = 0;
	max = arr[i];
	while (++ i < len)
	{
		if (max < arr[i])
			max = arr[i];
	}
	while (max > 0)
	{
		out ++;
		max /= 10;
	}
	return (out);
}

static t_radix	get_arr(t_radix buff, int *in, UINT siz)
{
	UINT	i;
	UINT	j;
	UINT	k;

	i = 0;
	j = 0;
	k = 0;
	while (++ i < siz)
	{
		if (in[i] < 0)
		{
			buff.neg[j] = -in[i];
			j ++;
		}
		else
		{
			buff.pos[k] = in[i];
			k ++;
		}
		i ++;
	}
	return (buff);
}

static UINT	*proc_count_sort(UINT *in, UINT siz, int place)
{
	UINT	i;
	UINT	pos[10];
	UINT	*out;

	ft_bzero(pos, 10 * sizeof(UINT));
	out = (UINT *) malloc (siz * sizeof(UINT));
	if (!out)
		return (NULL);
	i = -1;
	while (++ i < siz)
		pos[(in[i] / place) % 10]++;
	i = 0;
	while (++ i < 10)
		pos[i] += pos[i - 1];
	i = siz;
	while (1)
	{
		i --;
		out[pos[(in[i] / place) % 10] - 1] = in[i];
		pos[(in[i] / place) % 10]--;
		if (i == 0)
			break ;
	}
	free(in);
	return (out);
}

static t_radix	proc_radix(int *in, t_radix buff)
{
	UINT	i;
	UINT	pos;
	UINT	max;

	i = 0;
	pos = 1;
	max = buff.neg_len + buff.pos_len;
	while (i < buff.neg_max || i < buff.pos_max)
	{
		if (i < buff.neg_max)
			buff.neg = proc_count_sort(buff.neg, buff.neg_len, pos);
		if (i < buff.pos_max)
			buff.pos = proc_count_sort(buff.pos, buff.pos_len, pos);
		if (!buff.pos || ! buff.neg)
			return (buff);
		pos *= 10;
		i ++;
	}
	i = -1;
	while (++ i < buff.neg_len)
		in[i] = buff.neg[buff.neg_len - i - 1] * -1;
	i --;
	while (++ i < max)
		in[i] = buff.pos[i - buff.neg_len];
	return (buff);
}

int	*radixsort(int *in, UINT siz)
{
	t_radix	buff;
	UINT	i;

	i = -1;
	buff.neg_len = 0;
	while (++ i < siz)
		if (in[i] < 0)
			buff.neg_len ++;
	buff.pos_len = siz - buff.neg_len;
	buff.neg = (UINT *) malloc (buff.neg_len * sizeof(UINT));
	if (!buff.neg)
		return (NULL);
	buff.pos = (UINT *) malloc (buff.pos_len * sizeof(UINT));
	if (!buff.pos)
		return (free(buff.pos), NULL);
	buff = get_arr(buff, in, siz);
	buff.neg_max = get_max(buff.neg, buff.neg_len);
	buff.pos_max = get_max(buff.pos, buff.pos_len);
	buff = proc_radix(in, buff);
	if (!buff.neg || !buff.pos)
		return (NULL);
	free(buff.neg);
	free(buff.pos);
	return (in);
}

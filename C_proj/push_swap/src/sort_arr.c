/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 09:42:20 by jngerng           #+#    #+#             */
/*   Updated: 2023/06/16 09:42:20 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	*insertionsort(int in[], int len)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	while (++ i < len)
	{
		j = i - 1;
		temp = in[i];
		while (temp < in[j] && j >= 0)
		{
			in[j + 1] = in[j];
			j --;
			if (j == -1)
				break ;
		}
		in[j + 1] = temp;
	}
	return (in);
}

static void	proc_merge(int arr[], t_merge buff)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < buff.len1 && j < buff.len2)
	{
		if (buff.left[i] <= buff.right[j])
			arr[buff.k] = buff.left[i ++];
		else
			arr[buff.k] = buff.right[j ++];
		buff.k++;
	}
	while (i < buff.len1)
		arr[buff.k ++] = buff.left[i ++];
	while (j < buff.len2)
		arr[buff.k ++] = buff.right[j ++];
}

static int	*mergesort(int arr[], int l, int m, int r)
{
	t_merge	buff;

	buff.len1 = m - l;
	buff.len2 = r - m;
	buff.k = l;
	buff.left = (int *) malloc (buff.len1 * sizeof(int));
	if (!buff.left)
		return (NULL);
	buff.right = (int *) malloc (buff.len2 * sizeof(int));
	if (!buff.left)
		return (free(buff.left), NULL);
	ft_memmove(buff.left, &arr[l], buff.len1 * sizeof(int));
	ft_memmove(buff.right, &arr[m], buff.len2 * sizeof(int));
	proc_merge(arr, buff);
	free(buff.left);
	free(buff.right);
	return (arr);
}

int	*timsort(int in[], int len)
{
	int	i;
	int	j;
	int	mid;
	int	end;

	i = -1;
	while (++ i <= len / 32)
		insertionsort(&in[i * 32], int_min(32, len - i * 32));
	i = 32;
	while (i <= len)
	{
		j = 0;
		while (j < len)
		{
			mid = j + i;
			end = int_min((j + 2 * i), len);
			if (mid < end)
				mergesort(in, j, mid, end);
			j += 2 * i;
		}
		i *= 2;
	}
	return (in);
}

int	sort_check(int *out, int *in, int len)
{
	int	i;

	ft_memcpy(out, in, len * sizeof(int));
	if (len < 30)
		out = insertionsort(out, len);
	if (len >= 30 && len < 1000)
		out = timsort(out, len);
	if (len >= 1000)
		out = radixsort(out, len);
	if (!out)
		return (1);
	i = 0;
	while (++ i < len)
	{
		if (out[i - 1] == out[i])
			return (1);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_strs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 23:10:21 by jngerng           #+#    #+#             */
/*   Updated: 2023/07/17 23:10:21 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_strs(char **s)
{
	unsigned int	i;

	i = -1;
	if (!s)
		return ;
	while (s[++ i])
		free(s[i]);
	free(s);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utlis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 22:58:40 by jngerng           #+#    #+#             */
/*   Updated: 2023/08/03 08:10:22 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	rm_nl(char *dst, int len)
{
	while (dst[len - 1] == '\n' || dst[len - 1] == '\r')
	{
		dst[len - 1] = '\0';
		len --;
	}
	return (len);
}

t_game	check_border(char *line, t_game g)
{
	int	l;
	int	i;

	if (!line && !g.map)
		return (g);
	l = rm_nl(line, ft_strlen(line));
	i = -1;
	while (line[++ i])
	{
		if (line[i] != '1')
			p(err_msg(3), free_exit(g, 1));
	}
	if (!g.size.y)
		g.size.y = l;
	else
	{
		if (l != g.size.y)
			p(err_msg(3), free_exit(g, 1));
	}
	return (g);
}

int	check_line(t_game *in, char *new_l, int n)
{
	int	i;

	i = -1;
	rm_nl(new_l, ft_strlen(new_l));
	while (new_l[++ i])
	{
		if (new_l[i] == 'C')
			in->item.col ++;
		else if (new_l[i] == 'P')
		{
			in->item.ply ++;
			in->ply.pos = (t_point){n, i};
		}
		else if (new_l[i] == 'E')
			in->item.ext ++;
		else if (new_l[i] == 'D')
			in->item.ene ++;
		else if (new_l[i] != '0' && new_l[i] != '1')
			return (sp_err_msg(0, &new_l[i]), 1);
	}
	if (new_l[i - 1] != '1' || new_l[0] != '1')
		return (err_msg(3), 1);
	if (in->size.y != i)
		return (err_msg(4), 1);
	return (0);
}

char	*msg_steps_taken(t_game g)
{
	int		len;
	char	*out;
	char	*num;

	num = ft_itoa(g.steps);
	if (!num)
		return (sp_err_msg(2, "ft_itoa"), free_exit(g, 1), NULL);
	len = ft_strlen(num);
	out = (char *) malloc ((25 + len) * sizeof(char));
	if (!out)
		return (free(num), sp_err_msg(2, "msg_steps_taken"), \
				free_exit(g, 1), NULL);
	ft_strlcpy(out, "Player have taken ", 19);
	ft_strlcpy(&out[18], num, len + 1);
	ft_strlcpy(&out[18 + len], " steps", 7);
	return (free(num), out);
}

void	*p(void *f1, void *f2)
{
	(void)f1;
	(void)f2;
	return (NULL);
}


void	dev_print_map(char **map)
{
	int	c;
	int	i;

	i = -1;
	while (map[++ i])
	{
		c = write(1, map[i], ft_strlen(map[i]));
		c = write(1, "\n", 1);
		if (c == -1)
			return ;
	}
	c = write(1, "END\n", 4);
}

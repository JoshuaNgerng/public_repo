/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jngerng <jngerng@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 13:19:29 by jngerng           #+#    #+#             */
/*   Updated: 2023/11/17 01:38:18 by jngerng          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	check_wall(char **map, int *wall, t_point p, int i)
{
	printf("test %d %d %d %d %d %d\n", p.x, p.y, p.x - i, p.x + i, p.y - i, p.y + i);
	if (map[p.x - i][p.y] == '1' || map[p.x - i][p.y] == 'X')
		wall[0] = 1;
	if (map[p.x + i][p.y] == '1' || map[p.x + i][p.y] == 'X')
		wall[1] = 1;
	if (map[p.x][p.y - i] == '1' || map[p.x][p.y - i] == 'X')
		wall[2] = 1;
	if (map[p.x][p.y + i] == '1' || map[p.x][p.y + i] == 'X')
		wall[3] = 1;
}

char	check_nearby_ply(t_game g, t_point p)
{
	int	limit;
	int	i;
	int	*wall;

	limit = 5;
	i = -1;
	wall = (int[]){0, 0, 0, 0};
	while (++ i < limit)
	{
		if (p.x - i > 0)
			if (g.map[p.x - i][p.y] == 'P' && !wall[0])
				return ('u');
		if (p.x + i < g.size.x)
			if (g.map[p.x + i][p.y] == 'P' && !wall[1])
				return ('d');
		if (p.y - i > 0)
			if (g.map[p.x][p.y - i] == 'P' && !wall[2])
				return ('l');
		if (p.x + i < g.size.y)
			if (g.map[p.x][p.y + i] == 'P' && !wall[3])
				return ('r');
		check_wall(g.map, wall, p, i);
	}
	return (0);
}

char	calm_patrol_loop(t_game *g, int num)
{
	int		i;
	int		x;
	int		y;
	int		counter;
	char	*buffer;

	if (!process_enemy_move(g->enemy[num].move_direct, g, num))
		return (g->enemy[num].move_direct);
	counter = 0;
	buffer = "lrud";
	x = g->enemy[num].pos.x * PIX_SIZE + 10;
	y = g->enemy[num].pos.y * PIX_SIZE + 10;
	if (g->enemy[num].move_direct == 'l')
		counter = 1;
	else if (g->enemy[num].move_direct == 'r')
		counter = 2;
	mlx_put_image_to_window(g->mlx.init, g->mlx.win, \
							g->entity.enemy.idle[counter], y, x);
	i = -1;
	while (buffer[++ i])
		if (buffer[i] == g->enemy[num].move_direct)
			break ;
	g->enemy[num].move_direct = buffer[i + 1];
	if (!g->enemy[num].move_direct)
		return ('l');
	return (g->enemy[num].move_direct);
}

void	check_prev_location(t_game *g, int i, t_point prev)
{
	if (!g->enemy[i].block)
	{
		g->map[prev.x][prev.y] = '0';
		return ;
	}
	g->enemy[i].block --;
	if (g->enemy[i].block)
		g->map[prev.x][prev.y] = '0';
	else
		g->map[prev.x][prev.y] = 'C';	
}

void	loop_anime(t_game *g, int i, void **anime, t_point prev)
{
	int	y;
	int	x;

	y = (g->enemy[i].pos.y + prev.y) / 2 * PIX_SIZE + 10;
	x = (g->enemy[i].pos.x + prev.x) / 2 * PIX_SIZE + 10;
	mlx_put_image_to_window(g->mlx.init, g->mlx.win, \
							anime[g->enemy[i].counter], y, x);
	g->enemy[i].counter ++;
	if (!anime[g->enemy[i].counter])
	{
		g->enemy[i].move_status = 0;
		g->enemy[i].counter = 0;
		y = prev.y * PIX_SIZE + 10;
		x = prev.x * PIX_SIZE + 10;
		mlx_put_image_to_window(g->mlx.init, g->mlx.win, \
								g->entity.floor, y, x);
		check_prev_location(g, i, prev);
	}
}

void	enemy_anime(t_game *g, int i)
{
	// printf("test1 enemy\n");
	if (!g->enemy[i].move_status)
	{
		g->enemy[i].move_direct = calm_patrol_loop(g, i);
		// g->enemy[i].move_direct = check_nearby_ply(*g, g->enemy[i].pos);
		// if (!g->enemy[i].move_direct)
		// 	g->enemy[i].move_direct = calm_patrol_loop(g, i);
		// else
		// 	process_enemy_move(g->enemy[i].move_direct, g, i);
		g->enemy[i].counter = 0;
	}
	if (g->enemy[i].move_status)
	{
		if (g->enemy[i].move_direct == 'u')
			loop_anime(g, i, g->entity.enemy.up, \
						(t_point){g->enemy[i].pos.x + 1, g->enemy[i].pos.y});
		if (g->enemy[i].move_direct == 'd')
			loop_anime(g, i, g->entity.enemy.down, \
						(t_point){g->enemy[i].pos.x - 1, g->enemy[i].pos.y});
		if (g->enemy[i].move_direct == 'r')
			loop_anime(g, i, g->entity.enemy.right, \
						(t_point){g->enemy[i].pos.x, g->enemy[i].pos.y - 1});
		if (g->enemy[i].move_direct == 'l')
			loop_anime(g, i, g->entity.enemy.left, \
						(t_point){g->enemy[i].pos.x, g->enemy[i].pos.y + 1});
	}
}

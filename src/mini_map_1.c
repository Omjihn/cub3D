/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 13:11:06 by ashalagi          #+#    #+#             */
/*   Updated: 2023/12/12 11:23:18 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_map_element(t_data *data, int mini_map_x, \
									int mini_map_y, int color)
{
	int	dy;
	int	dx;

	dy = 0;
	while (dy < MINI_MAP_SCALE)
	{
		dx = 0;
		while (dx < MINI_MAP_SCALE)
		{
			img_pix_put(&data->img, mini_map_x + dx, mini_map_y + dy, color);
			dx++;
		}
		dy++;
	}
}

static void	process_mini_map_row(t_data *data, int y)
{
	t_coords	mini_map;
	int			x;
	int			color;

	x = 0;
	while (x < data->map_max_x)
	{
		mini_map.x = X_OFFSET + (x * MINI_MAP_SCALE);
		mini_map.y = Y_OFFSET + (y * MINI_MAP_SCALE);
		if (!ft_should_draw(mini_map.x, mini_map.y))
		{
			x++;
			continue ;
		}
		color = ft_put_color(data->map[y][x]);
		if (color == -1)
		{
			x++;
			continue ;
		}
		draw_map_element(data, mini_map.x, mini_map.y, color);
		x++;
	}
}

void	ft_draw_mini_map(t_data *data)
{
	int	y;

	y = 0;
	while (y < data->map_max_y)
	{
		process_mini_map_row(data, y);
		y++;
	}
	ft_draw_mini_player(data);
}

static void	ft_draw_indicator(t_data *data)
{
	t_coords	d;
	t_coords	map;
	t_coords	direction;
	float		angle;
	int			i;

	angle = ft_deg_to_rad(data->player->angle + 90);
	map.x = X_OFFSET + (int)(data->player->pos.x * MINI_MAP_SCALE) \
			- MINI_MAP_SCALE / 4;
	map.y = Y_OFFSET + (int)(data->player->pos.y * MINI_MAP_SCALE) \
			- MINI_MAP_SCALE / 4;
	d.x = (int)(-cosf(angle) * MINI_MAP_SCALE);
	d.y = (int)(sinf(angle) * MINI_MAP_SCALE);
	i = 0;
	while (i < MINI_MAP_SCALE)
	{
		direction.x = map.x + (d.x * i) / MINI_MAP_SCALE;
		direction.y = map.y + (d.y * i) / MINI_MAP_SCALE;
		if (i >= (MINI_MAP_SCALE / 2) / 2)
			img_pix_put(&data->img, direction.x, direction.y, 0xFF0000);
		i++;
	}
}

void	ft_draw_mini_player(t_data *data)
{
	t_coords	p;
	t_coords	player_map;

	p.y = -1;
	player_map.x = X_OFFSET + (int)(data->player->pos.x * MINI_MAP_SCALE) \
					- MINI_MAP_SCALE / 4;
	player_map.y = Y_OFFSET + (int)(data->player->pos.y * MINI_MAP_SCALE) \
					- MINI_MAP_SCALE / 4;
	while (++p.y < (MINI_MAP_SCALE / 2))
	{
		p.x = 0;
		while (p.x < (MINI_MAP_SCALE / 2))
		{
			if (player_map.x + MINI_MAP_SCALE > SCREENWIDTH || player_map.y \
				+ MINI_MAP_SCALE > SCREENHEIGHT)
			{
				p.x++;
				return ;
			}
			img_pix_put(&data->img, player_map.x + p.x - (MINI_MAP_SCALE / 2) \
				/ 2, player_map.y + p.y - (MINI_MAP_SCALE / 2) / 2, 0xFF0000);
			p.x++;
		}
	}
	ft_draw_indicator(data);
}

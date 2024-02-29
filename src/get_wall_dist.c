/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_wall_dist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 10:47:53 by gbricot           #+#    #+#             */
/*   Updated: 2023/12/12 10:56:02 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_get_side_dist(t_data *data)
{
	if (data->rcast->raydir.x < 0)
	{
		data->rcast->step.x = -1;
		data->rcast->sidedist.x = (data->rcast->pos.x - data->rcast->map.x) \
			* data->rcast->deltadist.x;
	}
	else
	{
		data->rcast->step.x = 1;
		data->rcast->sidedist.x = (data->rcast->map.x + 1.0 \
			- data->rcast->pos.x) * data->rcast->deltadist.x;
	}
	if (data->rcast->raydir.y < 0)
	{
		data->rcast->step.y = -1;
		data->rcast->sidedist.y = (data->rcast->pos.y \
			- data->rcast->map.y) * data->rcast->deltadist.y;
	}
	else
	{
		data->rcast->step.y = 1;
		data->rcast->sidedist.y = (data->rcast->map.y + 1.0 \
			- data->rcast->pos.y) * data->rcast->deltadist.y;
	}
}

char	ft_wall_found(t_data *data)
{
	if (data->rcast->map.x >= 0 && data->rcast->map.x <= data->map_max_x \
		&& data->rcast->map.y >= 0 && data->rcast->map.y < data->map_max_y)
	{
		if ((data->map[data->rcast->map.y][data->rcast->map.x] >= '1' && \
			data->map[data->rcast->map.y][data->rcast->map.x] <= '2') || \
			data->map[data->rcast->map.y][data->rcast->map.x] == 'D')
		{
			data->rcast->wall_type = \
				&data->map[data->rcast->map.y][data->rcast->map.x];
			return (1);
		}
	}
	else
		return (1);
	return (0);
}

void	ft_search_wall(t_data *data)
{
	int		hit;

	hit = 0;
	while (hit == 0)
	{
		if (data->rcast->sidedist.x < data->rcast->sidedist.y)
		{
			data->rcast->sidedist.x += data->rcast->deltadist.x;
			data->rcast->map.x += data->rcast->step.x;
			data->rcast->side = 0;
		}
		else
		{
			data->rcast->sidedist.y += data->rcast->deltadist.y;
			data->rcast->map.y += data->rcast->step.y;
			data->rcast->side = 1;
		}
		hit = ft_wall_found(data);
	}
}

void	ft_get_perp_wall_dist(t_data *data)
{
	if (data->rcast->side == 0)
		data->rcast->perp_wall_dist = (data->rcast->sidedist.x \
			- data->rcast->deltadist.x);
	else
		data->rcast->perp_wall_dist = (data->rcast->sidedist.y \
			- data->rcast->deltadist.y);
}

void	ft_calc_wall_dist(t_data *data)
{
	float	wall_x;

	ft_get_perp_wall_dist(data);
	data->rcast->line_height = (int)(SCREENHEIGHT \
		/ data->rcast->perp_wall_dist);
	data->rcast->draw_start = -data->rcast->line_height / 2 + SCREENHEIGHT / 2;
	if (data->rcast->draw_start < 0)
		data->rcast->draw_start = 0;
	data->rcast->draw_end = data->rcast->line_height / 2 + SCREENHEIGHT / 2;
	if (data->rcast->draw_end >= SCREENHEIGHT)
		data->rcast->draw_end = SCREENHEIGHT - 1;
	if (data->rcast->side == 0)
		wall_x = data->player->pos.y + data->rcast->perp_wall_dist \
			* data->rcast->raydir.y;
	else
		wall_x = data->player->pos.x + data->rcast->perp_wall_dist \
			* data->rcast->raydir.x;
	wall_x -= floor((wall_x));
	data->rcast->tex_x = (int)(wall_x * WALL_RES);
	if (data->rcast->side == 0 && data->rcast->raydir.x > 0)
		data->rcast->tex_x = WALL_RES - data->rcast->tex_x - 1;
	if (data->rcast->side == 1 && data->rcast->raydir.y < 0)
		data->rcast->tex_x = WALL_RES - data->rcast->tex_x - 1;
}

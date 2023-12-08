/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:45:26 by gbricot           #+#    #+#             */
/*   Updated: 2023/12/08 14:02:23 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	ft_deg_to_rad(float a)
{
	return (a * M_PI / 180.0);
}

void	ft_init_raycast(t_data *data)
{
	data->rcast->pos.x = data->player->pos.x;
	data->rcast->pos.y = data->player->pos.y;
	data->rcast->dir.y = cosf(ft_deg_to_rad(data->player->angle));
	data->rcast->dir.x = sinf(ft_deg_to_rad(data->player->angle));
	data->rcast->plane.x = cosf(FOV / 2.0) * -data->rcast->dir.y;
	data->rcast->plane.y = sinf(FOV / 2.0) * data->rcast->dir.x;
	data->rcast->x = 0;
}

void	ft_calc_vectors(t_data *data)
{
	data->rcast->camera_x = 2.0 * data->rcast->x / SCREENWIDTH - 1.0;
	data->rcast->raydir.x = data->rcast->dir.x \
		+ data->rcast->plane.x * data->rcast->camera_x;
	data->rcast->raydir.y = data->rcast->dir.y \
		+ data->rcast->plane.y * data->rcast->camera_x;
	data->rcast->map.x = data->rcast->pos.x;
	data->rcast->map.y = data->rcast->pos.y;
	if (data->rcast->raydir.x == 0)
		data->rcast->deltadist.x = 1e30;
	else
		data->rcast->deltadist.x = fabs((1.0 / data->rcast->raydir.x));
	if (data->rcast->raydir.y == 0)
		data->rcast->deltadist.y = 1e30;
	else
		data->rcast->deltadist.y = fabs((1.0 / data->rcast->raydir.y));
}

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
		if (data->rcast->map.x >= 0 && data->rcast->map.x <= data->map_max_x \
			&& data->rcast->map.y >= 0 && data->rcast->map.y < data->map_max_y)
		{
			if (data->map[data->rcast->map.y][data->rcast->map.x] == '1')
				hit = 1;
		}
		else
			break ;
	}
}

void	ft_calc_wall_dist(t_data *data)
{
	if (data->rcast->side == 0)
		data->rcast->perp_wall_dist = (data->rcast->sidedist.x \
			- data->rcast->deltadist.x);
	else
		data->rcast->perp_wall_dist = (data->rcast->sidedist.y \
			- data->rcast->deltadist.y);
	data->rcast->line_height = (int)(SCREENHEIGHT / data->rcast->perp_wall_dist);
	data->rcast->draw_start = -data->rcast->line_height / 2 + SCREENHEIGHT / 2;
	if (data->rcast->draw_start < 0)
		data->rcast->draw_start = 0;
	data->rcast->draw_end = data->rcast->line_height / 2 + SCREENHEIGHT / 2;
	if (data->rcast->draw_end >= SCREENHEIGHT)
		data->rcast->draw_end = SCREENHEIGHT - 1;

	float wall_x;
	if (data->rcast->side == 0)
		wall_x = data->player->pos.y + data->rcast->perp_wall_dist * data->rcast->raydir.y;
	else
		wall_x = data->player->pos.x + data->rcast->perp_wall_dist * data->rcast->raydir.x;
	wall_x -= floor((wall_x));
	data->rcast->tex_x = (int)(wall_x * WALL_RES);
	if (data->rcast->side == 0 && data->rcast->raydir.x > 0)
		data->rcast->tex_x = WALL_RES - data->rcast->tex_x - 1;
	if (data->rcast->side == 1 && data->rcast->raydir.y < 0)
		data->rcast->tex_x = WALL_RES - data->rcast->tex_x - 1;
}

// void	ft_render_line(t_data *data)
// {
	
// }

void	ft_raycast(t_data *data)
{
	ft_init_raycast(data);
	while (data->rcast->x < SCREENWIDTH)
	{
		ft_calc_vectors(data);
		ft_get_side_dist(data);
		ft_search_wall(data);
		ft_calc_wall_dist(data);
		float	step = 1.0 * (float) WALL_RES / data->rcast->line_height;
		data->rcast->tex_pos = (data->rcast->draw_start - SCREENHEIGHT / 2 + data->rcast->line_height / 2) * step;
		int	y = data->rcast->draw_start;
		while (y < data->rcast->draw_end)
		{
			int	tex_y = (int) data->rcast->tex_pos & (WALL_RES - 1);
			data->rcast->tex_pos += step;
			int	index = floorf((tex_y * data->textures->no.line_len) + (data->rcast->tex_x * (data->textures->no.bpp / 8)));
			if (data->rcast->side)
			{
				if (data->rcast->raydir.y > 0.0)
				{
					data->rcast->red = data->textures->so.addr[index + 2];
					data->rcast->green = data->textures->so.addr[index + 1];
					data->rcast->blue = data->textures->so.addr[index];
				}
				else
				{
					data->rcast->red = data->textures->no.addr[index + 2];
					data->rcast->green = data->textures->no.addr[index + 1];
					data->rcast->blue = data->textures->no.addr[index];
				}
			}
			else
			{
				if (data->rcast->raydir.x > 0.0)
				{
					data->rcast->red = data->textures->ea.addr[index + 2];
					data->rcast->green = data->textures->ea.addr[index + 1];
					data->rcast->blue = data->textures->ea.addr[index];
				}
				else
				{
					data->rcast->red = data->textures->we.addr[index + 2];
					data->rcast->green = data->textures->we.addr[index + 1];
					data->rcast->blue = data->textures->we.addr[index];
				}
			}
			img_pix_put(&data->img, data->rcast->x, y, ((data->rcast->red << 16) + (data->rcast->green << 8) + data->rcast->blue));
			y++;
		}
		data->rcast->x++;
	}
}

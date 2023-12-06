/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:45:26 by gbricot           #+#    #+#             */
/*   Updated: 2023/12/06 17:41:44 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float ft_deg_to_rad(float a)
{
	return (a * M_PI / 180.0);
}

void	ft_raycast(t_data *data)
{
	data->rcast->pos.x = data->player->pos.x;
	data->rcast->pos.y = data->player->pos.y;
	data->rcast->dir.y = cosf(ft_deg_to_rad(data->player->angle));
	data->rcast->dir.x = sinf(ft_deg_to_rad(data->player->angle));
	data->rcast->plane.x = cosf(FOV / 2.0) * -data->rcast->dir.y;
	data->rcast->plane.y = sinf(FOV / 2.0) * data->rcast->dir.x;

	int x = 0;
	while (x < SCREENWIDTH)
	{
		data->rcast->camera_x = 2.0 * x / SCREENWIDTH - 1.0;
		data->rcast->raydir.x = data->rcast->dir.x + data->rcast->plane.x * data->rcast->camera_x;
		data->rcast->raydir.y = data->rcast->dir.y + data->rcast->plane.y * data->rcast->camera_x;

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

		if (data->rcast->raydir.x < 0)
		{
			data->rcast->step.x = -1;
			data->rcast->sidedist.x = (data->rcast->pos.x - data->rcast->map.x) * data->rcast->deltadist.x;
		}
		else
		{
			data->rcast->step.x = 1;
			data->rcast->sidedist.x = (data->rcast->map.x + 1.0 - data->rcast->pos.x) * data->rcast->deltadist.x;
		}
		if (data->rcast->raydir.y < 0)
		{
			data->rcast->step.y = -1;
			data->rcast->sidedist.y = (data->rcast->pos.y - data->rcast->map.y) * data->rcast->deltadist.y;
		}
		else
		{
			data->rcast->step.y = 1;
			data->rcast->sidedist.y = (data->rcast->map.y + 1.0 - data->rcast->pos.y) * data->rcast->deltadist.y;
		}

		int		hit = 0;
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
		if (data->rcast->side == 0)
			data->rcast->perp_wall_dist = (data->rcast->sidedist.x - data->rcast->deltadist.x);
		else
			data->rcast->perp_wall_dist = (data->rcast->sidedist.y - data->rcast->deltadist.y);

		int line_height = (int) (SCREENHEIGHT / data->rcast->perp_wall_dist);
		int draw_start = -line_height / 2 + SCREENHEIGHT / 2;
		if(draw_start < 0)
			draw_start = 0;
		int draw_end = line_height / 2 + SCREENHEIGHT / 2;
		if(draw_end >= SCREENHEIGHT)
			draw_end = SCREENHEIGHT - 1;

		float wall_x;
		if (data->rcast->side == 0)
			wall_x = data->player->pos.y + data->rcast->perp_wall_dist * data->rcast->raydir.y;
		else
			wall_x = data->player->pos.x + data->rcast->perp_wall_dist * data->rcast->raydir.x;
		wall_x -= floor((wall_x));
		int tex_x = (int) (wall_x * WALL_RES);
		if(data->rcast->side == 0 && data->rcast->raydir.x > 0)
			tex_x = WALL_RES - tex_x - 1;
		if(data->rcast->side == 1 && data->rcast->raydir.y < 0)
			tex_x = WALL_RES - tex_x - 1;


		float	step = 1.0 * (float) WALL_RES / line_height;
		float	tex_pos = (draw_start - SCREENHEIGHT / 2 + line_height / 2) * step;
		int	y = draw_start;
		while (y < draw_end)
		{
			int	tex_y = (int) tex_pos & (WALL_RES - 1);
			tex_pos += step;
			int	index = (int) ((tex_y * data->textures->no.line_len) + (tex_x * (data->textures->no.bpp / 8)));
			unsigned int red = data->textures->no.addr[index];
			unsigned int green = data->textures->no.addr[index + 1];
			unsigned int blue = data->textures->no.addr[index + 2];
			img_pix_put(&data->img, x, y, ((red << 16) + (green << 8) + blue));
			y++;
		}
/*		while (draw_start < draw_end)
			img_pix_put(&data->img, x, draw_start++, 0xFFFFFF);
*/		x++;
	}
}

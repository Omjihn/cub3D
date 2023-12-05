/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:45:26 by gbricot           #+#    #+#             */
/*   Updated: 2023/12/05 18:05:58 by gbricot          ###   ########.fr       */
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

		int lineHeight = (int)(SCREENHEIGHT / data->rcast->perp_wall_dist);
		int drawStart = -lineHeight / 2 + SCREENHEIGHT / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + SCREENHEIGHT / 2;
		if(drawEnd >= SCREENHEIGHT)
			drawEnd = SCREENHEIGHT - 1;
		while (drawStart < drawEnd)
			img_pix_put(&data->img, x, drawStart++, 0xFFFFFF);
		x++;
	}
}

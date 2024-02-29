/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 16:45:26 by gbricot           #+#    #+#             */
/*   Updated: 2023/12/12 10:47:22 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	ft_deg_to_rad(float a)
{
	return (a * M_PI / 180.0);
}

static void	ft_init_raycast(t_data *data)
{
	data->rcast->pos.x = data->player->pos.x;
	data->rcast->pos.y = data->player->pos.y;
	data->rcast->dir.y = cosf(ft_deg_to_rad(data->player->angle));
	data->rcast->dir.x = sinf(ft_deg_to_rad(data->player->angle));
	data->rcast->plane.x = cosf(ft_deg_to_rad(FOV) / 2.0) * -data->rcast->dir.y;
	data->rcast->plane.y = sinf(ft_deg_to_rad(FOV) / 2.0) * data->rcast->dir.x;
	data->rcast->x = 0;
}

static void	ft_calc_vectors(t_data *data)
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

void	ft_raycast(t_data *data)
{
	ft_init_raycast(data);
	while (data->rcast->x < SCREENWIDTH)
	{
		ft_calc_vectors(data);
		ft_get_side_dist(data);
		ft_search_wall(data);
		ft_calc_wall_dist(data);
		data->rcast->step_tex = 1.0 * (float) WALL_RES \
			/ data->rcast->line_height;
		data->rcast->tex_pos = (data->rcast->draw_start - SCREENHEIGHT / 2 \
			+ data->rcast->line_height / 2) * data->rcast->step_tex;
		data->rcast->y = data->rcast->draw_start;
		while (data->rcast->y < data->rcast->draw_end)
			ft_draw_pix(data);
		data->rcast->x++;
	}
	if (data->rcast->frame >= 1 && data->rcast->frame <= 3)
		data->rcast->frame++;
	else
		data->rcast->frame = 1;
}

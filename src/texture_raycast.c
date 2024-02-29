/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_raycast.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:58:02 by gbricot           #+#    #+#             */
/*   Updated: 2023/12/11 17:01:04 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_get_pix_wall_s_n(t_data *data)
{
	if (data->rcast->raydir.y > 0.0)
	{
		data->rcast->red = data->textures->so.addr[data->rcast->index + 2];
		data->rcast->green = data->textures->so.addr[data->rcast->index + 1];
		data->rcast->blue = data->textures->so.addr[data->rcast->index];
	}
	else
	{
		data->rcast->red = data->textures->no.addr[data->rcast->index + 2];
		data->rcast->green = data->textures->no.addr[data->rcast->index + 1];
		data->rcast->blue = data->textures->no.addr[data->rcast->index];
	}
}

static void	ft_get_pix_wall_e_w(t_data *data)
{
	if (data->rcast->raydir.x > 0.0)
	{
		data->rcast->red = data->textures->ea.addr[data->rcast->index + 2];
		data->rcast->green = data->textures->ea.addr[data->rcast->index + 1];
		data->rcast->blue = data->textures->ea.addr[data->rcast->index];
	}
	else
	{
		data->rcast->red = data->textures->we.addr[data->rcast->index + 2];
		data->rcast->green = data->textures->we.addr[data->rcast->index + 1];
		data->rcast->blue = data->textures->we.addr[data->rcast->index];
	}
}

static void	ft_get_pix_layer(t_data *data, t_image *anim)
{
	data->rcast->red = anim->addr[data->rcast->index + 2];
	data->rcast->green = anim->addr[data->rcast->index + 1];
	data->rcast->blue = anim->addr[data->rcast->index];
	if (!data->rcast->red && !data->rcast->blue && data->rcast->green == 255)
	{
		if (data->rcast->side)
			ft_get_pix_wall_s_n(data);
		else
			ft_get_pix_wall_e_w(data);
	}
}

static void	ft_get_pix_frame(t_data *data)
{
	if (data->rcast->frame == 1)
		ft_get_pix_layer(data, &data->textures->anim_1);
	else if (data->rcast->frame == 2)
		ft_get_pix_layer(data, &data->textures->anim_2);
	else if (data->rcast->frame == 3)
		ft_get_pix_layer(data, &data->textures->anim_3);
	else
		ft_get_pix_layer(data, &data->textures->anim_4);
}

void	ft_draw_pix(t_data *data)
{
	int	tex_y;

	tex_y = (int) data->rcast->tex_pos & (WALL_RES - 1);
	data->rcast->tex_pos += data->rcast->step_tex;
	data->rcast->index = floorf((tex_y * data->textures->no.line_len) \
		+ (data->rcast->tex_x * (data->textures->no.bpp / 8)));
	if (*data->rcast->wall_type == 'D')
		ft_get_pix_layer(data, &data->textures->door);
	else if (*data->rcast->wall_type == '2')
		ft_get_pix_frame(data);
	else
	{
		if (data->rcast->side)
			ft_get_pix_wall_s_n(data);
		else
			ft_get_pix_wall_e_w(data);
	}
	img_pix_put(&data->img, data->rcast->x, data->rcast->y, \
		((data->rcast->red << 16) + (data->rcast->green << 8) \
		+ data->rcast->blue));
	data->rcast->y++;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:00:07 by gbricot           #+#    #+#             */
/*   Updated: 2023/12/03 19:09:52 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

// void	ft_render_game(t_data *data)
// {
// 	ft_raycast(data, 0);
// }

// char	ft_is_player_facing_up(float player_angle)
// {
// 	if ((player_angle >= 0 && player_angle <= 180))
// 		return (1);
// 	return (0);
// }

void	ft_create_image(t_data *data)
{
	if (data->img.addr)
		mlx_destroy_image(data->mlx, data->img.mlx_img);
	data->img.mlx_img = mlx_new_image(data->mlx, SCREENWIDTH, SCREENHEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, \
			&data->img.bpp,	&data->img.line_len, \
			&data->img.endian);
}

void	img_pix_put(t_image *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}
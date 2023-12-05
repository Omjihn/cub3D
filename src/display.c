/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 09:35:00 by gbricot           #+#    #+#             */
/*   Updated: 2023/12/05 17:55:11 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

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

void	ft_draw_bg(t_data *data)
{
	int		x;
	int		y;

	y = 0;
	while (y <= SCREENHEIGHT / 2)
	{
		x = 0;
		while (x <= SCREENWIDTH)
			img_pix_put(&data->img, x++, y, data->textures->floor);
		y++;
	}
	while (y <= SCREENHEIGHT)
	{
		x = 0;
		while (x <= SCREENWIDTH)
			img_pix_put(&data->img, x++, y, data->textures->ceiling);
		y++;
	}
}
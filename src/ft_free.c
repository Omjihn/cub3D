/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 12:18:22 by gbricot           #+#    #+#             */
/*   Updated: 2023/12/05 17:16:12 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_free_textures(t_data	*data)
{
	if (data->textures->no)
		mlx_destroy_image(data->mlx, data->textures->no);
	if (data->textures->so)
		mlx_destroy_image(data->mlx, data->textures->so);
	if (data->textures->ea)
		mlx_destroy_image(data->mlx, data->textures->ea);
	if (data->textures->we)
		mlx_destroy_image(data->mlx, data->textures->we);
	free(data->textures);
}

void	ft_free_all(t_data *data)
{
	int		i;

	i = 0;
	//mlx_mouse_show(data->mlx, data->win);
	if (data)
	{
		if (data->win)
		{
			mlx_clear_window(data->mlx, data->win);
			mlx_destroy_window(data->mlx, data->win);
		}
		if (data->map)
		{
			while (data->map[i])
				free(data->map[i++]);
			free(data->map);
		}
		if (data->textures)
			ft_free_textures(data);
		if (data->player)
			free(data->player);
		if (data->img.mlx_img)
			mlx_destroy_image(data->mlx, data->img.mlx_img);
		if (data->rcast)
			free(data->rcast);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
		free(data);
	}
}

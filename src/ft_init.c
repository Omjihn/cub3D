/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:16:28 by ashalagi          #+#    #+#             */
/*   Updated: 2023/12/04 14:58:54 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_game_loop(t_data *data)
{
	ft_create_image(data);
	ft_draw_bg(data);
    printf("Wall distance in front of the player : %f\n", vector_distance(data));
	//ft_draw_rays_2d(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.mlx_img, 0, 0);
	return (0);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:16:28 by ashalagi          #+#    #+#             */
/*   Updated: 2023/12/08 13:48:55 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_game_loop(t_data *data)
{
	ft_create_image(data);
	ft_draw_bg(data);
	ft_raycast(data);
	ft_draw_mini_map(data);
	mlx_put_image_to_window(data->mlx, data->win, data->img.mlx_img, 0, 0);
	// if (data->player->facing_door)
	// {
	// 	// Render the door as open or perform any specific action
	// }
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 08:54:19 by ashalagi          #+#    #+#             */
/*   Updated: 2023/12/11 17:06:43 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// nitialize facing_door to 0 in ft_put_player function

void	ft_interact_door(t_data *data)
{
	int	map_x;
	int	map_y;

	map_x = (int)(data->player->pos.x \
		+ cosf(ft_deg_to_rad(data->player->angle - 90.0f)) * 1.0f);
	map_y = (int)(data->player->pos.y \
		+ -sinf(ft_deg_to_rad(data->player->angle - 90.0f)) * 1.0f);
	if (data->map[map_y][map_x] == 'D')
		data->map[map_y][map_x] = 'O';
	else if (data->map[map_y][map_x] == 'O' \
		&& (map_x != (int) floorf(data->player->pos.x) \
		|| map_y != (int) floorf(data->player->pos.y)))
		data->map[map_y][map_x] = 'D';
}

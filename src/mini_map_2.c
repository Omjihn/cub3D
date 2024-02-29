/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 11:21:38 by ashalagi          #+#    #+#             */
/*   Updated: 2023/12/12 11:27:49 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_put_color(char map_value)
{
	if (map_value == '1' || map_value == '2')
		return (0xFFFFFF);
	else if (map_value == 'D' || map_value == 'O')
		return (0x00FFFF);
	else if (map_value == '0' || map_value == 'N' || map_value == 'S' \
			|| map_value == 'E' || map_value == 'W')
		return (0x000000);
	return (-1);
}

int	ft_should_draw(int mini_map_x, int mini_map_y)
{
	return (!(mini_map_x + MINI_MAP_SCALE > SCREENWIDTH \
			|| mini_map_y + MINI_MAP_SCALE > SCREENHEIGHT));
}

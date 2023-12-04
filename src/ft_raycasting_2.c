/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:32:31 by ashalagi          #+#    #+#             */
/*   Updated: 2023/12/04 10:55:29 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_draw_wall(t_data *data, float x, float distance, int color)
{
	float	line_height;
	float	y;
	float	draw_start;
	float	draw_end;

	if (distance <= 0)
		return;
	// Calculate the projected wall height
	line_height = (data->rcast.mapS * SCREENHEIGHT / distance);

	// Calculate the vertical start and end points
	draw_start = -line_height / 2 + SCREENHEIGHT / 2;
	if (draw_start < 0)
		draw_start = 0;
	draw_end = line_height / 2 + SCREENHEIGHT / 2;
	if (draw_end >= SCREENHEIGHT)
		draw_end = SCREENHEIGHT - 1;
	// Draw the vertical slice
	y = draw_start;
	while (y < draw_end)
	{
		img_pix_put(&data->img, x, y, color);
		y++;
	}
}
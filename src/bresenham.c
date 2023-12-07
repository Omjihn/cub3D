/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bresenham.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:53:55 by gbricot           #+#    #+#             */
/*   Updated: 2023/12/07 09:45:31 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_octant_0(float x1, float y1, float x2, float y2, t_data *data)
{
	float	error;
	float	slope;

	error = 0.0;
	slope = (float)(y2 - y1) / (float)(x2 - x1);
	while (x1 <= x2)
	{
		img_pix_put(&data->img, x1, y1, 0xFFFFFF);
		error += slope;
		if (error >= 0.5)
		{
			y1++;
			error -= 1.0;
		}
		x1++;
	}
}

void	ft_draw_octant_1(float x1, float y1, float x2, float y2, t_data *data)
{
	float	error;
	float	slope;

	error = 0.0;
	slope = (float)(x2 - x1) / (float)(y2 - y1);
	while (y1 <= y2)
	{
		img_pix_put(&data->img, x1, y1, 0xFFFFFF);
		error += slope;
		if (error >= 0.5)
		{
			x1++;
			error -= 1.0;
		}
		y1++;
	}
}

void	ft_draw_octant_6(float x1, float y1, float x2, float y2, t_data *data)
{
	float	error;
	float	slope;

	error = 0.0;
	slope = (float)(x2 - x1) / (float)(y1 - y2);
	while (y1 >= y2)
	{
		img_pix_put(&data->img, x1, y1, 0xFFFFFF);
		error += slope;
		if (error >= 0.5)
		{
			x1++;
			error -= 1.0;
		}
		y1--;
	}
}

void	ft_draw_octant_7(float x1, float y1, float x2, float y2, t_data *data)
{
	float	error;
	float	slope;

	error = 0.0;
	slope = (float)(y1 - y2) / (float)(x2 - x1);
	while (x1 <= x2)
	{
		img_pix_put(&data->img, x1, y1, 0xFFFFFF);
		error += slope;
		if (error >= 0.5)
		{
			y1--;
			error -= 1.0;
		}
		x1++;
	}
}

/*			BRESENHAM			*/
void	ft_draw_vector(float x1, float y1, float x2, float y2, t_data *data)
{
	float	temp;

	if (x1 > x2)
	{
		temp = x2;
		x2 = x1;
		x1 = temp;
		temp = y2;
		y2 = y1;
		y1 = temp;
	}
	if (x1 < x2 && y1 <= y2 && (x1 - x2) <= (y1 - y2))
		ft_draw_octant_0(x1, y1, x2, y2, data);
	else if (x1 <= x2 && y1 <= y2 && (x1 - x2) > (y1 - y2))
		ft_draw_octant_1(x1, y1, x2, y2, data);
	else if (x1 < x2 && y1 >= y2 && (x1 - x2) > (y2 - y1))
		ft_draw_octant_6(x1, y1, x2, y2, data);
	else if (x1 < x2 && y1 >= y2 && (x1 - x2) < (y2 - y1))
		ft_draw_octant_7(x1, y1, x2, y2, data);
}

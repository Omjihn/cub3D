/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_raycasting_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 10:13:51 by ashalagi          #+#    #+#             */
/*   Updated: 2023/12/04 18:35:38 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float ft_deg_to_rad(float a)
{
	return (a * M_PI / 180.0);
}

float	vector_distance(t_data *data)
{
	t_coords_f	pos;
	t_coords_f	dir;
	t_coords_f	plane;

	pos.x = data->player->pos->x;
	pos.y = data->player->pos->y;
	dir.x = cos(ft_deg_to_rad(data->player->angle));
	dir.y = sin(ft_deg_to_rad(data->player->angle));
	plane.x = 1.0;
	plane.y = tan(ft_deg_to_rad(FOV) / 2.0);

	int x = 0;
	while (x < SCREENWIDTH)
	{
		double	camerax = 2.0 * x / SCREENWIDTH - 1.0;
		t_coords_d	raydir;
		raydir.x = dir.x + plane.x * camerax;
		raydir.y = dir.y + plane.y * camerax;

		t_coords	map;
		map.x = pos.x;
		map.y = pos.y;

		t_coords_d	sidedist;
		t_coords_d	deltadist;
		if (raydir.x == 0)
			deltadist.x = 1e30;
		else
			deltadist.x = fabs(1 / raydir.x);
		if (raydir.y == 0)
			deltadist.y = 1e30;
		else
			deltadist.y = fabs(1 / raydir.y);
		double	perpWallDist;

		t_coords	step;
		int		hit = 0;
		int		side;

		if (raydir.x < 0)
		{
			step.x = -1;
			sidedist.x = (pos.x - map.x) * deltadist.x;
		}
		else
		{
			step.x = 1;
			sidedist.x = (map.x + 1.0 - pos.x) * deltadist.x;
		}
		if (raydir.y < 0)
		{
			step.y = -1;
			sidedist.y = (pos.y - map.y) * deltadist.y;
		}
		else
		{
			step.y = 1;
			sidedist.y = (map.y + 1.0 - pos.y) * deltadist.y;
		}

		while (hit == 0)
		{
			if (sidedist.x < sidedist.y)
			{
				sidedist.x += deltadist.x;
				map.x += step.x;
				side = 0;
			}
			else
			{
				sidedist.y += deltadist.y;
				map.y += step.y;
				side = 1;
			}
			if (map.x >= 0 && map.x <= data->map_max_x && map.y >= 0 && map.y <= data->map_max_y)
			{
				if (data->map[map.x][map.y] == '1')
					hit = 1;
			}
			else
			{
				break ;
			}
		}
		if (side == 0)
			perpWallDist = (sidedist.x - deltadist.x);
		else
			perpWallDist = (sidedist.y - deltadist.y);
		int lineHeight = (int)(SCREENHEIGHT / perpWallDist);
		int drawStart = -lineHeight / 2 + SCREENHEIGHT / 2;
		if(drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + SCREENHEIGHT / 2;
		if(drawEnd >= SCREENHEIGHT)
			drawEnd = SCREENHEIGHT - 1;
		while (drawStart < drawEnd)
			img_pix_put(&data->img, x, drawStart++, 0xFFFFFF);
		//printf("Wall distance :%f\n", perpWallDist);
		x++;
	}
	return (0);
}

// float ft_fix_ang(float a)
// {
// 	if (a > 359)
// 		a -= 360;
// 	if (a < 0)
// 		a += 360;
// 	return a;
// }

// void ft_cast_vertical_ray(t_data *data, float *disV)
// {
// 	float	Tan;
// 	int		dof;

// 	dof = 0;
// 	*disV = 100000;
// 	Tan = tan(ft_deg_to_rad(data->rcast.ra));

// 	if (cos(ft_deg_to_rad(data->rcast.ra)) > 0.001)
// 	{
// 		data->rcast.rx = (((int)data->rcast.px >> 6) << 6) + SQUARE_RES;
// 		data->rcast.ry = (data->rcast.px - data->rcast.rx) * Tan + data->rcast.py;
// 		data->rcast.xo = 64;
// 		data->rcast.yo = data->rcast.xo * Tan;
// 	}
// 	else if (cos(ft_deg_to_rad(data->rcast.ra)) < -0.001)
// 	{
// 		data->rcast.rx = (((int)data->rcast.px >> 6) << 6) - 0.0001;
// 		data->rcast.ry = (data->rcast.px - data->rcast.rx) * Tan + data->rcast.py;
// 		data->rcast.xo = -SQUARE_RES;
// 		data->rcast.yo = - data->rcast.xo * Tan;
// 	}
// 	else
// 	{
// 		data->rcast.rx = data->rcast.px;
// 		data->rcast.ry = data->rcast.py;
// 		dof = 8; // looking up or down, no hit
// 	}
// 	while (dof < 8)
// 	{
// 		data->rcast.mx = (int)(data->rcast.rx) >> 6;
// 		data->rcast.my = (int)(data->rcast.ry) >> 6;
// 		data->rcast.mp = data->rcast.my * data->map_max_x + data->rcast.mx;
// 		if (data->rcast.mp > 0 && data->rcast.mp < data->map_max_x * data->map_max_y && data->map[data->rcast.mp] == '1')
// 		{
// 			dof = 8;
// 			*disV = cos(ft_deg_to_rad(data->rcast.ra)) * (data->rcast.rx - data->rcast.px) - sin(ft_deg_to_rad(data->rcast.ra)) * (data->rcast.ry - data->rcast.py); // hit
// 		}
// 		else
// 		{
// 			data->rcast.rx += data->rcast.xo;
// 			data->rcast.ry += data->rcast.yo;
// 			dof += 1; // check next horizontal
// 		}
// 	}
// }

// void ft_cast_horizontal_ray(t_data *data, float *disH)
// {
// 	float	Tan;
// 	int		dof;

// 	dof = 0;
// 	*disH = 100000;
// 	Tan = 1.0 / tan(ft_deg_to_rad(data->rcast.ra));

// 	if (sin(ft_deg_to_rad(data->rcast.ra)) > 0.001)
// 	{
// 		data->rcast.ry = (((int)data->rcast.py >> 6) << 6) - 0.0001;
// 		data->rcast.rx = (data->rcast.py - data->rcast.ry) * Tan + data->rcast.px;
// 		data->rcast.yo = -SQUARE_RES;
// 		data->rcast.xo = - data->rcast.yo * Tan;
// 	}
// 	else if (sin(ft_deg_to_rad(data->rcast.ra)) < -0.001)
// 	{
// 		data->rcast.ry = (((int)data->rcast.py >> 6) << 6) + SQUARE_RES;
// 		data->rcast.rx = (data->rcast.py - data->rcast.ry) * Tan + data->rcast.px;
// 		data->rcast.yo = SQUARE_RES;
// 		data->rcast.xo = - data->rcast.yo * Tan;
// 	}
// 	else
// 	{
// 		data->rcast.rx = data->rcast.px;
// 		data->rcast.ry = data->rcast.py;
// 		dof = 8; // looking straight left or right, no hit
// 	}

// 	while (dof < 8)
// 	{
// 		data->rcast.mx = (int)(data->rcast.rx) >> 6;
// 		data->rcast.my = (int)(data->rcast.ry) >> 6;
// 		data->rcast.mp = data->rcast.my * data->map_max_x + data->rcast.mx;
// 		if (data->rcast.mp > 0 && data->rcast.mp < data->map_max_x * data->map_max_y && data->map[data->rcast.mp] == '1')
// 		{
// 			dof = 8;
// 			*disH = cos(ft_deg_to_rad(data->rcast.ra)) * (data->rcast.rx - data->rcast.px) - sin(ft_deg_to_rad(data->rcast.ra)) * (data->rcast.ry - data->rcast.py); // hit
// 		}
// 		else
// 		{
// 			data->rcast.rx += data->rcast.xo;
// 			data->rcast.ry += data->rcast.yo;
// 			dof += 1; // check next horizontal
// 		}
// 	}
// }

// void ft_draw_rays_2d(t_data *data)
// {
// //	int r;
// 	float disV, disH;
// //	float vx;
// //	float vy;
// 	float used_distance, ca, r;

// 	float angle_max = 90;

// 	data->rcast.ra = ft_fix_ang(data->rcast.pa + 30); // ray set back 30 degrees
// 	r = 0;
// 	while (r < angle_max)
// 	{
// 		ft_cast_vertical_ray(data, &disV);
// //		vx = rcast->rx;
// //		vy = rcast->ry;
// 		ft_cast_horizontal_ray(data, &disH);

// 		int color = 0x00FF00; // Some color for the ray

// 		if (disV < disH) //vertical distance is smaller
// 		{
// //			rcast->rx = vx;
// //			rcast->ry = vy;
// 			used_distance = disV;
// 			disH = disV;
// 			color = 0x006600; // Different color for vertical hit
// 		}
// 		else // Horizontal distance is smaller or equal
// 		{
// 			used_distance = disH;
// 			color = 0x00FF00; // Different color for horizontal hit
// 		}

// 		ca = ft_fix_ang(data->rcast.pa - data->rcast.ra);
// 		used_distance = used_distance * cos(ft_deg_to_rad(ca)); // Correct distance

// 		ft_draw_wall(data, r * SCREENWIDTH  / angle_max , used_distance, color);

// 		data->rcast.ra = ft_fix_ang(data->rcast.ra - 1); // Go to next ray
// 		r++;
// 	}
// }
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:30:06 by gbricot           #+#    #+#             */
/*   Updated: 2023/12/07 14:15:36 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_close_button(t_data *data)
{
	ft_free_all(data);
	exit(0);
}

/*
static void	ft_deplace_player(t_data *data, float forward, float right)
{
	data->player->pos.x += forward * cosf(ft_deg_to_rad(data->player->angle))
					+ right * cosf(ft_deg_to_rad(data->player->angle + 90.0));
	data->player->pos.y += forward * sinf(-ft_deg_to_rad(data->player->angle))
					+ right * sinf(-ft_deg_to_rad(data->player->angle + 90.0));
}
*/

/*
check if the player's new position after moving would intersect a wall.
If yes prevent the movement or adjust the position to avoid passing
through the wall
*/
static void	ft_deplace_player(t_data *data, float forward, float right)
{
	float	new_pos_x;
	float	new_pos_y;
	int		map_x;
	int		map_y;

	new_pos_x = data->player->pos.x + forward * cosf(ft_deg_to_rad(data->player->angle))
							+ right * cosf(ft_deg_to_rad(data->player->angle + 90.0));
	new_pos_y = data->player->pos.y + forward * sinf(-ft_deg_to_rad(data->player->angle))
							+ right * sinf(-ft_deg_to_rad(data->player->angle + 90.0));
	// Collision detection
	map_x = (int)new_pos_x;
	map_y = (int)new_pos_y;
	// Check if the new position is within a wall
	if (data->map[map_y][map_x] != '1')
	{
		// Update player's position if not colliding with a wall
		data->player->pos.x = new_pos_x;
		data->player->pos.y = new_pos_y;
	}
	// logic to handle sliding along walls or corner collisions
}

static void	ft_rotate_player(t_data *data, float val)
{
	if (data->player->angle + val > 360)
		data->player->angle -= 360;
	else if (data->player->angle + val < 0)
		data->player->angle += 360;
	data->player->angle += val;
}

int	ft_mouse_hook(int x, int y, t_data *data)
{
	(void) y;
	if (x == SCREENWIDTH / 2)
		return (0);
	x -= SCREENWIDTH / 2;
	ft_rotate_player(data, (float)(x * -ROT_SPEED));
	mlx_mouse_move(data->mlx, data->win, SCREENWIDTH / 2, SCREENHEIGHT / 2);
	//printf("%f\n", data->player->angle);
	/*mlx_mouse_hide(data->mlx, data->win); // leaks...*/
	return (0);
}

int	ft_player_move(int keycode, t_data *data)
{
	if (keycode == W)
		ft_deplace_player(data, 0, -MOVE_SPEED);
	else if (keycode == S)
		ft_deplace_player(data, 0, MOVE_SPEED);
	else if (keycode == A)
		ft_deplace_player(data, MOVE_SPEED, 0);
	else if (keycode == D)
		ft_deplace_player(data, -MOVE_SPEED, 0);
	// else if (keycode == SPACE)
	// 	ft_interact_door(data);
	else if (keycode == ESC)
	{
		ft_free_all(data);
		exit (0);
	}
	return (0);
}
/*
int ft_player_move(int keycode, t_data *data)
{
	// ... existing movement code ...

	if (keycode == SPACE)
	{
		if (data->player->facing_door)
		{
			// Replace 'D' with '0' in the map at the door's position
			data->map[data->player->door_y][data->player->door_x] = '0';
		}
	}

	// ... rest of the function ...
}
*/
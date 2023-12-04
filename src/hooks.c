/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:30:06 by gbricot           #+#    #+#             */
/*   Updated: 2023/12/04 20:30:23 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_close_button(t_data *data)
{
	ft_free_all(data);
	exit(0);
}

static void	ft_deplace_player(t_data *data, float y, float x)	//a changer besoin de l'angle du personnage pour le deplacer
{
	data->player->pos->y += y;
	data->player->pos->x += x;
}

static void	ft_rotate_player(t_data *data, float val)
{
	if (data->player->angle + val > 360)
		data->player->angle -= 360;
	else if (data->player->angle + val < 0)
		data->player->angle += 360;
	data->player->angle +=val;
}

int		ft_player_move( int keycode, t_data *data)
{
	ft_create_image(data);
	if (keycode == W)
		ft_deplace_player(data, MOVE_SPEED, 0);
	else if (keycode == S)
		ft_deplace_player(data, -MOVE_SPEED, 0);
	else if (keycode == A)
		ft_deplace_player(data, 0, -MOVE_SPEED);
	else if (keycode == D)
		ft_deplace_player(data, 0, MOVE_SPEED);
	else if (keycode == Q)
		ft_rotate_player(data, -ROT_SPEED);
	else if (keycode == E)
		ft_rotate_player(data, ROT_SPEED);
	else if (keycode == ESC)
	{
		ft_free_all(data);
		exit (0);
	}
	ft_game_loop(data);
	printf("[DEBUG] Player pos:x=%f, y=%f", data->player->pos->x, data->player->pos->y);
	printf(" | Player angle:%f\n", data->player->angle);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 13:00:07 by gbricot           #+#    #+#             */
/*   Updated: 2023/12/01 16:33:57 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

// void	ft_render_game(t_data *data)
// {
// 	ft_raycast(data, 0);
// }

char	ft_is_player_facing_up(float player_angle)
{
	if ((player_angle >= 0 && player_angle <= 180))
		return (1);
	return (0);
}

void	ft_raycast_horizontal(t_data *data, int angle)
{
	t_coords_f	a;
	t_coords_f	node;
	float	xa;
	float	ya;

	if (ft_is_player_facing_up(data->player->angle))
	{
		a.y = (int) (data->player->pos->y/SQUARE_RES) * (SQUARE_RES) - 1;
		printf("At the begining :y=%f\n", a.y);
		a.y /= SQUARE_RES;
		printf("At the begining : y=%f\n", a.y);
		a.x = data->player->pos->x + (data->player->pos->y - a.y) / tan(angle);
		printf("At the begining : x=%f, y=%f\n", a.x, a.y);
		a.y /= SQUARE_RES;
		printf("At the begining : x=%f, y=%f\n", a.x, a.y);
		ya = -SQUARE_RES;
	}
	else
	{
		a.y = (int) (data->player->pos->y/SQUARE_RES) * (SQUARE_RES) + SQUARE_RES;
		a.y /= SQUARE_RES;
		a.x = data->player->pos->x + (data->player->pos->y - a.y) / tan(angle);
		a.y /= SQUARE_RES;
		ya = SQUARE_RES;
	}
	xa = SQUARE_RES / tan(FOV);
	node.y = a.y + ya;
	node.x = a.x + xa;
	// node.y /= SQUARE_RES;
	// node.x /= SQUARE_RES;
	printf("before while : x=%f, y=%f\n", node.x, node.y);
	usleep(100000);
	while (data->map[(int)node.y][(int)node.x] != '1')
	{
		node.y += ya;
		node.x += xa;
	}
	node.y /= SQUARE_RES;
	node.x /= SQUARE_RES;
	printf("Wall found at : x=%f, y=%f\n", node.x, node.y);
}
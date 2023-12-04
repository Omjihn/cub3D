/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:50:34 by gbricot           #+#    #+#             */
/*   Updated: 2023/12/04 16:56:07 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_get_player_coords(t_data *data)
{
	int		i;
	int		tab;

	data->player = ft_calloc(sizeof(t_player), 1);
	tab = 0;
	while (data->map[tab])
	{
		i = 0;
		while (data->map[tab][i])
		{
			if (data->map[tab][i] == 'N' || data->map[tab][i] == 'S'
				|| data->map[tab][i] == 'E' || data->map[tab][i] == 'W')
			{
				if (!data->player->pos)
				{
					data->player->angle = 90; // Need to add the player angle with the addapted character !!!
					data->player->pos = ft_calloc(sizeof(t_coords_f), 1);
					data->player->pos->x = (float) i + 0.5;
					data->player->pos->y = (float) tab + 0.5;
				}
				else
				{
					free(data->player->pos);
					free(data->player);
					data->player = NULL;
					return ;
				}
			}
			i++;
		}
		tab++;
	}
}

void	ft_run_through(t_data *data, char **map, int y, int x)
{
	//usleep(10000);
	//printf("[DEBUG] Run Through : y=%d, x=%d | limits :x%d, y%d\n", y, x, data->map_max_y, data->map_max_x);
	if (map[y][x] == '1')
		return ;
	if (x <= 0 || y <= 0 || x >= data->map_max_x - 1 || y >= data->map_max_y - 1)
	{
		if (map[y][x] == '0' || map[y][x] == 'S' || map[y][x] == 'E'
			|| map[y][x] == 'N' || map[y][x] == 'W')
		{
			data->err = 1;
			//printf("[DEBUG] err with y=%d, x=%d\n", y, x);
			return ;
		}
		//printf("[DEBUG] On the border return\n"); //useless
		return ;
	}
	if (map[y][x] == ' ')
	{
		data->err = 1;
		//printf("[DEBUG] err with y=%d, x=%d\n", y, x);
		map[y][x] = '1';
		return ;
	}
	if (map[y][x] == '0' || map[y][x] == 'S' || map[y][x] == 'E'
		|| map[y][x] == 'N' || map[y][x] == 'W')
	{
		map[y][x] = '1';
	}
	ft_run_through(data, map, y - 1, x);
	ft_run_through(data, map, y, x - 1);
	ft_run_through(data, map, y + 1, x);
	ft_run_through(data, map, y, x + 1);
}

char	ft_pathfinding(t_data *data)
{
	char	**cpy_map;
	int		i;

	ft_get_player_coords(data);
	if (data->player)
		printf("[DEBUG] player coords : y = %f | x = %f\n", data->player->pos->y, data->player->pos->x);
	if (!data->player)
		return (0);
	i = 0;
	cpy_map = ft_calloc (sizeof(char *), ft_tablen(data->map) + 1);
	while (data->map[i])
	{
		cpy_map[i] = ft_strdup(data->map[i]);
		i++;
	}
	cpy_map[i] = NULL;
	ft_run_through(data, cpy_map, data->player->pos->y, data->player->pos->x);
	i = 0;
	while (cpy_map[i])
		free (cpy_map[i++]);
	free (cpy_map);
	if (data->err)
		return (0);
	return (1);
}

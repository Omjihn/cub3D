/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathfinding.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 10:50:34 by gbricot           #+#    #+#             */
/*   Updated: 2023/12/11 17:24:59 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_put_player(t_data *data, int tab, int i)
{
	data->player = ft_calloc(sizeof(t_player), 1);
	data->player->pos.x = (float) i + 0.5;
	data->player->pos.y = (float) tab + 0.5;
	if (data->map[tab][i] == 'N')
		data->player->angle = 180;
	if (data->map[tab][i] == 'S')
		data->player->angle = 0;
	if (data->map[tab][i] == 'E')
		data->player->angle = 90;
	if (data->map[tab][i] == 'W')
		data->player->angle = 270;
}

void	ft_get_player_coords(t_data *data)
{
	int		i;
	int		tab;

	tab = 0;
	while (data->map[tab])
	{
		i = 0;
		while (data->map[tab][i])
		{
			if (data->map[tab][i] == 'N' || data->map[tab][i] == 'S'
				|| data->map[tab][i] == 'E' || data->map[tab][i] == 'W')
			{
				if (!data->player)
					ft_put_player(data, tab, i);
				else
				{
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
	if (x < 0 || y < 0 || x > data->map_max_x || y >= data->map_max_y)
	{
		data->err = 1;
		return ;
	}
	if (map[y][x] == '1' || map[y][x] == '2')
		return ;
	if (map[y][x] == ' ')
	{
		data->err = 1;
		map[y][x] = '1';
		return ;
	}
	if (map[y][x] == '0' || map[y][x] == 'S' || map[y][x] == 'E'
		|| map[y][x] == 'N' || map[y][x] == 'W' || map[y][x] == 'D')
		map[y][x] = '1';
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
	ft_run_through(data, cpy_map, data->player->pos.y, data->player->pos.x);
	i = 0;
	while (cpy_map[i])
		free (cpy_map[i++]);
	free (cpy_map);
	if (data->err)
		return (0);
	return (1);
}

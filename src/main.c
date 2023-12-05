/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:14:02 by ashalagi          #+#    #+#             */
/*   Updated: 2023/12/05 18:11:38 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_print_map(char **map)
{
	int i = 0;
	while (map[i])
		printf("%s\n", map[i++]);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac != 2)
	{
		printf("Error: wrong number of arguments\n");
		return (0);
	}
	data = ft_parse_map(av[1]);
	if (!data)
	{
		printf("Error: invalid map.\n");
		return (0);
	}
	ft_print_map(data->map);
	printf("[DEBUG] Textures* :%p, %p, %p ,%p\nColors Hex : %u, %u\n", data->textures->no, data->textures->so, data->textures->ea, data->textures->we, data->textures->floor, data->textures->ceiling);
	data->win = mlx_new_window(data->mlx, SCREENWIDTH, SCREENHEIGHT, "cub3D");
	data->rcast = ft_calloc(sizeof(t_rcast), 1);
	mlx_hook(data->win, 17, 0L, ft_close_button, data);
	mlx_hook(data->win, 2, 1L<<0, ft_player_move, data);
	mlx_hook(data->win, 6, 1l<<6, ft_mouse_hook, data);
	mlx_loop_hook(data->mlx, ft_game_loop, data);
	mlx_loop(data->mlx);
	ft_free_all(data);
	return (0);
}

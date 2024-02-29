/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:15:29 by gbricot           #+#    #+#             */
/*   Updated: 2023/12/12 13:00:13 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	ft_is_map_char(char c)
{
	if (c == '1' || c == '0' || c == 'D' || c == 'N' || c == 'D' || c == '2'
		|| c == 'S' || c == 'E' || c == 'W' || c == ' ' || c == '\n')
		return (1);
	return (0);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	unsigned int	total_len;
	unsigned int	i;
	char			*ptr;

	total_len = ft_strlen(s1) + ft_strlen(s2);
	ptr = malloc((total_len + 1) * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	ptr[i] = '\0';
	ft_strlcat(ptr, s2, total_len + 1);
	free(s1);
	free(s2);
	return (ptr);
}

void	ft_init_textures(t_data *data)
{
	int	res;

	res = WALL_RES;
	data->textures->no.addr = mlx_get_data_addr(data->textures->no.mlx_img, \
		&data->textures->no.bpp, &data->textures->no.line_len, \
			&data->textures->no.endian);
	data->textures->so.addr = mlx_get_data_addr(data->textures->so.mlx_img, \
		&data->textures->so.bpp, &data->textures->so.line_len, \
			&data->textures->so.endian);
	data->textures->ea.addr = mlx_get_data_addr(data->textures->ea.mlx_img, \
		&data->textures->ea.bpp, &data->textures->ea.line_len, \
			&data->textures->ea.endian);
	data->textures->we.addr = mlx_get_data_addr(data->textures->we.mlx_img, \
		&data->textures->we.bpp, &data->textures->we.line_len, \
			&data->textures->we.endian);
	data->textures->door.mlx_img \
		= mlx_xpm_file_to_image(data->mlx, DOOR_PATH, &res, &res);
	data->textures->anim_1.mlx_img \
		= mlx_xpm_file_to_image(data->mlx, ANIM_1, &res, &res);
	data->textures->anim_2.mlx_img \
		= mlx_xpm_file_to_image(data->mlx, ANIM_2, &res, &res);
	data->textures->anim_3.mlx_img \
		= mlx_xpm_file_to_image(data->mlx, ANIM_3, &res, &res);
	data->textures->anim_4.mlx_img \
		= mlx_xpm_file_to_image(data->mlx, ANIM_4, &res, &res);
}

void	ft_get_addr(t_data *data, t_textures *tex)
{
	if (!tex->door.mlx_img || !tex->anim_1.mlx_img \
		|| !tex->anim_2.mlx_img || !tex->anim_3.mlx_img \
		|| !tex->anim_4.mlx_img)
	{
		ft_free_all(data);
		printf("Error : Missing textures, please recover the original repo\n");
		exit (0);
	}
	tex->door.addr = mlx_get_data_addr(tex->door.mlx_img, \
		&tex->door.bpp, &tex->door.line_len, &tex->door.endian);
	tex->anim_1.addr = mlx_get_data_addr(tex->anim_1.mlx_img, \
		&tex->anim_1.bpp, &tex->anim_1.line_len, &tex->anim_1.endian);
	tex->anim_2.addr = mlx_get_data_addr(tex->anim_2.mlx_img, \
		&tex->anim_2.bpp, &tex->anim_2.line_len, &tex->anim_2.endian);
	tex->anim_3.addr = mlx_get_data_addr(tex->anim_3.mlx_img, \
		&tex->anim_3.bpp, &tex->anim_3.line_len, &tex->anim_3.endian);
	tex->anim_4.addr = mlx_get_data_addr(tex->anim_4.mlx_img, \
		&tex->anim_4.bpp, &tex->anim_4.line_len, &tex->anim_4.endian);
}

char	ft_check_data(t_data *data)
{
	if (!data->textures->no.mlx_img || !data->textures->so.mlx_img
		|| !data->textures->ea.mlx_img || !data->textures->we.mlx_img)
		return (0);
	ft_init_textures(data);
	ft_get_addr(data, data->textures);
	if ((data->textures->floor == ERR
			|| data->textures->ceiling == ERR) \
			|| data->textures->floor < 16777216 \
			|| data->textures->ceiling < 16777216)
		return (0);
	if (!data->map)
		return (0);
	if (!ft_pathfinding(data))
		return (0);
	return (1);
}

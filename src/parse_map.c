/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:01:20 by gbricot           #+#    #+#             */
/*   Updated: 2023/11/30 14:21:08 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_file_name(char *map_name)
{
	int		i;

	i = ft_strlen(map_name);
	if (i < 4)
	{
		printf("Error: the file don't have the .cub suffix\n");
		exit(0);
	}
	if (ft_strncmp(map_name + (i - 4), ".cub", 4))
	{
		printf("Error: the file don't have the .cub suffix\n");
		exit(0);
	}
}

t_data	*ft_parse_map(char *map_name)
{
	int		fd;
	char	*line;
	t_data	*data;

	ft_check_file_name(map_name);
	fd = open(map_name, O_RDONLY);
	if (fd == -1)
	{
		printf("Error while opening the map\n");
		exit (0);
	}
	data = ft_read_infos(fd);
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (data);
}

void	*ft_get_image(char *line, t_data *data)
{
	char	**s_line;
	void	*img;
	int		i;
	int		j;
	int		wall_res;

	wall_res = WALL_RES;
	i = 0;
	s_line = ft_split(line, ' ');
	if (ft_tablen(s_line) != 2)
	{
		while (s_line[i])
			free(s_line[i++]);
		free(s_line);
		return (NULL);
	}
	j = 0;
	while (ft_isprint(s_line[1][j]))
		j++;
	s_line[1][j] = '\0';
	img = mlx_xpm_file_to_image(data->mlx, s_line[1], &wall_res, &wall_res);
	while (s_line[i])
		free(s_line[i++]);
	free(s_line);
	return (img);
}

int	ft_get_color(char *line)
{
	unsigned int	res;
	unsigned int	err;
	int				add;
	int				nb;
	int				i;

	nb = 0;
	i = 2;
	res = 0;
	err = 2147483648;
	while (line[i] && line[i] != '\n')
	{
		while (line[i] == ' ')
			i++;
		if (line[i] && ft_isdigit(line[i]))
		{
			nb++;
			add = ft_atoi(line + i);
			if (add > 255 || add < 0)
				return (err);
			res <<= 8;
			res += add;
			while (ft_isdigit(line[i]))
				i++;
		}
		while (line[i] && line[i] == ' ')
			i++;
		if (line[i] && line[i] == ',')
			i++;
	}
	if (nb == 3)
		return (res);
	return (err);
}

int		ft_strlen_map(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (!ft_is_map_char(str[i]))
			return (-1);
		i++;
	}
	return (i);
}

char	**ft_extend_map(char **map, int max_len)
{
	int		tab;
	char	*new_ptr;

	tab = 0;
	while (map[tab])
	{
		if ((int) ft_strlen(map[tab]) != max_len)
		{
			new_ptr = ft_memalloc(max_len + 1);
			ft_memset(new_ptr, ' ', max_len);
			new_ptr[max_len] = '\0';
			ft_memcpy(new_ptr, map[tab], ft_strlen(map[tab]));
			free (map[tab]);
			map[tab] = new_ptr;
		}
		tab++;
	}
	return (map);
}

char	**ft_check_map(char **base_map, t_data *data)
{
	int		i;
	int		max_len;
	int		tab;

	i = 0;
	max_len = 0;
	tab = 0;
	while (base_map[tab])
	{
		i = ft_strlen_map(base_map[tab++]);
		if (i == -1)
		{
			i = 0;
			while (base_map[i])
				free(base_map[i++]);
			free(base_map);
			return (NULL);
		}
		else if (i > max_len)
			max_len = i;
	}
	data->map_max_x = max_len;
	data->map_max_y = tab;
	return (ft_extend_map(base_map, max_len));
}

char	**ft_get_map(char *line, int fd, t_data *data)
{
	char	*map;
	char	**temp_map;

	map = ft_calloc(1, 1);
	while (line)
	{
		if (ft_strlen_map(line) == -1)
		{
			free (map);
			free (line);
			return (0);
		}
		map = ft_strjoin_free(map, line);
		line = get_next_line(fd);
	}
	temp_map = ft_split(map, '\n');
	free (map);
	/*int i = 0;
	while (temp_map[i])
	{
		printf("%s\n", temp_map[i++]); //debug
	}*/
	return (ft_check_map(temp_map, data));
}

t_data	*ft_read_infos(int fd)
{
	char	*line;
	t_data	*data;
	int		i;

	data = ft_calloc(sizeof(t_data), 1);
	data->mlx = mlx_init();
	data->textures = ft_calloc(sizeof(t_textures), 1);
	line = get_next_line(fd);
	while (line)
	{
		i = 0;
		while (line[i] && (!ft_isprint(line[i]) || line[i] == ' '))
			i++;
		if (!ft_get_info(line + i, data))
		{
			if (line[i] && ft_is_map_char(line[i]))
			{
				data->map = ft_get_map(line, fd, data);
				line = NULL;
			}
			else
			{
				free(line);
				ft_free_all(data);
				return (NULL);
			}
		}
		if (line)
			free(line);
		line = get_next_line(fd);
	}
	if (!ft_check_data(data))
	{
		ft_free_all(data);
		return (NULL);
	}
	if (line)
		free(line);
	return (data);
}

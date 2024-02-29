/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 10:01:20 by gbricot           #+#    #+#             */
/*   Updated: 2023/12/12 13:03:42 by gbricot          ###   ########.fr       */
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
		if (!ft_only_spaces(data, line, fd))
		{
			free(line);
			return (NULL);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (data);
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
		if (*line == '\n')
		{
			free(line);
			temp_map = ft_split(map, '\n');
			free (map);
			return (ft_check_map(temp_map, data));
		}
		map = ft_strjoin_free(map, line);
		line = get_next_line(fd);
	}
	temp_map = ft_split(map, '\n');
	free (map);
	return (ft_check_map(temp_map, data));
}

char	*ft_iterate_all_lines(t_data *data, char *line, int fd)
{
	int		i;

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
			printf("Error : invalid map.\n");
			exit (0);
		}
	}
	if (line)
		free(line);
	return (get_next_line(fd));
}

t_data	*ft_read_infos(int fd)
{
	char	*line;
	t_data	*data;

	data = ft_calloc(sizeof(t_data), 1);
	data->mlx = mlx_init();
	data->textures = ft_calloc(sizeof(t_textures), 1);
	line = get_next_line(fd);
	while (line)
		line = ft_iterate_all_lines(data, line, fd);
	if (!ft_check_data(data))
	{
		ft_free_all(data);
		return (NULL);
	}
	if (line)
		free(line);
	return (data);
}

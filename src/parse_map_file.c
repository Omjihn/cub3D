/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 13:02:02 by gbricot           #+#    #+#             */
/*   Updated: 2023/12/12 13:03:59 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strlen_map(char *str)
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

char	ft_only_spaces(t_data *data, char *line, int fd)
{
	int		i;
	char	*gnl;

	i = 0;
	while (line[i] && (!ft_isprint(line[i]) || line[i] == ' '))
		i++;
	if (line[i])
	{
		ft_free_all(data);
		free(line);
		gnl = get_next_line(fd);
		while (gnl)
		{
			free(gnl);
			gnl = get_next_line(fd);
		}
		return (-1);
	}
	return (0);
}

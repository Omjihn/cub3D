/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_infos.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/12 12:58:10 by gbricot           #+#    #+#             */
/*   Updated: 2023/12/12 13:03:45 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	ft_get_info(char *line, t_data *data)
{
	if (!*line)
		return (1);
	if (!ft_strncmp(line, "NO ", 3))
		ft_get_image(data, line, &data->textures->no);
	else if (!ft_strncmp(line, "SO ", 3))
		ft_get_image(data, line, &data->textures->so);
	else if (!ft_strncmp(line, "EA ", 3))
		ft_get_image(data, line, &data->textures->ea);
	else if (!ft_strncmp(line, "WE ", 3))
		ft_get_image(data, line, &data->textures->we);
	else if (!ft_strncmp(line, "F ", 2))
		data->textures->floor = ft_get_color(line, data->textures->floor);
	else if (!ft_strncmp(line, "C ", 2))
		data->textures->ceiling = ft_get_color(line, data->textures->ceiling);
	else
		return (0);
	return (1);
}

char	*ft_check_tex_name(char *line, char	*file, int j)
{
	int		i;

	if (!file)
		return (NULL);
	while (line[j] && (!ft_isprint(line[j]) || line[j] == ' '))
		j++;
	if (line[j])
	{
		free(file);
		return (NULL);
	}
	i = ft_strlen(file);
	if (i <= 4 || ft_strncmp(file + i - 4, ".xpm", 4))
	{
		free(file);
		return (NULL);
	}
	return (file);
}

void	ft_get_image(t_data *data, char *line, t_image *img)
{
	char	*file;
	int		i;
	int		j;

	if (img->mlx_img)
	{
		data->err = 1;
		return ;
	}
	i = 3;
	while (line[i] && (!ft_isprint(line[i]) || line[i] == ' '))
		i++;
	j = i;
	while (line[j] && (ft_isprint(line[j]) && line[j] != ' '))
		j++;
	file = ft_substr(line, i, j - i);
	file = ft_check_tex_name(line, file, j);
	if (file)
	{
		img->mlx_img = mlx_xpm_file_to_image(data->mlx, \
			file, &i, &i);
		free(file);
	}
	else
		data->err = 1;
}

void	ft_add_color(char *line, int *i, unsigned int *res, int *nb)
{
	int		add;

	while (line[*i] && (!ft_isprint(line[*i]) || line[*i] == ' '))
		*i += 1;
	if (line[*i] && ft_isdigit(line[*i]))
	{
		*nb += 1;
		add = ft_atoi(line + *i);
		if (add > 255 || add < 0)
			*nb += 4;
		*res <<= 8;
		*res += add;
		while (ft_isdigit(line[*i]))
			*i += 1;
	}
	while (line[*i] && (!ft_isprint(line[*i]) || line[*i] == ' '))
		*i += 1;
	if (line[*i] && line[*i] == ',')
		*i += 1;
}

int	ft_get_color(char *line, unsigned int color)
{
	unsigned int	res;
	int				nb;
	int				i;

	nb = 0;
	i = 2;
	res = 0;
	while (line[i] && line[i] != '\n' && color < 16777216)
	{
		if (!ft_isdigit(line[i]) && (ft_isprint(line[i]) && line[i] != ' '))
			return (ERR);
		ft_add_color(line, &i, &res, &nb);
	}
	if (nb == 3)
		return (res + 16777216);
	return (ERR);
}

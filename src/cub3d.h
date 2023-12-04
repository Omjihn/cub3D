/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbricot <gbricot@student.42perpignan.fr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 14:15:04 by ashalagi          #+#    #+#             */
/*   Updated: 2023/12/04 20:43:35 by gbricot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"

# include <limits.h>
# include <float.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define W			119
# define S			115
# define A			97
# define D			100

# define Q			113
# define E			101

# define ESC		65307

# define UP			65362
# define DOWN		65364
# define LEFT		65361
# define RIGHT		65363

# define WALL_RES	500

# define SCREENWIDTH	1280
# define SCREENHEIGHT	720

# define MOVE_SPEED		0.15
# define ROT_SPEED		2.0

# define SQUARE_RES		64

# define FOV		60

/*		STRUCTURES		*/

typedef struct s_texture
{
	void			*no;
	void			*so;
	void			*ea;
	void			*we;
	unsigned int	floor;
	unsigned int	ceiling;
}		t_textures;

typedef struct s_image
{
	void	*mlx_img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
}	t_image;

typedef struct s_coords
{
	int		x;
	int		y;
}			t_coords;

typedef struct s_coords_f
{
	float	x;
	float	y;
}			t_coords_f;

typedef struct s_coords_d
{
	double	x;
	double	y;
}			t_coords_d;

typedef struct s_player
{
	t_coords_f	*pos;
	float		angle;
}		t_player;

typedef struct s_rcast{
	int		mapX;
	int		mapY;
	int		mapS;
	int		*map;
	int		mx;
	int		my;
	int		mp;
	float	Tan;
	float	xo;
	float	yo;
	float	px; //player x
	float	py; //player y
	float	pdx; //player position delta
	float	pdy;
	float	pa; //player's angle, the direction the player is facing
	float	ra; //current ray angle being cast from the player's perspective
	float	rx;
	float	ry;
}			t_rcast;

typedef struct s_data
{
	void		*mlx;
	void		*win;
	char		**map;
	int			map_max_y;
	int			map_max_x;
	char		err;
	t_textures	*textures;
	t_player	*player;
	t_image		img;
	t_rcast		rcast;
}		t_data;

/*		PARSING FUNCTIONS		*/

t_data	*ft_parse_map(char *map_name);
t_data	*ft_read_infos(int fd);

char	ft_get_info(char *line, t_data *data);
char	ft_check_data(t_data *data);
char	ft_is_map_char(char c);
char	ft_pathfinding(t_data *data);

char	*ft_strjoin_free(char *s1, char *s2);

void	*ft_get_image(char *line, t_data *data);
void	ft_get_player_coords(t_data *data);

int		ft_get_color(char *line);

/*		UTILS FUNCTIONS		*/

void	ft_free_all(t_data *data);

/*		HOOKS		*/

int		ft_close_button(t_data *data);
int		ft_player_move(int keycode, t_data *data);

/*		RAYCASTING		*/

//void	ft_render_game(t_data *data);
void	ft_raycast_horizontal(t_data *data, int angle);

/*		DRAW			*/

void	img_pix_put(t_image *img, int x, int y, int color);
void	ft_create_image(t_data *data);
void	ft_draw_bg(t_data *data);

/*		FI_INIT			*/
int ft_game_loop(t_data *data);


/*		FT_PAYCASTING_1			*/
float ft_deg_to_rad(float a);
float ft_fix_ang(float a);
void ft_cast_vertical_ray(t_data *data, float *disV);
void ft_cast_horizontal_ray(t_data *data, float *disH);
void ft_draw_rays_2d(t_data *data);

/*		FT_PAYCASTING_2			*/
void ft_draw_wall(t_data *data, float x, float distance, int color);
float castRay(t_data *data);
float	vector_distance(t_data *data);


#endif
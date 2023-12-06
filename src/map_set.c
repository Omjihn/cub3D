/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ashalagi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 08:54:19 by ashalagi          #+#    #+#             */
/*   Updated: 2023/12/06 13:11:43 by ashalagi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_draw_mini_map(t_data *data)
{
	int miniMapScale = 4; // Example scale factor to reduce the map size
	int xOffset = 10;	  // X offset from the screen corner
	int yOffset = 10;	  // Y offset from the screen corner

	int y = 0;
	while (y < data->map_max_y)
	{
		int x = 0;
		while (x < data->map_max_x)
		{
			int miniMapX = xOffset + (x * miniMapScale);
			int miniMapY = yOffset + (y * miniMapScale);
			int color;
			if (data->map[y][x] == '1')
			{
				color = 0xFFFFFF; // White for walls
			}
			else
			{
				color = 0x000000; // Black for empty space
			}

			// Draw the map element
			int dy = 0;
			while (dy < miniMapScale)
			{
				int dx = 0;
				while (dx < miniMapScale)
				{
					img_pix_put(&data->img, miniMapX + dx, miniMapY + dy, color);
					dx++;
				}
				dy++;
			}
			x++;
		}
		y++;
	}

	// Draw the player on the mini-map
	int playerMapX = xOffset + (int)(data->player->pos.x * miniMapScale);
	int playerMapY = yOffset + (int)(data->player->pos.y * miniMapScale);
	img_pix_put(&data->img, playerMapX, playerMapY, 0xFF0000); // Red dot for the player
}

/*
Remember to call ft_draw_mini_map(data); in your game loop after drawing the main game
elements but before rendering the frame to the window. This will ensure the mini-map
is updated and displayed correctly on each frame.
*/

// Inside your raycasting loop
// Calculate where exactly the ray hits the wall
double wallX; // Where exactly the wall was hit
if (side == 0)
	wallX = data->rcast->pos.y + perpWallDist * rayDirY;
else
	wallX = data->rcast->pos.x + perpWallDist * rayDirX;
wallX -= floor((wallX));

// Calculate X coordinate on the texture
int texX = int(wallX * double(texWidth));
if (side == 0 && rayDirX > 0)
	texX = texWidth - texX - 1;
if (side == 1 && rayDirY < 0)
	texX = texWidth - texX - 1;



// Inside the loop where you draw the wall slice
int draw_start;
int draw_end;

int y;
y = draw_start;
while (y < draw_end)
{
	int d = y * 256 - SCREENHEIGHT * 128 + lineHeight * 128; // 256 and 128 factors to avoid floats
	int texY = ((d * texHeight) / lineHeight) / 256;
	int color = texture[texX][texY]; // Fetch the color from the texture
	img_pix_put(&data->img, x, y, color);
}
y++



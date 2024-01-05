/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:44:51 by m_kamal           #+#    #+#             */
/*   Updated: 2024/01/02 17:44:51 by m_kamal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	render_line(t_data *cub3d, t_point p0, t_point p1)
{
	cub3d->minimap->line = start_line(p0, p1, cub3d->minimap->line_color);
	if (!cub3d->minimap->line)
		return ;
	scale_line(cub3d->minimap, cub3d->map, cub3d->minimap->line);
	draw_line(cub3d->minimap, cub3d->minimap->line);
}

static void	thicken_line(t_data *cub3d, t_point p0, t_point p1)
{
	int	i;

	i = 0;
	render_line(cub3d, p0, p1);
	while (i < 3)
	{
		cub3d->minimap->line->start.x++;
		cub3d->minimap->line->end.x++;
		cub3d->minimap->line->start.y++;
		cub3d->minimap->line->end.y++;
		draw_line(cub3d->minimap, cub3d->minimap->line);
		i++;
	}
	free(cub3d->minimap->line);
}

static void	render_player(t_data *cub3d)
{
	int	i;

	i = 0;
	cub3d->player->pos_scaled->x = cub3d->player->pos->x
		* cub3d->minimap->scale.x;
	cub3d->player->pos_scaled->y = cub3d->player->pos->y
		* cub3d->minimap->scale.y;
	pixel_put(cub3d->minimap, cub3d->player->pos_scaled->x,
		cub3d->player->pos_scaled->y, C_GREEN);
	if (cub3d->player->cardinal == NORTH)
		while (++i < 5)
			player_arrow(cub3d->minimap, cub3d->player, i);
	if (cub3d->player->cardinal == SOUTH)
		while (++i < 5)
			player_arrow(cub3d->minimap, cub3d->player, i);
	if (cub3d->player->cardinal == EAST)
		while (++i < 5)
			player_arrow(cub3d->minimap, cub3d->player, i);
	if (cub3d->player->cardinal == WEST)
		while (++i < 5)
			player_arrow(cub3d->minimap, cub3d->player, i);
}

static void	select_points(t_data *cub3d, int *x, int *y)
{
	if (*x < (cub3d->map->grid[*y][*x].local_x_max - 1) && \
		cub3d->map->grid[*y][*x].type == WALL && \
		cub3d->map->grid[*y][*x + 1].type == WALL)
	{
		thicken_line(cub3d, cub3d->map->grid[*y][*x],
			cub3d->map->grid[*y][*x + 1]);
	}
	if (*y < (cub3d->map->rows - 1) && \
		cub3d->map->grid[*y][*x].type == WALL && \
		*x < cub3d->map->grid[*y + 1]->local_x_max && \
		cub3d->map->grid[*y + 1][*x].type == WALL)
	{
		thicken_line(cub3d, cub3d->map->grid[*y][*x],
			cub3d->map->grid[*y + 1][*x]);
	}
	if (*x < (cub3d->map->grid[*y][*x].local_x_max - 1) && \
		cub3d->map->grid[*y][*x].type == PLAYER)
		render_player(cub3d);
}

void	render_minimap(t_data *cub3d)
{
	int	x;
	int	y;

	y = -1;
	cub3d->minimap->line_color = C_WHITE;
	while (++y < cub3d->map->rows)
	{
		x = 0;
		while (x < cub3d->map->grid[y][x].local_x_max)
		{
			select_points(cub3d, &x, &y);
			x++;
		}
	}
	mlx_put_image_to_window(cub3d->win->mlx, cub3d->win->m_win,
		cub3d->minimap->img_ptr, 0, 0);
	print_text(cub3d);
}

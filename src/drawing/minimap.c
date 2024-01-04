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
	cub3d->img->line = start_line(p0, p1, cub3d->img->line_color);
	if (!cub3d->img->line)
		write(2, "error parsing line", 18);
	scale_line(cub3d->img->line, 10);
	draw_line(cub3d->img, cub3d->img->line);
	free(cub3d->img->line);
}

void	select_points(t_data *cub3d, int *x, int *y)
{
	if (*x < (cub3d->map->grid[*y][*x].x_max - 1) && \
		cub3d->map->grid[*y][*x].type == WALL && \
		cub3d->map->grid[*y][*x + 1].type == WALL)
	{
		render_line(cub3d, cub3d->map->grid[*y][*x],
			cub3d->map->grid[*y][*x + 1]);
	}
	if (*y < (cub3d->map->rows - 1) && \
		cub3d->map->grid[*y][*x].type == WALL && \
		*x < cub3d->map->grid[*y + 1]->x_max && \
		cub3d->map->grid[*y + 1][*x].type == WALL)
	{
		render_line(cub3d, cub3d->map->grid[*y][*x],
			cub3d->map->grid[*y + 1][*x]);
	}
}

void	render_minimap(t_data *cub3d, int color)
{
	int	x;
	int	y;

	cub3d->img->line_color = color;
	y = -1;
	while (++y < cub3d->map->rows)
	{
		x = 0;
		while (x < cub3d->map->grid[y][x].x_max)
		{
			select_points(cub3d, &x, &y);
			x++;
		}
	}
	mlx_put_image_to_window(cub3d->win->mlx, cub3d->win->m_win,
		cub3d->img->img_ptr, 0, 0);
	print_text(cub3d);
}

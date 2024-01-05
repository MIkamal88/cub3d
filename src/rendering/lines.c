/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/30 09:07:53 by m_kamal           #+#    #+#             */
/*   Updated: 2023/12/30 09:07:53 by m_kamal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_line	*start_line(t_point p0, t_point p1, int color)
{
	t_line	*line;

	line = malloc(sizeof(t_line));
	if (!line)
		return (NULL);
	line->start.x = p0.x;
	line->start.y = p0.y;
	line->end.x = p1.x;
	line->end.y = p1.y;
	line->decision = 0;
	line->dx = 0;
	line->dy = 0;
	line->color = color;
	return (line);
}

static void	plotline_low(t_img *img, t_line *line)
{
	t_point	pixel;
	int		yi;

	pixel = line->start;
	line->dx = line->end.x - line->start.x;
	line->dy = line->end.y - line->start.y;
	yi = 1;
	if (line->dy < 0)
	{
		yi = -1;
		line->dy = line->dy * (-1);
	}
	line->decision = (2 * line->dy) - line->dx;
	while (pixel.x < line->end.x)
	{
		pixel_put(img, pixel.x, pixel.y, line->color);
		if (line->decision > 0)
		{
			pixel.y = pixel.y + yi;
			line->decision = line->decision + (2 * (line->dy - line->dx));
		}
		else
			line->decision = line->decision + 2 * line->dy;
		pixel.x++;
	}
}

static void	plotline_high(t_img *img, t_line *line)
{
	t_point	pixel;
	int		xi;

	pixel = line->start;
	line->dx = line->end.x - line->start.x;
	line->dy = line->end.y - line->start.y;
	xi = 1;
	if (line->dx < 0)
	{
		xi = -1;
		line->dx = -(line->dx);
	}
	line->decision = (2 * line->dx) - line->dy;
	while (pixel.y < line->end.y)
	{
		pixel_put(img, pixel.x, pixel.y, line->color);
		if (line->decision > 0)
		{
			pixel.x = pixel.x + xi;
			line->decision = line->decision + (2 * (line->dx - line->dy));
		}
		else
			line->decision = line->decision + 2 * line->dx;
		pixel.y++;
	}
}

void	scale_line(t_img *img, t_map *map, t_line *line)
{
	img->scale.y = img->h / map->rows;
	img->scale.x = img->w / map->x_max;
	line->start.x *= img->scale.x;
	line->start.y *= img->scale.y;
	line->end.x *= img->scale.x;
	line->end.y *= img->scale.y;
}

void	draw_line(t_img *img, t_line *line)
{
	line->dx = line->end.x - line->start.x;
	line->dy = line->end.y - line->start.y;
	if (ft_abs(line->dy) < ft_abs(line->dx))
	{
		if (line->start.x > line->end.x)
		{
			swap_points(&line->start, &line->end);
			plotline_low(img, line);
		}
		else
			plotline_low(img, line);
	}
	else
	{
		if (line->start.y > line->end.y)
		{
			swap_points(&line->start, &line->end);
			plotline_high(img, line);
		}
		else
			plotline_high(img, line);
	}
}

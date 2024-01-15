/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pbalbino <pbalbino@student.42abudhabi.a    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 05:32:35 by m_kamal           #+#    #+#             */
/*   Updated: 2024/01/14 17:09:44 by pbalbino         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_win	*new_win(int w, int h)
{
	t_win	*win;

	win = malloc(sizeof(t_win));
	win->mlx = mlx_init();
	win->height = h;
	win->width = w;
	win->m_win = mlx_new_window(win->mlx, win->width, win->height, "Cub3D");
	return (win);
}

static t_img	*new_img(int w, int h, t_win *window)
{
	t_img	*image;

	image = malloc(sizeof(t_img));
	if (!image)
		ft_error(NULL, MALLOC_ERR);
	if (h > window->height || w > window->width)
		ft_error(NULL, IMG_ERR);
	image->img_ptr = mlx_new_image(window->mlx, w, h);
	image->addr = mlx_get_data_addr(image->img_ptr, &(image->bpp),
			&(image->line_length), &(image->endian));
	image->w = w;
	image->h = h;
	image->line = NULL;
	return (image);
}

static t_data	*init_cub3d(int w, int h)
{
	t_data	*cub3d;

	cub3d = malloc(sizeof(t_data));
	if (!cub3d)
		ft_error(NULL, MALLOC_ERR);
	cub3d->map = NULL;
	cub3d->win = NULL;
	cub3d->player = NULL;
	cub3d->win = new_win(w, h);
	cub3d->scene = new_img(w, h, cub3d->win);
	cub3d->rays = malloc(sizeof(t_ray) * WINDOW_WIDTH);
	cub3d->game_color_buffer = malloc((WINDOW_WIDTH * WINDOW_HEIGHT) * sizeof(int));
	cub3d->minimap = new_img((0.2 * WINDOW_WIDTH), (0.2 * WINDOW_HEIGHT), \
		cub3d->win);
	return (cub3d);
}

static void	loop_mlx(t_data *cub3d)
{
	mlx_hook(cub3d->win->m_win, 17, 0, exit_window, cub3d);
	mlx_key_hook(cub3d->win->m_win, key_parse, cub3d);
	mlx_loop_hook(cub3d->win->mlx, render_loop, cub3d);
	mlx_loop(cub3d->win->mlx);
}
void print_map(t_data *cub3d) {
	int i;
	int j;

	i = -1;
	while (++i < cub3d->map->rows)
	{
		j = -1;
		while (++j < cub3d->map->x_max)
		{
			printf("%d", cub3d->map->grid[i][j].type);
		}
		printf("\n");
	}

}

int	main(int argc, char **argv)
{
	t_data	*cub3d;

	if (argc != 2)
		ft_error(NULL, ARGS_ERR);
	if (!valid_extension(argv[1], ".cub"))
		ft_error(NULL, MAP_ERR);
	cub3d = init_cub3d(WINDOW_WIDTH, WINDOW_HEIGHT);
	map_read(cub3d, argv[1]);
	print_map(cub3d);
	render_minimap(cub3d);
	get_current_rotation_angle(cub3d);
	loop_mlx(cub3d);
}

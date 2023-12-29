/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 05:32:35 by m_kamal           #+#    #+#             */
/*   Updated: 2023/12/29 05:32:35 by m_kamal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

static t_data	*init_cub3d(char *filename, int w, int h)
{
	t_data	*cub3d;

	cub3d = malloc(sizeof(t_data));
	if (!cub3d)
		ft_error(NULL, MALLOC_ERR);
	printf("%s\n", filename);
	cub3d->win = new_win(w, h);
	return (cub3d);
}

static void	loop_mlx(t_data *cub3d)
{
	mlx_hook(cub3d->win->m_win, 17, 0, exit_window, cub3d);
	mlx_key_hook(cub3d->win->m_win, key_parse, cub3d);
	mlx_loop(cub3d->win->mlx);
}

int	main(int argc, char **argv)
{
	t_data	*cub3d;
	char	*filename;
	char	**file_test;
	int		i;

	i = 0;
	if (argc != 2)
		ft_error(NULL, ARGS_ERR);
	filename = argv[1];
	file_test = ft_split(filename, '.');
	while (file_test[i])
		i++;
	if (ft_strcmp(file_test[i - 1], "cub") != 0)
	{
		free_double_ptr((void **)file_test);
		ft_error(NULL, MAP_ERR);
	}
	free_double_ptr((void **)file_test);
	cub3d = init_cub3d(filename, WINDOW_WIDTH, WINDOW_HEIGHT);
	loop_mlx(cub3d);
}

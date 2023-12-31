/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 10:12:51 by m_kamal           #+#    #+#             */
/*   Updated: 2023/12/29 10:12:51 by m_kamal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	map_error(void *pointer);

static void	write_err(char *str)
{
	write(2, str, ft_strlen(str));
}

void	ft_error(void *pointer, int code)
{
	if (code == MALLOC_ERR)
	{
		write_err(RED);
		write_err("Error:\n Malloc error.\n");
		write_err(RESET);
		exit(1);
	}
	else if (code == ARGS_ERR)
	{
		write_err(RED);
		write_err("Error:\n Wrong number of arguments.\n");
		write_err(RESET);
		exit(0);
	}
	else if (code == MAP_ERR)
		map_error(pointer);
	else if (code == EXIT)
		exit_window(pointer);
	// else if (code == IMG_ERR)
}

static void	map_error(void *pointer)
{
	t_data	*cub3d;

	cub3d = (t_data *)pointer;
	write_err(RED);
	write_err("Error:\n Invalid map.\n");
	write_err(RESET);
	free_all(cub3d);
	exit(0);
}

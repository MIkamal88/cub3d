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

static void	write_err(char *str)
{
	write(2, str, ft_strlen(str));
}

void	ft_error(t_data *cub3d, int code)
{
	if (code == MALLOC_ERR)
	{
		write_err(RED);
		write_err("Error: Malloc error.\n");
		exit(1);
	}
	if (code == ARGS_ERR)
	{
		write_err(RED);
		write_err("Error: Wrong number of arguments.\n");
		exit(0);
	}
	if (code == MAP_ERR)
	{
		write_err(RED);
		write_err("Error: Reading Map.\n");
		if (cub3d)
			free_all(cub3d);
		exit(0);
	}
}

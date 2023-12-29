/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: m_kamal <m_kamal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/29 07:29:25 by m_kamal           #+#    #+#             */
/*   Updated: 2023/12/29 07:29:25 by m_kamal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/libft/includes/libft.h"
# include "../libs/mlx/linux/mlx.h"
/* #include "../libs/mlx/mac/mlx.h" */
# include <math.h>
# include "colors.h"
# include "keybinds.h"

# define WINDOW_WIDTH	1920
# define WINDOW_HEIGHT	1080
# define IMG_SIZE		2073600

enum e_errs
{
	EXIT,
	ARGS_ERR,
	MALLOC_ERR,
	MAP_ERR,
	IMG_ERR,
};

typedef struct s_win
{
	void	*mlx;
	void	*m_win;
	int		width;
	int		height;
}	t_win;

typedef struct s_data
{
	t_win	*win;
}	t_data;

// Key Parsing Functions
int		key_parse(int key, t_data *cub3d);

// Destroy and Error handling Functions
void	ft_error(t_data *cub3d, int code);
void	free_all(t_data *cub3d);
void	free_double_ptr(void **d_array);
int		exit_window(t_data *cub3d);
#endif

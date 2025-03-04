/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gecarval <gecarval@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 20:32:15 by gecarval          #+#    #+#             */
/*   Updated: 2024/11/08 09:11:14 by gecarval         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/renderer.h"

void	free_life(t_lifeform *life, t_data *data)
{
	t_lifeform	*tmp;
	int			i;

	i = -1;
	while (++i < data->num_of_life)
	{
		tmp = life;
		life = life->next;
		pthread_mutex_destroy(&tmp->life_mutex);
		free(tmp);
	}
}

int	exit_data(t_data *data, int fd)
{
	if (data != NULL && data->processor != NULL)
		free(data->processor);
	if (data != NULL && data->img != NULL && data->img->img_ptr != NULL)
		mlx_destroy_image(data->ini, data->img->img_ptr);
	if (data != NULL && data->img != NULL)
		free(data->img);
	if (data != NULL && data->lsim != NULL && data->lsim->atrrules != NULL)
		ft_free_matrix((void **)data->lsim->atrrules);
	if (data != NULL && data->lsim != NULL && data->lsim->reprules != NULL)
		ft_free_matrix((void **)data->lsim->reprules);
	if (data != NULL && data->lsim != NULL && data->lsim->rules != NULL)
		ft_free_matrix((void **)data->lsim->rules);
	if (data != NULL && data->lsim != NULL && data->lsim->life != NULL)
		free_life(data->lsim->life, data);
	if (data != NULL && data->lsim != NULL)
		free(data->lsim);
	if (data != NULL && data->win != NULL)
		mlx_clear_window(data->ini, data->win);
	if (data != NULL && data->win != NULL)
		mlx_destroy_window(data->ini, data->win);
	if (data != NULL && data->ini != NULL)
		mlx_destroy_display(data->ini);
	if (data != NULL && data->ini != NULL)
		free(data->ini);
	if (data != NULL)
		free(data);
	exit(fd);
	return (0);
}

void	display_error(t_data *data, char *msg)
{
	ft_putstr_fd(msg, 2);
	exit_data(data, 1);
}

void	ft_set_params(t_data *data, int life_n, int radius, int part_n)
{
	data->num_of_life = life_n;
	data->radius = radius;
	data->part_num = part_n;
	data->lsim->atrg = 1;
	data->lsim->repg = 3;
	data->lsim->minrul = 0.3;
	data->lsim->maxrul = 1.5;
	data->lsim->minrep = 6 * data->radius;
	data->lsim->maxrep = 12 * data->radius;
	data->lsim->minatr = 30 * data->radius;
	data->lsim->maxatr = 60 * data->radius;
}

void	ft_init_program(t_data *data)
{
	data->ini = mlx_init();
	if (!data->ini)
		display_error(data, "init error\n");
	data->win = mlx_new_window(data->ini, data->winx, data->winy, "render");
	if (!data->win)
		display_error(data, "window error\n");
	data->lsim = (t_lifesim *)malloc(sizeof(t_lifesim));
	if (!data->lsim)
		display_error(data, "lifesim malloc error\n");
	ft_set_params(data, 2000, 1, 6);
	data->lsim->life = NULL;
	data->img = (t_img *)malloc(sizeof(t_img));
	if (!data->img)
		display_error(data, "img malloc error\n");
	data->img->img_ptr = mlx_new_image(data->ini, data->winx, data->winy);
	if (!data->img->img_ptr)
		display_error(data, "img ptr error\n");
	data->img->img_px = mlx_get_data_addr(data->img->img_ptr, &data->img->bpp,
			&data->img->llen, &data->img->end);
	if (!data->img->img_px)
		display_error(data, "img data error\n");
	data->processor = (t_processor *)malloc(sizeof(t_processor) * MAX_THREADS);
	if (!data->processor)
		display_error(data, "processor malloc error\n");
}

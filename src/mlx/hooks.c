/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lemos <lemos@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/29 00:00:00 by lemos             #+#    #+#             */
/*   Updated: 2026/10/29 00:00:00 by lemos            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../../includes/minirt.h"

int	close_window(t_app *app)
{
	mlx_destroy_window(app->mlx, app->win);
	mlx_destroy_display(app->mlx);
	free(app->mlx);
	exit(EXIT_SUCCESS);
}

void	init_hooks(t_app *app)
{
	mlx_hook(app->win, DestroyNotify, StructureNotifyMask, close_window, app);
	mlx_key_hook(app->win, key_press, app);
}

int	key_press(int keycode, t_app *app)
{
	if (keycode == XK_Escape)
		close_window(app);
	return (0);
}

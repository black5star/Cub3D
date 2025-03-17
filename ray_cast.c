/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:49:03 by het-taja          #+#    #+#             */
/*   Updated: 2025/03/17 16:49:04 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

double	dgr_to_rad(double degrees)
{
	return (degrees * (PI / 180.0));
}

double	dist_calc(t_game *game, double x, double y, double ray)
{
	double	dx;
	double	dy;
	double	dist;
	double	beta;

	dx = x - game->px;
	dy = y - game->py;
	beta = ray - game->pa;
	while (beta > PI)
		beta -= 2 * PI;
	while (beta < -PI)
		beta += 2 * PI;
	dist = (dx * cos(game->pa) + dy * sin(game->pa));
	return (dist);
}

double	complete_line(t_game *game, double x, double y, double ray)
{
	double	dist;

	if (wall_checker(game, round(x), round(y)))
	{
		detect_direction(game, round(x), round(y), ray);
		if (game->flag == 'E' || game->flag == 'W')
			game->pos = y;
		if (game->flag == 'S' || game->flag == 'N')
			game->pos = x;
		dist = dist_calc(game, x, y, ray);
		return (dist);
	}
	return (-1);
}

double	dda_line_drawing(t_game *game, double x, double y, double ray)
{
	double	x_inc;
	double	y_inc;
	double	dx;
	double	dy;
	double	step;

	dx = cos(ray);
	dy = sin(ray);
	if (fabs(dx) > fabs(dy))
		step = fabs(dx);
	else
		step = fabs(dy);
	if (!step)
		step = 0.1;
	x_inc = dx / step;
	y_inc = dy / step;
	while (x >= 0 && y >= 0)
	{
		dx = complete_line(game, x, y, ray);
		if (dx != -1)
			break ;
		x += x_inc;
		y += y_inc;
	}
	return (dx);
}

void	ray_cast(t_game *game, int x, int y, double ray)
{
	double	dist;
	double	angle;
	int		i;

	i = 0;
	angle = ray - (dgr_to_rad(FOV / 2));
	while (i <= 1280)
	{
		dist = dda_line_drawing(game, x, y, angle);
		vertical_line(game, i, dist);
		i++;
		angle += dgr_to_rad(ANG_STEP);
	}
}

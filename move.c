/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:48:43 by het-taja          #+#    #+#             */
/*   Updated: 2025/03/17 16:48:44 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	go_up(t_game *game)
{
	double	x;
	double	y;

	x = round(cos(game->pa) * SPEED);
	y = round(sin(game->pa) * SPEED);
	if (!can_move(game, game->px + x, game->py + y))
	{
		game->px += x;
		game->py += y;
	}
}

void	go_down(t_game *game)
{
	double	x;
	double	y;

	x = round(cos(game->pa) * SPEED);
	y = round(sin(game->pa) * SPEED);
	if (!can_move(game, game->px - x, game->py - y))
	{
		game->px -= x;
		game->py -= y;
	}
}

void	to_right(t_game *game)
{
	double	x;
	double	y;

	x = round(sin(game->pa) * SPEED);
	y = round(cos(game->pa) * SPEED);
	if (game->key[100] && !can_move(game, game->px - x, game->py + y))
	{
		game->px -= x;
		game->py += y;
	}
}

void	to_left(t_game *game)
{
	double	x;
	double	y;

	x = round(sin(game->pa) * SPEED);
	y = round(cos(game->pa) * SPEED);
	if (!can_move(game, game->px + x, game->py - y))
	{
		game->px += x;
		game->py -= y;
	}
}

void	ft_key_hook(t_game *game)
{
	if (game->key[97])
		to_left(game);
	if (game->key[100])
		to_right(game);
	if (game->key[119])
		go_up(game);
	if (game->key[115])
		go_down(game);
	if (game->key[130])
	{
		game->pa += dgr_to_rad(ANG_STEP + SPEED);
		if (game->pa >= (2 * PI))
			game->pa -= (2 * PI);
	}
	if (game->key[131])
	{
		game->pa -= dgr_to_rad(ANG_STEP + SPEED);
		if (game->pa <= 0)
			game->pa += (2 * PI);
	}
}

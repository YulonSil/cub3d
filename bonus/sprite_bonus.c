/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cclaude <cclaude@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 18:04:34 by cclaude           #+#    #+#             */
/*   Updated: 2020/01/08 17:02:40 by cclaude          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	ft_slocate(t_all *s, t_spr spr)
{
	double	angle;

	spr.x = (spr.x - s->pos.x) / spr.d;
	spr.y = (spr.y - s->pos.y) / spr.d;
	if (spr.y <= 0)
		angle = acos(spr.x) * 180 / M_PI;
	else
		angle = 360 - acos(spr.x) * 180 / M_PI;
	angle = s->dir.a - angle + 33;
	if (angle >= 180)
		angle -= 360;
	else if (angle <= -180)
		angle += 360;
	if (spr.c == '5')
		ft_sdraw(s, angle * s->win.x / 66, spr.d);
	else if (spr.c == '6')
		ft_ddraw(s, angle * s->win.x / 66, spr.d);
}

void	ft_sorder(t_all *s)
{
	t_spr	tmp;
	int		i;
	int		j;

	i = 0;
	while (i < s->map.spr - 1)
	{
		j = i + 1;
		while (j < s->map.spr)
		{
			if (s->spr[i].d < s->spr[j].d)
			{
				tmp = s->spr[i];
				s->spr[i] = s->spr[j];
				s->spr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

int		ft_slist(t_all *s)
{
	int		i;
	int		j;
	int		k;

	free(s->spr);
	if (!(s->spr = malloc(sizeof(t_spr) * s->map.spr)))
		return (-1);
	i = 0;
	j = 0;
	while (j < s->map.y)
	{
		k = 0;
		while (k < s->map.x)
		{
			if (ft_is(SPRITE, s->map.tab[j][k]))
			{
				s->spr[i].y = (double)j + 0.5;
				s->spr[i].x = (double)k + 0.5;
				s->spr[i++].c = s->map.tab[j][k];
			}
			k++;
		}
		j++;
	}
	return (1);
}

void	ft_sprite(t_all *s)
{
	int		i;

	i = 0;
	while (i < s->map.spr)
	{
		s->spr[i].d = hypot(s->spr[i].x - s->pos.x, s->spr[i].y - s->pos.y);
		i++;
	}
	ft_sorder(s);
	i = 0;
	while (i < s->map.spr)
	{
		s->hit.x = s->spr[i].x;
		s->hit.y = s->spr[i].y;
		ft_slocate(s, s->spr[i]);
		i++;
	}
	free(s->stk);
}

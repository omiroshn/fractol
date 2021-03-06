/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <omiroshn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 18:30:46 by omiroshn          #+#    #+#             */
/*   Updated: 2018/01/24 18:31:28 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

void	iter_mandelbrot(t_info *i)
{
	while (i->n < i->maxiterations)
	{
		i->z_re2 = i->z_re * i->z_re;
		i->z_im2 = i->z_im * i->z_im;
		if (i->z_re2 + i->z_im2 > 4)
			break ;
		i->z_im = 2 * i->z_re * i->z_im + i->c_im;
		i->z_re = i->z_re2 - i->z_im2 + i->c_re;
		i->n++;
	}
}

void	iter_julia(t_info *i)
{
	while (i->n < i->maxiterations)
	{
		i->z_re2 = i->z_re * i->z_re;
		i->z_im2 = i->z_im * i->z_im;
		if (i->z_re2 + i->z_im2 > 4)
			break ;
		i->z_im = 2 * i->z_re * i->z_im + i->k_im;
		i->z_re = i->z_re2 - i->z_im2 + i->k_re;
		i->n++;
	}
}

void	iter_mandelbar3(t_info *i)
{
	while (i->n < i->maxiterations)
	{
		i->z_re2 = i->z_re * i->z_re;
		i->z_im2 = i->z_im * i->z_im;
		if (i->z_re2 + i->z_im2 > 4)
			break ;
		i->z_im = i->z_re * i->z_im * -2.0 + i->c_im;
		i->z_re = i->z_re2 - i->z_im2 + i->c_re;
		i->n++;
	}
}

void	iter_mandelbar4(t_info *i)
{
	while (i->n < i->maxiterations)
	{
		i->z_re2 = i->z_re * i->z_re;
		i->z_im2 = i->z_im * i->z_im;
		if (i->z_re2 + i->z_im2 > 4)
			break ;
		i->z_im = (i->z_re2 * 3.0 - i->z_im2) * i->z_im + i->c_im;
		i->z_re = -(i->z_re2 - i->z_im2 * 3.0) * i->z_re + i->c_re;
		i->n++;
	}
}

void	iter_mandelbar5(t_info *i)
{
	while (i->n < i->maxiterations)
	{
		i->z_re2 = i->z_re * i->z_re;
		i->z_im2 = i->z_im * i->z_im;
		if (i->z_re2 + i->z_im2 > 4)
			break ;
		i->z_im = -4 * i->z_re * i->z_im * (i->z_re2 - i->z_im2) + i->c_im;
		i->z_re = i->z_re2 * i->z_re2 + i->z_im2 * i->z_im2
		- 6 * i->z_re2 * i->z_im2 + i->c_re;
		i->n++;
	}
}

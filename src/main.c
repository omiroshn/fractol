/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <omiroshn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 16:26:45 by omiroshn          #+#    #+#             */
/*   Updated: 2018/01/24 16:12:22 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fract.h"

double	ft_map(double value, double istart, double iend, double ostart, double oend)
{
    return (ostart + (oend - ostart) * ((value - istart) / (iend - istart)));
}

static inline int	rgb_to_int(int red, int green, int blue)
{
	int r;
	int g;
	int b;

	r = red & 0xFF;
	g = green & 0xFF;
	b = blue & 0xFF;
	return (r << 16 | g << 8 | b);
}

int		get_rgb_smooth(double t, int k)
{
	return (rgb_to_int((int)(9 * k * (1 - t) * t * t * t * 255),
		(int)(15 * k * (1 - t)* (1 - t) * t * t * 255),
		(int)(8.5 * k * (1 - t) * (1 - t) * (1 - t) * t * 255)));
}

int		fract_inter(double t, int offset)
{
	t_color color;

	if (t > 1.0)
		t = 1.0;
	color.channel[(2 + offset) % 3] = (t_byte)(9 * (1 - t) * t * t * t * 255);
 	color.channel[(1 + offset) % 3] = (t_byte)(15 * (1 - t) * (1 - t) * t * t * 255);
 	color.channel[(0 + offset) % 3] = (t_byte)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	color.channel[3] = 0;
	return (color.color);
}

void	draw(t_info *i)
{
	i->y = i->cunt;
	while (i->y < i->end)
	{
		i->c_im = i->minim + (WIDTH - i->y) * i->im_factor;
		i->x = 0;
		while (i->x < HEIGHT)
		{
			i->c_re = i->minre + i->x * i->re_factor;

			i->z_im = i->c_im;
			i->z_re = i->c_re;

			i->n = 0;
			i->func(i);
			i->bright = fract_inter(((double)i->n / i->maxiterations), i->offset);
			if (i->n == i->maxiterations)
				i->bright = 0;
			i->pix = (i->x + i->y * WIDTH);
			i->map.image[i->pix] = i->bright;
			i->x++;
		}
		i->y++;
	}
}

void	threads_crete(t_info *in)
{
	pthread_t	threads[THREADS];
	int			*status_addr;
	int			status;
	t_info		info[THREADS];
	unsigned	y;
	int			i;

	in->re_factor = in->dre / (WIDTH - 1);
	in->im_factor = in->dre / (HEIGHT - 1);
	i = 0;
	y = 0;
	while (i < THREADS)
	{
		info[i] = *in;
		info[i].cunt = y;
		y += HEIGHT / THREADS;
		info[i].end = y;
		pthread_create(&threads[i], NULL, (void *(*)(void *))draw, (void *)&info[i]);
		i++;
	}
	while (i-- > 0)
		if ((status = pthread_join(threads[i], (void**)&status_addr)))
			printf("Error join thread\n");
	mlx_put_image_to_window(in->map.mlx, in->map.win, in->map.image_ptr, 0, 0);
	mlx_string_put(in->map.mlx, in->map.win, 10, 10, 0xFF0000, ft_itoa(in->maxiterations));
}

void	loops(t_info info, void *mlx)
{
	info.map.mlx = mlx;
	info.map.win = mlx_new_window(info.map.mlx, WIDTH, HEIGHT, info.name);
	info.map.image_ptr = mlx_new_image(info.map.mlx, WIDTH, HEIGHT);
	info.map.image = (int *)mlx_get_data_addr(info.map.image_ptr,
		&info.map.bits_per_pixel, &info.map.size, &info.map.endian);
	threads_crete(&info);
	mlx_hook(info.map.win, 2, 5, key_function, &info);
	mlx_hook(info.map.win, 17, 1L << 17, exit_func, &info);
	mlx_hook(info.map.win, 6, 5, julia_motion, &info);
	mlx_mouse_hook(info.map.win, mouse_hook, &info);
	mlx_loop(info.map.mlx);
}

void	init(char *name, t_info *i)
{
	i->name = name;
	i->maxiterations = 50;
	i->moveX = -0.5;
	i->moveY = 0;
	i->zoom = 1;
	i->minre = -2.0;
	i->minim = -2.0;
	i->dre = 4.0;
	i->is_julia = -1;
	i->k_im = 0.6;
	i->k_re = -0.4;
}

void	options()
{
	ft_putendl("Usage : ./fractol <name>");
	ft_putendl("                  mandelbrot");
	ft_putendl("                  julia");
	ft_putendl("                  bs");
	ft_putendl("                  bs_cubic");
	ft_putendl("                  bs_perpend");
	ft_putendl("                  mandelbar3");
	ft_putendl("                  mandelbar4");
	ft_putendl("                  mandelbar5");
	ft_putendl("                  perp_mandelbrot");
	ft_putendl("                  celtic_mandelbar");
	ft_putendl("                  celtic_perpend");
	ft_putendl("                  perpend_buffalo");
	exit(0);
}

void	check(int argc, char **a)
{
	int i;

	i = 1;
	printf("%i\n", argc);
	while (i < argc)
	{
		if (!ft_strequ(a[i], "mandelbrot") && !ft_strequ(a[i], "julia")
			&& !ft_strequ(a[i], "bs") && !ft_strequ(a[i], "bs_cubic")
			&& !ft_strequ(a[i], "bs_perpend") && !ft_strequ(a[i], "mandelbar3")
			&& !ft_strequ(a[i], "mandelbar4") && !ft_strequ(a[i], "mandelbar5")
			&& !ft_strequ(a[i], "perp_mandelbrot") && !ft_strequ(a[i], "celtic_mandelbar")
			&& !ft_strequ(a[i], "celtic_perpend") && !ft_strequ(a[i], "perpend_buffalo"))
		{
			ft_putstr("Wrong arguments! ");
			ft_putendl("try:");
			options();
		}
		i++;
	}
}

void	run(int argc, char **argv)
{
	static t_info info[12];
	void *mlx;
	int i;
	int cunt;

	i = -1;
	cunt = 1;
	mlx = mlx_init();
	while (++i < argc)
	{
		check(argc, argv);
		if (ft_strequ(argv[cunt], "mandelbrot"))
			info[i].func = &iter_mandelbrot;
		else if (ft_strequ(argv[cunt], "julia"))
			info[i].func = &iter_julia;
		else if (ft_strequ(argv[cunt], "mandelbar3"))
			info[i].func = &iter_mandelbar3;
		else if (ft_strequ(argv[cunt], "mandelbar4"))
			info[i].func = &iter_mandelbar4;
		else if (ft_strequ(argv[cunt], "mandelbar5"))
			info[i].func = &iter_mandelbar5;
		else if (ft_strequ(argv[cunt], "perp_mandelbrot"))
			info[i].func = &iter_perp_mand;
		else if (ft_strequ(argv[cunt], "celtic_mandelbar"))
			info[i].func = &iter_celtic_mand;
		else if (ft_strequ(argv[cunt], "bs"))
			info[i].func = &iter_burning_ship;
		else if (ft_strequ(argv[cunt], "bs_cubic"))
			info[i].func = &iter_cubic_burning_ship;
		else if (ft_strequ(argv[cunt], "bs_perpend"))
			info[i].func = &iter_bs_perpend;
		else if (ft_strequ(argv[cunt], "celtic_perpend"))
			info[i].func = &iter_celtic_perpend;
		else if (ft_strequ(argv[cunt], "perpend_buffalo"))
			info[i].func = &iter_perpend_buffalo;
		init(argv[cunt], &info[i]);
		loops(info[i], mlx);
		cunt++;
	}
}

int		main(int argc, char **argv)
{
	run(argc, argv);
	return (0);
}

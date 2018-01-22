/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omiroshn <omiroshn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/07 18:24:30 by omiroshn          #+#    #+#             */
/*   Updated: 2018/01/22 17:53:22 by omiroshn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_H
# define FRACT_H

# define WIDTH 800
# define HEIGHT 800
# define THREADS 16
# define DB(x) ((double)x)
# define MAP(x, y, z, a, b) (DB(a) + (DB(b) - DB(a)) * ((DB(x) - DB(y)) / (DB(z) - DB(y))))

# define MAC_ESC_BUT 53
# define MAC_BUT_MINUS 27
# define MAC_BUT_PLUS 24
# define MAC_ARROW_UP 126
# define MAC_ARROW_DOWN 125
# define MAC_ARROW_LEFT 123
# define MAC_ARROW_RIGHT 124
# define MAC_BUT_1 18
# define MAC_BUT_2 19

# define LINUX_ESC_BUT 65307
# define LINUX_BUT_MINUS 45
# define LINUX_BUT_PLUS 61
# define LINUX_ARROW_UP 65362
# define LINUX_ARROW_DOWN 65364
# define LINUX_ARROW_LEFT 65361
# define LINUX_ARROW_RIGHT 65363
# define LINUX_BUT_1 49
# define LINUX_BUT_2 50

# include "libft/includes/libft.h"
# include <math.h>
# include <fcntl.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <mlx.h>
# include <pthread.h>

typedef struct	s_complex
{
	float		real;
	float		im;
}				t_complex;

typedef	struct	s_mapinfo
{
	int			size;
	int			*image;
	int			endian;
	int			bits_per_pixel;
	void		*mlx;
	void		*win;
	void		*image_ptr;
}				t_mapinfo;

typedef struct	s_info
{
	double		k_re;
	double		k_im;
	int			is_julia;
	double		re_factor;
	double		im_factor;
	double		dre;
	double		minre;
	double		minim;
	double		maxre;
	double		maxim;
	char		*name;
	unsigned	x;
	unsigned	y;
	unsigned	cunt;
	unsigned	end;
	double		bright;
	double		c_im;
	double		c_re;
	int			n;
	double		z_re2;
	double		z_im2;
	double		z_im;
	double		z_re;
	int			pix;
	long long	maxiterations;
	float		moveX;
	float		moveY;
	float		zoom;
	void		(*func)(struct s_info *i);
	t_mapinfo	map;
}				t_info;

void	draw(t_info *in);
void	threads_crete(t_info *in);

void	iter_julia(t_info *i);
void	iter_mandelbrot(t_info *i);
void	iter_mandelbar3(t_info *i);
void	iter_mandelbar4(t_info *i);
void	iter_mandelbar5(t_info *i);
void	iter_perp_mand(t_info *i);
void	iter_celtic_mand(t_info *i);
void	iter_burning_ship(t_info *i);
void	iter_cubic_burning_ship(t_info *i);
void	iter_bs_perpend(t_info *i);
void	iter_celtic_perpend(t_info *i);
void	iter_perpend_buffalo(t_info *i);

void	init(char *name, t_info *i);
void	init_mandelbrot(t_info *i);
void	init_julia(t_info *i);

int		exit_func(void *param);
int		key_function(int keycode, void *param);
int		mouse_hook(int mousecode, int x, int y, t_info *i);
int		julia_motion(int x, int y, t_info *i);
double	ft_map(double value, double istart, double iend, double ostart, double oend);

#endif
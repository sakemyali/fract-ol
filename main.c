/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosakura <mosakura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 04:34:32 by mosakura          #+#    #+#             */
/*   Updated: 2025/12/08 04:46:10 by mosakura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	print_usage(void)
{
	ft_putendl_fd("Usage:", 1);
	ft_putendl_fd("  ./fractol mandelbrot", 1);
	ft_putendl_fd("  ./fractol burningship", 1);
	ft_putendl_fd("  ./fractol julia <cx> <cy>", 1);
}

static void	set_julia_params(t_fractal *fractal, char **argv)
{
	double	cx;
	double	cy;

	if (!ft_is_valid_float(argv[2]) || !ft_is_valid_float(argv[3]))
	{
		ft_putendl_fd("Error: cx and cy must be valid numbers.", 1);
		exit_error(fractal);
	}
	cx = ft_atof(argv[2]);
	cy = ft_atof(argv[3]);
	fractal->cx = cx;
	fractal->cy = cy;
}

static void	handle_julia(t_fractal *fractal, int argc, char **argv)
{
	if (argc == 4)
		set_julia_params(fractal, argv);
	else
	{
		fractal->cx = -0.745429;
		fractal->cy = 0.05;
	}
}

int	draw_fractal(t_fractal *fractal, char *query)
{
	if (ft_strncmp(query, "mandelbrot", 7) == 0)
		draw_mandelbrot(fractal);
	else if (ft_strncmp(query, "julia", 6) == 0)
	{
		if (!fractal->cx && !fractal->cy)
		{
			fractal->cx = -0.745429;
			fractal->cy = 0.05;
		}
		draw_julia(fractal);
	}
	else if (ft_strncmp(query, "burningship", 5) == 0)
		draw_burning_ship(fractal);
	else
	{
		ft_putendl_fd("Available fractals: mandelbrot,\
			 julia <x> <y>, burningship", 1);
		exit_fractal(fractal);
	}
	mlx_put_image_to_window(fractal->mlx, fractal->window, fractal->image, 0,
		0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_fractal	*fractal;

	if (!check_args(argc))
	{
		print_usage();
		return (0);
	}
	fractal = malloc(sizeof(t_fractal));
	if (!fractal)
		return (1);
	init_fractal(fractal);
	if (ft_strncmp(argv[1], "julia", 6) == 0)
		handle_julia(fractal, argc, argv);
	init_mlx(fractal);
	init_hooks(fractal);
	draw_fractal(fractal, argv[1]);
	mlx_loop(fractal->mlx);
	return (0);
}

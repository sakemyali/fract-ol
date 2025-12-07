#include "fractol.h"
#include "minilibx_opengl_20191021/mlx.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * If MALLOC goes bad (improbable)
*/
static void	malloc_error(void)
{
	perror("Problems with malloc");
	exit(EXIT_FAILURE);
}



static void	data_init(t_fractal *fractal)
{
	fractal->escape_value = 4; // 2 ^ 2, my hypotenuse
	fractal->iterations_defintion = 42; 
	fractal->shift_x = 0.0;
	fractal->shift_y = 0.0;
	// zoom factor
	fractal->zoom = 1.0;
}


static void	events_init(t_fractal *fractal)
{
    /* Use mlx_key_hook for portability across macOS/Linux MLX variants */
    mlx_key_hook(fractal->mlx_window, handle_key, fractal);
    mlx_hook(fractal->mlx_window,
	    ButtonPress,
	    ButtonPressMask,
	    handle_mouse,
	    fractal);
    mlx_hook(fractal->mlx_window,
	    DestroyNotify,
	    StructureNotifyMask,
	    handle_close,
	    fractal);
    mlx_hook(fractal->mlx_window,
	    MotionNotify,
	    PointerMotionMask,
	    handle_julia_motion,
	    fractal);
}

/*
 * INIT 
 * ~mlx
 * ~listening events
 * ~hooks data
*/
void	fractol_init(t_fractal *fractal)
{
	//MLX stuff
	fractal->mlx_connection = mlx_init();
	if (NULL == fractal->mlx_connection)
		malloc_error();
	fractal->mlx_window = mlx_new_window(fractal->mlx_connection,
										WIDTH,
										HEIGHT,
										fractal->name);
	if (NULL == fractal->mlx_window)
	{
		free(fractal->mlx_connection);
		malloc_error();
	}
	fractal->img.img_ptr = mlx_new_image(fractal->mlx_connection,
										WIDTH, HEIGHT);
	if (NULL == fractal->img.img_ptr)
	{
		mlx_destroy_window(fractal->mlx_connection, fractal->mlx_window);
		free(fractal->mlx_connection);
		malloc_error();
	}
	fractal->img.pixels_ptr = mlx_get_data_addr(fractal->img.img_ptr,
												&fractal->img.bpp,
												&fractal->img.line_len,
												&fractal->img.endian);
	events_init(fractal);
	data_init(fractal);
}

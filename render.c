#include "fractol.h"
#include "minilibx_opengl_20191021/mlx.h"

/*
 * Put a pixel in my image buffer
*/
static void	img_put_pixel(int x, int y, t_img *img, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}
	
/*
 * EASY TOGGLE mandel & julia
*/
static void	set_c_for_fractal(t_complex *z, t_complex *c, t_fractal *fractal)
{
	if (!ft_strncmp(fractal->name, "julia", 5))
	{
		c->x = fractal->julia_x;
		c->y = fractal->julia_y;
	}
	else
	{
		c->x = z->x;
		c->y = z->y;
	}
}


/*
 * 						 ✅ map()
		   	0__________800     -2___________+2    
 *			|			 |     |            |
 *			|			 |	   |            |
 *		800	|			 |     |            |
 *			|			 |     |            |
 *			|			 |     |            |
 *			|____________|     |____________|

 *	
 *		MANDELBROT
 *		z = z^2 + c
 *		z initially is (0, 0)
 *		c is the actual point
 *
 *		z = z^2 + c -> z1 = c + c
 *
 *		JULIA
 *		./fractol julia <real> <i> 
 *		z = pixel_point + constant
*/
static void	render_pixel(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;

	i = 0;
	// pixel coordinate x && y scaled to fit mandel needs 
	//                                 --> 📏 <--			🕹🕹🕹 🕹

	z.x = (ft_map(x, -2, +2, 0, WIDTH) * fractal->zoom) + fractal->shift_x;
	z.y = (ft_map(y, +2, -2, 0, HEIGHT) * fractal->zoom) + fractal->shift_y;


	set_c_for_fractal(&z, &c, fractal);


	// How many times you want to iterate z^2 + c
	//	to check if the point escaped?
	while (i < fractal->iterations_defintion)
	{
		// actual z^2 + c	
		// z = z^2 + c
	z = complex_add(complex_square(z), c);
		
		// Is the value escaped???
		// if hypotenuse > 2 i assume the point has escaped
		if ((z.x * z.x) + (z.y * z.y) > fractal->escape_value)
		{
			color = ft_map(i, BLACK, WHITE, 0, fractal->iterations_defintion);
			img_put_pixel(x, y, &fractal->img, color);
			return ;
		}
		++i;	
	}
	// We are in MANDELBROT given the iterations made
	img_put_pixel(x, y, &fractal->img, WHITE);
}



/*
 * Actual 🍖
 *
 * 				
 *		   	____800_______
 *			|			 |
 *			|			 |
 *		800	|			 |
 *			|			 |
 *			|			 |
 *			|____________|
*/
void	fractol_render(t_fractal *fractal)
{
	int	x;
	int	y;

	y = -1;
	while (++y < HEIGHT)
	{
		x = -1;
		while (++x < WIDTH)
		{
			render_pixel(x, y, fractal);
		}
	}
	mlx_put_image_to_window(fractal->mlx_connection,
							fractal->mlx_window,
							fractal->img.img_ptr,
							0, 0);	

}

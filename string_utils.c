#include "fractol.h"


int	ft_strncmp(char *s1, char *s2, int n)
{
	int i;

	if (n <= 0)
		return (0);
	/* NULL handling: if both NULL -> equal, otherwise not equal */
	if (s1 == NULL || s2 == NULL)
		return (s1 == s2 ? 0 : 1);
	i = 0;
	while (i < n && s1[i] && s1[i] == s2[i])
		++i;
	if (i == n)
		return (0);
	/* return difference as unsigned char like strncmp */
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

/*
 * RECURSION
*/
void	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL || fd < 0)
		return;
	while (*s)
	{
		write(fd, s, 1);
		++s;
	}
}

/*
 * ALPHA TO DOUBLE
 * similar to atoi, but dealing with floats
 * takes the cmnd line args and
 * converts to long double (typedef ldbl)
*/
double	ft_atod(char *s)
{
	long    integer_part;
	double  fractional_part;
	double  pow;
	int     sign;

	if (s == NULL)
		return (0.0);
	integer_part = 0;
	fractional_part = 0.0;
	sign = 1;
	pow = 1.0;
	/* skip whitespace */
	while ((*s >= 9 && *s <= 13) || *s == 32)
		++s;
	/* sign */
	if (*s == '+' || *s == '-')
	{
		if (*s == '-')
			sign = -1;
		++s;
	}
	/* integer part */
	while (*s >= '0' && *s <= '9')
		integer_part = (integer_part * 10) + (*s++ - '0');
	/* fractional part */
	if (*s == '.')
		++s;
	while (*s >= '0' && *s <= '9')
	{
		pow /= 10.0;
		fractional_part += (*s++ - '0') * pow;
	}
	return ((integer_part + fractional_part) * sign);
}

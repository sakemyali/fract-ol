/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosakura <mosakura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 04:41:06 by mosakura          #+#    #+#             */
/*   Updated: 2025/12/08 04:46:40 by mosakura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	ft_is_valid_float(const char *s)
{
	int	has_digit;

	has_digit = 0;
	if (*s == '+' || *s == '-')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		has_digit = 1;
		s++;
	}
	if (*s == '.')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		has_digit = 1;
		s++;
	}
	if (has_digit && *s == '\0')
		return (1);
	return (0);
}

static double	parse_int_part(const char **s)
{
	double	num;

	num = 0.0;
	while (**s >= '0' && **s <= '9')
	{
		num = num * 10.0 + (**s - '0');
		(*s)++;
	}
	return (num);
}

static double	parse_frac_part(const char **str2)
{
	double	frac;
	double	div;

	frac = 0.0;
	div = 1.0;
	while (**str2 >= '0' && **str2 <= '9')
	{
		frac = frac * 10.0 + (**str2 - '0');
		div *= 10.0;
		(*str2)++;
	}
	return (frac / div);
}

double	ft_atof(const char *str)
{
	double	num;
	double	frac;
	int		sign;

	num = 0.0;
	frac = 0.0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	num = parse_int_part(&str);
	if (*str == '.')
	{
		str++;
		frac = parse_frac_part(&str);
	}
	return (sign * (num + frac));
}

int	check_args(int argc)
{
	if (argc != 2 && argc != 4)
		return (0);
	return (1);
}

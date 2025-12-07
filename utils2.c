/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mosakura <mosakura@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/08 02:38:13 by mosakura          #+#    #+#             */
/*   Updated: 2025/12/08 03:07:26 by mosakura         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t				i;
	const unsigned char	*us1;
	const unsigned char	*us2;

	us1 = (const unsigned char *)s1;
	us2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (us1[i] != us2[i] || us1[i] == '\0')
			return ((int)(us1[i] - us2[i]));
		i++;
	}
	return (0);
}

static void	ft_putstr_fd(char *s, int fd)
{
	size_t	slen;
	size_t	total;
	ssize_t	pdone;

	if (!s || fd < 0)
		return ;
	slen = ft_strlen(s);
	total = 0;
	while (slen - total > WRITE_MAX)
	{
		pdone = write(fd, s + total, WRITE_MAX);
		if (pdone < 0)
			return ;
		total += (size_t)pdone;
	}
	if (slen > total)
		write(fd, s + total, slen - total);
}

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

int	ft_isdigit(int c)
{
	return ((c >= '0' && c <= '9'));
}

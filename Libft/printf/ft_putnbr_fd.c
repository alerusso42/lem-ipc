/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alerusso <alessandro.russo.frc@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 16:42:50 by alerusso          #+#    #+#             */
/*   Updated: 2026/01/05 16:28:42 by alerusso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_fd(int n, t_fd fd)
{
	char	str[12];
	int		temp_num;
	int		index;

	index = 0;
	if (n < 0)
		str[index++] = '-';
	if (n == 0)
		str[index] = '0';
	temp_num = n;
	while ((temp_num > 9) || (temp_num < -9))
	{
		index++;
		temp_num /= 10;
	}
	str[index + 1] = '\0';
	while (n != 0)
	{
		if (n < 0)
			str[index--] = (((n % 10) * -1) + 48);
		else
			str[index--] = ((n % 10) + 48);
		n /= 10;
	}
	WRITE(fd.p, str, ft_strlen(str));
}

/*
int	main()
{
	int		fd;

	fd = open("testoh.txt", O_RDWR);
	if (fd == -1)
		return (1);
	ft_putnbr_fd(52352, fd);
	close(fd);
	return (0);
}*/

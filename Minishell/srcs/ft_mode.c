/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 10:06:43 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/12 19:55:59 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_keys.h"

# define MAX_LENGTH 6

void		ft_raw_mode(void)
{
	struct termios	attr;

	tcgetattr(0, &attr);
	attr.c_lflag &= ~(ECHO | ICANON);
	attr.c_oflag &= ~(OPOST);
	attr.c_cc[VMIN] = 1;
	attr.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &attr);
}

void		ft_default_mode(void)
{
	struct termios	attr;

	tcgetattr(0, &attr);
	attr.c_lflag |= (ECHO | ICANON);
	attr.c_oflag |= (OPOST);
	tcsetattr(0, TCSADRAIN, &attr);
}

void		ft_put_fake_str(const char *str)
{
	while (*str)
		ioctl(0, TIOCSTI, str++);
}

int			ft_check_input(void)
{
	char	buff[6];
	char	key;

	key = 0;
	while (key != 1)
	{
		ft_raw_mode();
		(void)memset(buff, 0, MAX_LENGTH);
		read(0, buff, MAX_LENGTH);
		ft_default_mode();
		if (ft_key_isenter(buff))
			key = 1;
		else if (ft_key_istab(buff))
			ft_printf("[TAB]\n");
		else if (ft_key_isleft(buff))
			ft_printf("[LEFT]\n");
		else if (ft_key_isright(buff))
			ft_printf("[RIGHT]\n");
		else if (ft_key_isup(buff))
			ft_printf("[UP]\n");
		else if (ft_key_isdown(buff))
			ft_printf("[DOWN]\n");
		else if (ft_key_isctrl_d(buff))
			ft_printf("[CTRLD]\n");
		else
			ft_put_fake_str(buff);
	}
	ioctl(0, TIOCSTI, "\n");
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 10:06:43 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/14 19:36:38 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_keys.h"

static void		ft_raw_mode(void)
{
	struct termios	attr;

	tcgetattr(0, &attr);
	attr.c_lflag &= ~(ECHO | ICANON);
	attr.c_oflag &= ~(OPOST);
	attr.c_cc[VMIN] = 1;
	attr.c_cc[VTIME] = 0;
	tcsetattr(0, TCSADRAIN, &attr);
}

void			ft_default_mode(void)
{
	struct termios	attr;

	tcgetattr(0, &attr);
	attr.c_lflag |= (ECHO | ICANON);
	attr.c_oflag |= (OPOST);
	tcsetattr(0, TCSADRAIN, &attr);
	ft_putchar('\n');
}

static int		ft_get_char(size_t *col)
{
	char	c;
	char	key;

	ft_raw_mode();
	read(0, &c, 1);
	if ((key = ft_key_iscontrol(c)) == K_NONE)
		key = ft_key_isarrow(c);
	if (key == K_NONE)
		ft_add_input(c, col);
	return (key);
}

int			ft_check_input(char **envp, size_t *col)
{
	int		key;

	while (1)
	{
		key = ft_get_char(col);
		if (key == K_TAB)
		{
			ft_completion(envp, col);
			return (1);
		}
		else if (key == K_BACK)
		{
			if (*col > 0)
				ft_remove_input(col);
		}
		else if (key == K_LEFT)
		{
			if (*col > 0)
			{
				ft_printf("\033[1D");
				(*col)--;
			}
		}
		else if (key == K_RIGHT)
		{
			if (*col < ft_strlen(*ft_get_input()))
			{
				(*col)++;
				ft_printf("\033[1C");
			}
		}
		else if (key == K_UP)
			;
		else if (key == K_DOWN)
			;
		else if (key == K_CTRL_D)
		{
			ft_default_mode();
			return (-1);
		}
		else if (key == K_RETURN)
		{
			ft_default_mode();
			return (0);
		}
	}
}

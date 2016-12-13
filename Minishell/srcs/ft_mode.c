/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 10:06:43 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/13 19:27:24 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_keys.h"

#define MAX_LENGTH 6

#define K_RETURN	0
#define K_TAB		1
#define K_LEFT		2
#define K_RIGHT		3
#define K_UP		4
#define K_DOWN		5
#define K_CTRL_D	6
#define K_BACK		7

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

int			ft_get_char(void)
{
	char	buff[6];

	ft_raw_mode();
	(void)memset(buff, 0, MAX_LENGTH);
	read(0, buff, MAX_LENGTH);
	if (ft_key_isenter(buff))
		return (K_RETURN);
	else if (ft_key_istab(buff))
		return (K_TAB);
	else if (ft_key_isleft(buff))
		return (K_LEFT);
	else if (ft_key_isright(buff))
		return (K_RIGHT);
	else if (ft_key_isup(buff))
		return (K_UP);
	else if (ft_key_isdown(buff))
		return (K_DOWN);
	else if (ft_key_isctrl_d(buff))
		return (K_CTRL_D);
	else if (ft_key_isreturn(buff))
		return (K_BACK);
	else
		return (*buff);
}

char	**get_input(void)
{
	static char	*input = NULL;

	if (input == NULL)
		input = ft_strnew(4096);
	return (&input);
}

void	ft_strinsert(char **str, char c, size_t index)
{
	char	*ret;

	if (!str || index > ft_strlen(*str))
		return ;
	ret = ft_strnew(ft_strlen(*str) + 1);
	ret = ft_strncpy(ret, *str, index);
	ret[index] = c;
	ret = ft_strcat(ret, *str + index);
	ft_strdel(str);
	*str = ft_strdup(ret);
	ft_strdel(&ret);
}

void	ft_strremove(char **str, size_t index)
{
	char	*ret;

	if (!str || index > ft_strlen(*str))
		return ;
	ret = ft_strnew(ft_strlen(*str) - 1);
	ret = ft_strncpy(ret, *str, index);
	ret[index - 1] = 0;
	ret = ft_strcat(ret, *str + index);
	ft_strdel(str);
	*str = ft_strdup(ret);
	ft_strdel(&ret);
}

int			ft_check_input(size_t *col)
{
	int		key;

	key = ft_get_char();
	if (key == K_TAB)
		;//ft_printf("|TAB|");
	else if (key == K_BACK)
	{
		if (*col > 0)
		{
			ft_printf("\033[%dD", (*col) ? *col : -1);
			for (int i = 0; i < (int)ft_strlen(*get_input()) + (*col == 1); i++)
				ft_putchar(' ');
			ft_printf("\033[%dD", ft_strlen(*get_input()));
			ft_strremove(get_input(), *col);
			ft_printf("%s", *get_input());
			(*col)--;
			ft_printf("\033[%dD", ft_strlen(*get_input()));
			ft_printf("\033[%dC", (*col) ? *col : -1);
		}
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
		if (*col < ft_strlen(*get_input()))
		{
			(*col)++;
			ft_printf("\033[1C");
		}
	}
	else if (key == K_UP)
		;//ft_printf("|UP|");
	else if (key == K_DOWN)
		;//ft_printf("|DOWN|");
	else if (key == K_CTRL_D)
	{
		ft_default_mode();
		ft_putchar('\n');
		return (-1);
	}
	else if (key == K_RETURN)
	{
		ft_default_mode();
		ft_putchar('\n');
		return (0);
	}
	else
	{
		if (ft_isprint(key))
		{
			ft_printf("\033[%dD", (*col) ? *col : -1);
			ft_strinsert(get_input(), key, *col);
			ft_printf("%s", *get_input());
			(*col)++;
			ft_printf("\033[%dD", ft_strlen(*get_input()));
			ft_printf("\033[%dC", (*col) ? *col : -1);
		}
	}
	return (1);
}

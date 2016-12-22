/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mode.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 10:06:43 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/22 15:50:53 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_shell.h"
#include "libft.h"
#include "ft_keys.h"

void			ft_raw_mode(void)
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

	read(0, &c, 1);
	if (g_reset)
	{
		ioctl(0, TIOCSTI, &c);
		return (-2);
	}
	if ((key = ft_key_iscontrol(c)) == K_NONE)
		key = ft_key_isarrow(c);
	if (key == K_NONE)
		ft_add_input(c, col);
	return (key);
}

int				ft_check_input(char **envp, size_t *col)
{
	int				key;
	int				i;
	static t_keys	key_funcs[9];

	ft_memcpy(key_funcs, ((t_keys[9])
	{{K_CTRL_D, &ft_key_ctrl_d}, {K_RETURN, &ft_key_return},
	{K_TAB, &ft_key_tab}, {K_BACK, &ft_key_back}, {K_RIGHT, ft_key_right},
	{K_UP, &ft_key_up}, {K_DOWN, &ft_key_down}, {K_LEFT, &ft_key_left},
	{K_NONE, NULL}, }), sizeof(t_keys[9]));
	i = 0;
	key = ft_get_char(col);
	if (key == -2)
		return (-2);
	while (key_funcs[i].func != NULL)
	{
		if (key_funcs[i].key == key)
			return (key_funcs[i].func(envp, col));
		i++;
	}
	return (1);
}

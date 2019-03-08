/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_key_controls.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/12 19:23:54 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/15 15:50:39 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_keys.h"

int		ft_key_back(char **envp, size_t *col)
{
	(void)envp;
	if (*col > 0)
		ft_remove_input(col);
	return (1);
}

int		ft_key_tab(char **envp, size_t *col)
{
	ft_completion(envp, col);
	return (1);
}

int		ft_key_return(char **envp, size_t *col)
{
	(void)envp;
	(void)col;
	ft_default_mode();
	return (0);
}

int		ft_key_ctrl_d(char **envp, size_t *col)
{
	(void)envp;
	(void)col;
	ft_default_mode();
	return (-1);
}

int		ft_key_iscontrol(char key)
{
	if (key == '\x7f')
		return (K_BACK);
	if (key == '\x9')
		return (K_TAB);
	if (key == '\xa')
		return (K_RETURN);
	if (key == '\x4')
		return (K_CTRL_D);
	return (K_NONE);
}

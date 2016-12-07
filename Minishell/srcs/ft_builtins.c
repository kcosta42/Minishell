/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 16:04:13 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/07 19:40:39 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_shell.h"

static int	ft_echo(char **argv)
{
	int		i;
	int		n;

	n = (argv[1] && !ft_strcmp(argv[1], "-n"));
	i = 1 + n;
	while (argv[i])
	{
		(void)ft_printf("%s", argv[i]);
		if (argv[i + 1])
			ft_putchar(' ');
		i++;
	}
	if (!n)
		ft_putchar('\n');
	return (0);
}

int			ft_builtins(const char *path, char **argv, char ***envp)
{
	if (!path)
		return (0);
	if (!ft_strcmp(path, "echo"))
		(void)ft_echo(argv);
/*	else if (!ft_strcmp(path, "cd"))
*/	else if (!ft_strcmp(path, "setenv"))
		(void)ft_setenv(argv, envp);
	else if (!ft_strcmp(path, "unsetenv"))
		(void)ft_unsetenv(argv, envp);
	else if (!ft_strcmp(path, "env"))
		(void)ft_env(argv, *envp);
/*	else if (!ft_strcmp(path, "exit"))
*/	else
		return (1);
	return (0);
}

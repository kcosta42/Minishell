/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 16:57:32 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/07 19:36:04 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_shell.h"

int			ft_env(char **argv, char **envp)
{
	int		i;

	(void)argv;
	i = 0;
	while (envp[i])
		ft_printf("%s\n", envp[i++]);
	return (1);
}

int			ft_unsetenv(char **argv, char ***envp)
{
	(void)envp;
	while (*argv)
		argv++;
	return (0);
}

int			ft_setenv(char **argv, char ***envp)
{
	char	*entry;
	char	*tmp;
	char	**envtmp;

	if (!argv[1])
		return (ft_env(argv, *envp));
	if (ft_tablen(argv) > 3)
		return (ft_printf("setenv: Too many arguments.\n"));
	if (ft_strisalnum(argv[1]))
		entry = ft_strjoin(argv[1], "=");
	else
		return (ft_printf("setenv: Variable name must \
contain alphanumeric characters.\n"));
	if (ft_strisalnum(argv[2]))
	{
		tmp = entry;
		entry = ft_strjoin(entry, argv[2]);
		ft_strdel(&tmp);
	}
	envtmp = *envp;
	*envp = ft_tabdup(*envp, entry);
	ft_strdel(&entry);
//	for (int i = 0; envtmp[i]; i++)
//		ft_strdel(&envtmp[i]);
//	ft_strdel((char**)&envtmp);
	//ft_tabdel(&envtmp);
	return (0);
}

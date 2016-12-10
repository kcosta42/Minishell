/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 16:57:32 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/10 09:19:26 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_shell.h"

int			ft_env(char **argv, char **envp)
{
	int		i;

	if (ft_tablen(argv) != 1)
		return (ft_printf("env: %s: Permission denied\n", argv[1]));
	i = 0;
	while (envp[i])
		ft_printf("%s\n", envp[i++]);
	return (1);
}

int			ft_unsetenv(char **argv, char ***envp)
{
	char	*entry;
	int		index;

	index = 1;
	while (argv[index])
	{
		entry = ft_strjoin(argv[index], "=");
		if (ft_tabstr(*envp, entry))
			ft_tabreplace(envp, entry, NULL);
		ft_strdel(&entry);
		index++;
	}
	return (0);
}

static int	ft_setenv_exist(char ***envp, char **var, char **entry)
{
	ft_tabreplace(envp, *var, (*entry) ? *entry : *var);
	if (*entry)
		ft_strdel(var);
	return (0);
}

int			ft_setenv(char **argv, char ***envp)
{
	char	*var;
	char	*entry;
	char	**envtmp;

	entry = NULL;
	if (!argv[1])
		return (ft_env(argv, *envp));
	if (ft_tablen(argv) > 3)
		return (ft_printf("setenv: Too many arguments.\n"));
	if (ft_strisalnum(argv[1]))
		var = ft_strjoin(argv[1], "=");
	else
		return (ft_printf("setenv: Variable name incorrect.\n"));
	if (argv[2])
		entry = ft_strjoin(var, argv[2]);
	if (ft_tabstr(*envp, var))
		return (ft_setenv_exist(envp, &var, &entry));
	envtmp = *envp;
	*envp = ft_tabdup(*envp, (entry) ? entry : var);
	if (entry)
		ft_strdel(&entry);
	ft_strdel(&var);
	ft_tabdel(&envtmp);
	return (0);
}

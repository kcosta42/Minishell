/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 15:59:46 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/08 19:14:18 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_shell.h"

static int		ft_cd_initialise(char **pwd, char **old_pwd, char **envp)
{
	*pwd = *ft_tabstr(envp, "PWD=") + 4;
	*old_pwd = *ft_tabstr(envp, "HOME=") + 5;
	return (0);
}

int				ft_cd(char **argv, char ***envp, int init)
{
	static char	*pwd = NULL;
	static char	*old_pwd = NULL;
	char		*tmp;

	if (init)
		return (ft_cd_initialise(&pwd, &old_pwd, *envp));
	if (ft_tablen(argv) != 2)
		return (ft_printf("cd: String not in pwd.\n"));
	if (argv[1][0] == '/')
		return (chdir(argv[1]));
	else if (argv[1][0] == '-')
	{
		chdir(old_pwd);
		tmp = pwd;
		pwd = old_pwd;
		old_pwd = tmp;
	}
	return (0);
}

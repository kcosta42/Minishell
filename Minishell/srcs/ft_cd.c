/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 15:59:46 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/09 22:26:24 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_shell.h"

static int		ft_cd_back(char ***envp, char **pwd, char **old_pwd)
{
	char		*path;
	size_t		size;

	ft_strdel(old_pwd);
	*old_pwd = ft_strdup(*pwd);
	size = (ft_strrchr(*pwd, '/') - *pwd) ? ft_strrchr(*pwd, '/') - *pwd : 1;
	path = ft_strnew(size);
	path = ft_strncpy(path, *pwd, size);
	chdir(path);
	ft_strdel(pwd);
	*pwd = path;
	return (ft_set_pwd(envp, *pwd, *old_pwd));
}

static int		ft_cd_forward(char ***envp, char *arg,
													char **pwd, char **old_pwd)
{
	char		*path;
	char		*tmp;

	ft_strdel(old_pwd);
	if (arg[0] == '/')
	{
		path = strdup(arg);
		*old_pwd = ft_strdup(*pwd);
		ft_strdel(pwd);
		*pwd = path;
		chdir(*pwd);
		return (ft_set_pwd(envp, *pwd, *old_pwd));
	}
	tmp = ft_strjoin(*pwd, "/");
	path = ft_strjoin(tmp, arg);
	ft_strdel(&tmp);
	chdir(path); // CAN SEGFAULT : ADD A CHECK FOR VALID DIRECTORY IN FT_CD
	*old_pwd = ft_strdup(*pwd);
	ft_strdel(pwd);
	*pwd = ft_get_path(&path);
	return (ft_set_pwd(envp, *pwd, *old_pwd));
}

static int		ft_cd_manage(char ***envp, char *arg,
													char **pwd, char **old_pwd)
{
	if (arg[0] == '-')
	{
		ft_printf("%s\n", *old_pwd);
		chdir(*old_pwd);
		ft_strswp(pwd, old_pwd);
		return (ft_set_pwd(envp, *pwd, *old_pwd));
	}
	else if (!ft_strcmp(arg, ".."))
		return (ft_cd_back(envp, pwd, old_pwd));
	else if (!ft_strcmp(arg, "."))
		return (0);
	else
		return (ft_cd_forward(envp, arg, pwd, old_pwd));
}

int				ft_cd(char **argv, char ***envp, int init)
{
	static char	*pwd = NULL;
	static char	*old_pwd = NULL;
	char		**path;
	size_t		index;

	if (init)
		return (ft_cd_initialise(&pwd, &old_pwd, *envp));
	if (ft_tablen(argv) != 2)
		return (ft_printf("cd: String not in pwd.\n"));
	path = ft_strsplit(argv[1], '/');
	index = 0;
	while (index < ft_tablen(path))
	{
		if (ft_cd_manage(envp, path[index++], &pwd, &old_pwd))
		{
			ft_tabdel(&path);
			return (1);
		}
	}
	ft_tabdel(&path);
	return (0);
}

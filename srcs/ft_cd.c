/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 15:59:46 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/22 17:28:27 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_shell.h"

static int		ft_cd_back(char **pwd)
{
	char		*path;
	size_t		size;

	size = (ft_strrchr(*pwd, '/') - *pwd) ? ft_strrchr(*pwd, '/') - *pwd : 1;
	path = ft_strnew(size);
	path = ft_strncpy(path, *pwd, size);
	chdir(path);
	ft_strdel(pwd);
	*pwd = path;
	return (0);
}

static int		ft_cd_forward(char *arg, char **pwd)
{
	char		*path;
	char		*tmp;

	if (arg[0] == '/')
	{
		path = ft_strdup(arg);
		ft_strdel(pwd);
		*pwd = path;
		return (chdir(*pwd));
	}
	if (ft_strcmp(*pwd, "/"))
		tmp = ft_strjoin(*pwd, "/");
	else
		tmp = ft_strdup(*pwd);
	path = ft_strjoin(tmp, arg);
	ft_strdel(&tmp);
	chdir(path);
	ft_strdel(pwd);
	*pwd = ft_get_path(&path);
	return (0);
}

static int		ft_cd_manage(char ***envp, char **path, char **pwd, char **old)
{
	size_t		index;

	index = 0;
	if (!ft_strcmp(path[index], "-"))
	{
		ft_printf("%s\n", *old);
		chdir(*old);
		ft_strswp(pwd, old);
		return (ft_set_pwd(envp, *pwd, *old));
	}
	ft_strdel(old);
	*old = ft_strdup(*pwd);
	while (index < ft_tablen(path))
	{
		if (!ft_strcmp(path[index], ".."))
			ft_cd_back(pwd);
		else if (!ft_strcmp(path[index], "."))
			;
		else
			ft_cd_forward(path[index], pwd);
		index++;
	}
	return (ft_set_pwd(envp, *pwd, *old));
}

static int		ft_cd_home(char *home, char ***envp, char **pwd, char **old_pwd)
{
	if (chdir(home) == -1)
		return (ft_printf("cd: HOME not found.\n"));
	ft_strdel(old_pwd);
	*old_pwd = ft_strdup(*pwd);
	ft_strdel(pwd);
	*pwd = ft_strdup(home);
	return (ft_set_pwd(envp, *pwd, *old_pwd));
}

int				ft_cd(char **argv, char ***envp, int init)
{
	static char *home = NULL;
	static char	*pwd = NULL;
	static char	*old_pwd = NULL;
	char		**path;

	if (init)
		return (ft_cd_initialise(&home, &pwd, &old_pwd, *envp));
	if (ft_tablen(argv) > 2)
		return (ft_printf("cd: String not in pwd.\n"));
	if (!argv[1] || !ft_strcmp(argv[1], "~"))
		return (ft_cd_home(home, envp, &pwd, &old_pwd));
	if (ft_isvalid_path(pwd, argv[1]))
		return (1);
	path = ft_path_split(argv[1]);
	(void)ft_cd_manage(envp, path, &pwd, &old_pwd);
	ft_tabdel(&path);
	return (0);
}

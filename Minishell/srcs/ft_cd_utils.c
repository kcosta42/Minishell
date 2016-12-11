/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 19:09:24 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/11 11:32:35 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_shell.h"

int			ft_cd_initialise(char **home, char **pwd,
												char **old_pwd, char **envp)
{
	*home = ft_strdup(*ft_tabstr(envp, "HOME=") + 5);
	*pwd = ft_strdup(*ft_tabstr(envp, "PWD=") + 4);
	*old_pwd = ft_strdup(*ft_tabstr(envp, "HOME=") + 5);
	return (0);
}

int			ft_set_pwd(char ***envp, char *pwd, char *old_pwd)
{
	char	*t_pwd;
	char	*t_old_pwd;
	int		del;

	del = 3;
	t_pwd = ft_strjoin("PWD=", pwd);
	t_old_pwd = ft_strjoin("OLDPWD=", old_pwd);
	if (ft_tabstr(*envp, "PWD="))
		del--;
	if (ft_tabstr(*envp, "OLDPWD="))
		del -= 2;
	ft_tabreplace(envp, "PWD=", t_pwd);
	ft_tabreplace(envp, "OLDPWD=", t_old_pwd);
	if (del == 1 || del == 3)
		ft_strdel(&t_pwd);
	if (del == 2 || del == 3)
		ft_strdel(&t_old_pwd);
	return (0);
}

int			ft_isvalid_path(char *path, char *arg)
{
	struct stat	st_stat;
	char		*tmp;
	char		*absolute_path;
	int			ret;

	ret = 0;
	if (!ft_strcmp(arg, "-"))
		return (ret);
	if (*arg != '/')
	{
		tmp = ft_strjoin(path, "/");
		absolute_path = ft_strjoin(tmp, arg);
		ft_strdel(&tmp);
	}
	else
		absolute_path = ft_strdup(arg);
	if (stat(absolute_path, &st_stat) == -1)
		ret = ft_printf("cd: No such file or directory: %s\n", arg);
	else if (!S_ISDIR(st_stat.st_mode))
		ret = ft_printf("cd: Not a directory: %s\n", arg);
	else if (access(absolute_path, X_OK) == -1)
		ret = ft_printf("cd: Permission denied: %s\n", arg);
	ft_strdel(&absolute_path);
	return (ret);
}

char		**ft_path_split(char *absolute_path)
{
	char	**path;
	char	*tmp;

	if (*absolute_path == '/')
	{
		tmp = ft_strjoin(" ", absolute_path);
		path = ft_strsplit(tmp, '/');
		path[0][0] = '/';
		ft_strdel(&tmp);
	}
	else
		path = ft_strsplit(absolute_path, '/');
	return (path);
}

char		*ft_get_path(char **path)
{
	char	*absolute_path;
	size_t	index;

	index = ft_strlen(*path) - 1;
	while ((*path)[index] == '/')
		index--;
	absolute_path = ft_strnew(index + 1);
	absolute_path = ft_strncpy(absolute_path, *path, index + 1);
	ft_strdel(path);
	return (absolute_path);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 19:09:24 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/09 22:16:40 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_shell.h"

int		ft_cd_initialise(char **pwd, char **old_pwd, char **envp)
{
	*pwd = ft_strdup(*ft_tabstr(envp, "PWD=") + 4);
	*old_pwd = ft_strdup(*ft_tabstr(envp, "HOME=") + 5);
	return (0);
}

int			ft_set_pwd(char ***envp, char *pwd, char *old_pwd)
{
	char	*t_pwd;
	char	*t_old_pwd;

	t_pwd = ft_strjoin("PWD=", pwd);
	t_old_pwd = ft_strjoin("OLDPWD=", old_pwd);
	ft_tabreplace(envp, "PWD=", t_pwd);
	ft_tabreplace(envp, "OLDPWD=", t_old_pwd);
	return (0);
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


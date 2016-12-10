/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 12:43:07 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/10 11:50:03 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_shell.h"
#include <sys/ioctl.h>

static void		ft_display_prompt(char **envp)
{
	static char	*pwd = NULL;
	char		**tmp;
	char		**path;
	int			size;

	if (envp)
		if ((tmp = ft_tabstr(envp, "PWD=")))
		{
			if (pwd)
				ft_strdel(&pwd);
			pwd = ft_strdup(*tmp + 4);
		}
	path = ft_path_split(pwd);
	size = ft_tablen(path) - 1;
	ft_printf("\n\033[1;34m");
	if (size >= 2)
		ft_printf("%s/", path[size - 2]);
	if (size >= 1)
		ft_printf("%s/", path[size - 1]);
	ft_printf("%s", path[size]);
	ft_printf("\033[0m\n%C ",  L'▶');
	ft_tabdel(&path);
}

static void		sig_handler(int signal)
{
	(void)signal;
	ft_putchar('\n');
	ft_display_prompt(NULL);
	return ;
}

int				ft_find_command(char *command, char **argv, char **envp)
{
	char	*tmp;
	char	*new;
	char	**paths;
	int		i;

	i = 0;
	execve(command, argv, envp);
	paths = ft_strsplit(*ft_tabstr(envp, "PATH="), ':');
	paths[0] = ft_strstr(paths[0], "=") + 1;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		new = ft_strjoin(tmp, command);
		execve(new, argv, envp);
		i++;
	}
	return (0);
}

int				main(int argc, char **argv, char **envp)
{
	pid_t	process;
	char	*line;
	char	*commands;
	int		ret;

	(void)argc;
	ret = 1;
	envp = ft_tabdup(envp, NULL);
	ft_cd(argv, &envp, 1);
	while (42)
	{
		if (ret == 0)
			exit(1);
		ft_display_prompt(envp);
		signal(SIGINT, sig_handler);
		//ioctl(0, TIOCSTI, "l");
		if ((ret = ft_getline(0, &line)) >= 0)
		{
			commands = ft_strepur(line);
			argv = ft_strsplit(commands, ' ');
			if (ft_builtins(argv[0], argv, &envp))
			{
				process = fork();
				if (!process)
				{
					ft_find_command(argv[0], argv, envp);
					ft_printf("0sh: Command not found: %s\n", argv[0]);
				}
				if (process > 0)
					wait(NULL);
				if (!process)
					exit(1);
			}
			ft_tabdel(&argv);
			ft_strdel(&line);
			ft_strdel(&commands);
		}
	}
}

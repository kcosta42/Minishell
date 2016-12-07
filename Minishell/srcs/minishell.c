/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcosta <kcosta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 12:43:07 by kcosta            #+#    #+#             */
/*   Updated: 2016/12/07 19:47:31 by kcosta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_shell.h"

int			main(int argc, char **argv, char **envp)
{
	pid_t	process;
	char	*line;
	char	*commands;

	(void)argc;
	(void)envp;
	(void)process;
	while (42)
	{
		ft_printf("\n\033[1;34m%s\033[0m\n%C ", "Minishell", L'▶');
		if (ft_getline(0, &line) > 0)
		{
			commands = ft_strepur(line);
			argv = ft_strsplit(commands, ' ');
			if (ft_builtins(argv[0], argv, &envp))
			{
				process = fork();
				if (!process)
				{
					execve(argv[0], argv, envp);
					ft_printf("0sh: Command not found: %s\n", argv[0]);
				}
				if (process > 0)
					wait(NULL);
				for (int i = 0; argv[i]; i++)
					ft_strdel(&argv[i]);
				ft_strdel((char**)&argv);
				ft_strdel(&line);
				ft_strdel(&commands);
				if (!process)
					exit(1);
			}
			if (argv)
			{
				for (int i = 0; argv[i]; i++)
					ft_strdel(&argv[i]);
				ft_strdel((char**)&argv);
			}
			if (line)
				ft_strdel(&line);
			if (commands)
				ft_strdel(&commands);
		}
	}
}
